#include "PreCompile.h"
#include "SelectStageUIActor.h"

#include "OverCookedUIRenderer.h"
#include "UIDebugGUI.h"
#include "GlobalGameData.h"
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

SelectStageUIActor::SelectStageUIActor()
{
}

SelectStageUIActor::~SelectStageUIActor()
{
}

void SelectStageUIActor::ServerRelease()
{
	if (ServerInitManager::Net->GetIsHost() == true)
	{
		EraseServerObject(GetNetID());
	}
}

void SelectStageUIActor::ServerInit()
{
	if (ServerInitManager::Net->GetIsHost() == true)
	{
		ClientInit(ServerObjectType::UI, 4020);
	}
	else
	{
		int i = 4021;
		for (; ; i++)
		{
			if (GameServerObject::GetServerObject(i) == nullptr)
			{
				ClientInit(ServerObjectType::UI, i);
				break;
			}
		}
	}
}

void SelectStageUIActor::UIStart()
{
	InitRenderer();
}

void SelectStageUIActor::InitRenderer()
{
	EndBackground_ = CreateUIRenderer("EndBackground.png");

	Background_ = CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	Header_ = CreateUIRenderer("t_ui_dialog_header_01_d.png");
	Header_->GetTransform().SetLocalPosition({ -260,290,-1 });

	ControlGuide_ = CreateUIRenderer("control_bg.png");
	ControlGuide_->GetTransform().SetLocalPosition({ -318,-308,-1 });

	SelectMap_ = CreateUIRenderer("Selectmap.png");
	SelectMap_->SetSamplerPointClamp();
	SelectMap_->GetTransform().SetLocalPosition({ 20,-30 });

	CreateLevelSelect("level_select_air_balloon.png", 1, "���ⱸ ����", 0);
	CreateLevelSelect("level_select_raft.png", 3, "�԰ɽ����� �޷�", 1);
	CreateLevelSelect("level_select_space.png", 2, "�̽İ� ����", 2);
	CreateLevelSelect("UI_Level_Select_Random_01.png", 1, "����", 3);
	CreateLevelSelect("level_select_sushi.png", 3, "�ʹ� ��Ƽ", 4);
	CreateLevelSelect("level_select_wizard.png", 2, "�������� Űģ", 5);
	CreateLevelSelect("level_select_mine.png", 2, "��ĥ�� ���� ����", 6);

	//����ũ ������
	{
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("screen_bg_overlay_01.png");
		NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
		NewRenderer->SetSamplerWrap();
		NewRenderer->StartDown(0.2f);
	}
	{
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("screen_bg_overlay_02.png");
		NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
		NewRenderer->SetSamplerWrap();
		NewRenderer->StartDown(0.1f);
	}

	//ȭ��ǥ ������
	{
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("UI_ArrowLeft_Dark_01.png");
		NewRenderer->GetTransform().SetLocalPosition({ -200.f,-30.f });
		ArrowRenderer_.push_back(NewRenderer);
	}
	{
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("UI_ArrowRight_Dark_01.png");
		NewRenderer->GetTransform().SetLocalPosition({ 210.f,-30.f });
		ArrowRenderer_.push_back(NewRenderer);
	}

	//�÷��̾� ������
	{
		CreatePlayerIcon(0, "LoveSushi");
		CreatePlayerIcon(1, "AS40");
		CreatePlayerIcon(2, "NiceRice");
		CreatePlayerIcon(3, "HelpMe");
	}

	//ī��Ʈ �ٿ�
	CountDownFont_ = CreateComponent<GameEngineFontRenderer>("CowntDownFont");
	CountDownFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	CountDownFont_->SetText("04", "Naughty Squirrel");
	CountDownFont_->SetColor({ 120.f / 256.f,178.f / 256.f,218.f / 256.f,1 });
	CountDownFont_->SetSize(58.f);
	CountDownFont_->SetAffectTransform(true);
	CountDownFont_->GetTransform().SetLocalPosition({ 340,345 });
	CountDownFont_->Off();
}

void SelectStageUIActor::UIUpdate(float _DeltaTime)
{
	//Ŭ��� �����κ��� ��ǲ �����͸� �޴´�
	while (false == IsPacketEmpty())
	{
		std::shared_ptr<GameServerPacket> Packet = PopPacket();
		if (Packet == nullptr)
		{
			break;
		}

		ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

		switch (PacketType)
		{
		case ContentsPacketType::SelectStageInputData:
		{
			std::shared_ptr<SelectStageInputDataPacket> InputPacket = std::dynamic_pointer_cast<SelectStageInputDataPacket>(Packet);
			InputBuffer_ = InputPacket->InputBuffer;
			//RecipeManager_.CreateRecipe(static_cast<FoodType>(RecipePacket->CreateFoodType));
			break;
		}
		default:
			break;
		}
	}



	switch (Phase_)
	{
	case 0:// 0 : Ű����� ���� �����ϴ� �ܰ� 1 : ���� �����ϰ� ��ٸ��� �ܰ�
	{
		MovingMap(_DeltaTime);
		UpdatePlayerIcon(_DeltaTime);
		break;
	}
	case 1://1 : ���� �����ϰ� ��ٸ��� �ܰ�
	{
		//ī��Ʈ�ٿ� ������Ʈ
		int CountDownNum = static_cast<int>(CountDown_.GetCurTime());
		CountDownFont_->SetText("0" + std::to_string(CountDownNum), "Naughty Squirrel");
		CountDown_.Update(_DeltaTime);
		break;
	}
	case 2://Transition�ִϸ��̼� ���
	{
		if (TransitionIcon_->IsFinishFadeOut_ == true)
		{
			GEngine::ChangeLevel("LoadingLevel");
		}
		break;
	}
	default:
		break;
	}
}

void SelectStageUIActor::UIEnd()
{
}

void SelectStageUIActor::MovingMap(float _DeltaTime)
{
	
	if (IsChanging() == false)
	{
		if (ServerInitManager::Net->GetIsHost() == true)
		{
			if (GameEngineInput::GetInst()->IsDownKey("PlayerLeft") == true)
			{
				StartChange(1);//���� ���� ���� �����Ѵ�. & �� �ʵ��� ���������� �̵��Ѵ�.
			}
			else if (GameEngineInput::GetInst()->IsDownKey("PlayerRight") == true)
			{
				StartChange(-1); // ���� �� ������ ���� �����Ѵ�. & �� �ʵ��� �������� �̵��Ѵ�.
			}
			else if (GameEngineInput::GetInst()->IsDownKey("PlayerHold") == true)
			{
				std::shared_ptr<SelectStageInputDataPacket> Packet = std::make_shared<SelectStageInputDataPacket>();
				Packet->InputBuffer = 0;
				ServerInitManager::Net->SendPacket(Packet);
				StartSelectMap();

			}
		}
		else
		{
			if (InputBuffer_ > -2)
			{
				if (InputBuffer_ != 0)
				{
					StartChange(InputBuffer_);
				}
				else
				{
					StartSelectMap();
				}
				InputBuffer_ = -2;
			}
		}

	}
	else //���� ȭ�� ��ȯ ��
	{
		if (CurInterval_Iter_ >= 1.f)
		{
			EndChange();
		}
		else
		{
			CurInterval_Iter_ += _DeltaTime * 3.5f;
			float CurInterval = GameEngineMath::LerpLimit(0.f, Interval_, CurInterval_Iter_);
			//�̵�
			for (int i = 0; i < LevelSelect_.size(); i++)
			{
				float4 PrevPos = PrevPos_[i];
				PrevPos.x += CurInterval * MovingDir_;
				LevelSelect_[i].Parent->GetTransform().SetWorldPosition(PrevPos);
			}
		}
	}
}

void SelectStageUIActor::StartSelectMap()
{
	//CurPos�� StartIndex�� �༮�� Select�ϱ�
	for (int i = 0; i < LevelSelect_.size(); i++)
	{
		LevelSelect_[i].Off();
	}
	SelectMap_->Off();
	for (auto i : ArrowRenderer_)
	{
		i->Off();
	}

	int WantIndex = 0;
	for (; WantIndex < LevelSelect_.size(); WantIndex++)
	{
		if (LevelSelect_[WantIndex].CurPos == StartIndex_)
		{
			break;
		}
	}
	LevelSelect_[WantIndex].On();
	LevelSelect_[WantIndex].LevelHighlisht->Off();
	LevelSelect_[WantIndex].Font->Off();
	LevelSelect_[WantIndex].Parent->StartPump(1.1f, 8.0f);

	SetCurStage(WantIndex);

	//ī��Ʈ�ٿ� ����
	CountDown_.StartTimer(4.5);
	CountDown_.SetTimeOverFunc(std::bind(&SelectStageUIActor::StartTransition, this, 3));
	CountDownFont_->On();

	Phase_ = 1;
}

void SelectStageUIActor::SetCurStage(int _Index)
{
	std::string WantStage;
	switch (_Index)
	{
	case 4: //�ʹ��Ƽ
	{
		WantStage = "1-1";
		//StageName = "4-1";
		//StageName = "�ɺ� 3";
		break;
	}
	case 5: //�������� Űģ
	{
		WantStage = "1-4";

		break;
	}
	default:
		WantStage = "1-1";

		break;
	}

	GlobalGameData::SetCurStage(WantStage);
}

void SelectStageUIActor::EndChange()
{
	//Index �̵�
	for (int i = 0; i < LevelSelect_.size(); i++)
	{
		if (MovingDir_ == 1) //���������� �̵��Ѵٸ� && ���� ���� ����� �Է�
		{
			LevelSelect_[i].CurPos++;
			if (LevelSelect_[i].CurPos >= LevelSelect_.size())
			{
				LevelSelect_[i].CurPos = 0;
			}
		}
		else if (MovingDir_ == -1) //�������� �̵��Ѵٸ� && ���� ������ ����Ű �Է�
		{
			LevelSelect_[i].CurPos--;
			if (LevelSelect_[i].CurPos <= -1)
			{
				LevelSelect_[i].CurPos = static_cast<int>(LevelSelect_.size()) - 1;
			}
		}
	}

	//CurPos�� ���缭 ������
	for (int i = 0; i < LevelSelect_.size(); i++)
	{
		LevelSelect_[i].Parent->GetTransform().SetLocalPosition({ Interval_ * (LevelSelect_[i].CurPos - StartIndex_),130,-10 });
	}

	//CurPos�� 3�� �༮�� Pumping�ϱ�
	int WantIndex = 0;
	for (; WantIndex < LevelSelect_.size(); WantIndex++)
	{
		if (LevelSelect_[WantIndex].CurPos == StartIndex_)
		{
			break;
		}
	}
	LevelSelect_[WantIndex].Parent->StartPump(1.1f, 8.f);

	PrevPos_.clear();
	CurInterval_Iter_ = 0.f;
	IsChanging_ = false;
}

void SelectStageUIActor::CreateLevelSelect(std::string_view _MapFileName, int _BoarderType, std::string_view _Text, int _Index)
{
	float XSize = Interval_;
	//�г�
	LevelSelect NewSelect;

	//�ε���
	NewSelect.Index = _Index;
	NewSelect.CurPos = _Index;

	//�θ�
	std::shared_ptr<OverCookedUIRenderer> NewParent = CreateUIRenderer("AvatarSelectionRing.png");
	NewParent->GetTransform().SetLocalScale({ 1,1,1 });
	NewParent->GetTransform().SetLocalPosition({ XSize * (_Index - StartIndex_),130,-10 });
	//NewParent->Off();
	NewSelect.Parent = NewParent;

	//�� �̹���
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer(_MapFileName.data());
	NewRenderer->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewSelect.Select = NewRenderer;

	NewSelect.BoarderType = _BoarderType;

	//Non Selected Boarder
	std::shared_ptr<OverCookedUIRenderer> NewBoarder = CreateUIRenderer("level_boarder_0" + std::to_string(NewSelect.BoarderType) + "_not_selected.png");
	NewBoarder->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewBoarder->GetTransform().SetLocalMove({ 0,0,-1 });
	NewSelect.Boarder = NewBoarder;

	//Select Boarder
	std::shared_ptr<OverCookedUIRenderer> NewSelectBoarder = CreateUIRenderer("level_boarder_0" + std::to_string(NewSelect.BoarderType) + "_selected.png");
	NewSelectBoarder->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewSelectBoarder->GetTransform().SetLocalMove({ 0,0,-1 });
	NewSelectBoarder->Off();
	NewSelect.BoarderSelected = NewSelectBoarder;

	//�������̶���Ʈ
	std::shared_ptr<OverCookedUIRenderer> LevelHighlight = CreateUIRenderer("level_highlight.png");
	LevelHighlight->GetTransform().SetParentTransform(NewParent->GetTransform());
	LevelHighlight->GetTransform().SetLocalMove({ 0,0,-10 });
	LevelHighlight->Off();
	NewSelect.LevelHighlisht = LevelHighlight;

	//��Ʈ
	std::shared_ptr<GameEngineFontRenderer> NewFont = CreateComponent<GameEngineFontRenderer>(_Text.data());
	NewFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewFont->SetText(_Text.data(), "Naughty Squirrel");
	NewFont->SetColor({ 0.4f,0.4f,0.4f,1 });
	NewFont->SetSize(20.f);
	NewFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewFont->SetAffectTransform(true);
	NewFont->GetTransform().SetLocalMove({ 0,-65.f,-1 });
	NewFont->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewSelect.Font = NewFont;

	LevelSelect_.push_back(NewSelect);
}

void SelectStageUIActor::StartChange(int _Dir)
{
	if (ServerInitManager::Net->GetIsHost() == true)
	{
		std::shared_ptr<SelectStageInputDataPacket> Packet = std::make_shared<SelectStageInputDataPacket>();
		Packet->InputBuffer = _Dir;
		ServerInitManager::Net->SendPacket(Packet);
	}
	ShowSelectEffect(_Dir);

	//�����̱� �� ��ġ���� ����
	PrevPos_.clear();
	for (int i = 0; i < LevelSelect_.size(); i++)
	{
		float4 CurPos = LevelSelect_[i].Parent->GetTransform().GetWorldPosition();
		PrevPos_.push_back(CurPos);
	}
	CurInterval_Iter_ = 0.f;
	MovingDir_ = _Dir;
	IsChanging_ = true;
}

void SelectStageUIActor::ShowSelectEffect(int _Dir)
{
	//��� ���� ����Ʈ�� ���� �� ���� ����Ʈ�� Ų��
	for (int i = 0; i < LevelSelect_.size(); i++)
	{
		LevelSelect_[i].BoarderSelected->Off();
		LevelSelect_[i].LevelHighlisht->Off();
	}

	int WantIndex = 0; //���̶���Ʈ�ϰ� ���� �ε���
	if (_Dir == 1) //���� ����Ű
	{
		for (; WantIndex < LevelSelect_.size(); WantIndex++)
		{
			if (LevelSelect_[WantIndex].CurPos == 2)
			{
				break;
			}
		}
	}
	else if (_Dir == -1) //������ ����Ű
	{
		for (; WantIndex < LevelSelect_.size(); WantIndex++)
		{
			if (LevelSelect_[WantIndex].CurPos == 4)
			{
				break;
			}
		}
	}

	LevelSelect_[WantIndex].BoarderSelected->On();
	LevelSelect_[WantIndex].LevelHighlisht->On();
}

bool SelectStageUIActor::IsChanging()
{
	return IsChanging_;
}

void SelectStageUIActor::StartTransition(int _A)
{
	CountDownFont_->Off();
	StartFadeOut();
	Phase_ = 2;
	//GEngine::ChangeLevel("LoadingLevel");
}

void SelectStageUIActor::LevelSelect::On()
{
	Parent->On();
	Select->On();
	Font->On();
	Boarder->On();
	BoarderSelected->On();
	LevelHighlisht->On();
}

void SelectStageUIActor::LevelSelect::Off()
{
	Parent->Off();
	Select->Off();
	Font->Off();
	Boarder->Off();
	BoarderSelected->Off();
	LevelHighlisht->Off();
}