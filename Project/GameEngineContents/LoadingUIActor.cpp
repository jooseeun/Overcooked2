#include "PreCompile.h"
#include "LoadingUIActor.h"

#include "GlobalGameData.h"
#include "OverCookedUIRenderer.h"
#include "GamePlayLevel.h"

#include "LoadingData.h"

#define ServerLoadingStart 4010
LoadingUIActor::LoadingUIActor()
{
}

LoadingUIActor::~LoadingUIActor()
{
}

void LoadingUIActor::StartLoad()
{
	if (IsLoadFirst_ == true)
	{
		IsLoadFirst_ = false;
		LoadingData::GetFunc("FirstLoad")();
		LoadingData::GetFunc(GlobalGameData::GetCurStage().StageName)();
		return;
	}
	LoadingData::GetFunc(GlobalGameData::GetCurStage().StageName)();
}

void LoadingUIActor::Reset()
{
	AccTime_ = 0.0f;
	IsLoad_ = false;
	TransitionIcon_->IsFinishFadeOut_ = false;
}

void LoadingUIActor::UIStart()
{
	InitRenderer();
}

void LoadingUIActor::InitRenderer()
{
	EndBackground_ = CreateUIRenderer("EndBackground.png");

	Background_ = CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	Header_ = CreateUIRenderer("t_ui_dialog_header_01_load.png");
	Header_->GetTransform().SetLocalPosition({ -260,290,-1 });

	{
		//�г�
		LevelSelect NewSelect;

		//�ε���
		NewSelect.Index = 0;

		//�θ�
		std::shared_ptr<OverCookedUIRenderer> NewParent = CreateUIRenderer("AvatarSelectionRing.png");
		NewParent->GetTransform().SetLocalScale({ 1.3f,1.3f,1.3f });
		NewParent->GetTransform().SetLocalPosition({ 0,100,-10 });
		NewSelect.Parent = NewParent;

		//�� �̹���
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("level_select_air_balloon.png");
		NewRenderer->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelect.Select = NewRenderer;

		//Select Boarder
		std::shared_ptr<OverCookedUIRenderer> NewSelectBoarder = CreateUIRenderer("level_boarder_0" + std::to_string(1) + "_selected.png");
		NewSelectBoarder->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelectBoarder->GetTransform().SetLocalMove({ 0,0,-1 });
		NewSelect.BoarderSelected = NewSelectBoarder;

		//��Ʈ
		std::shared_ptr<GameEngineFontRenderer> NewFont = CreateComponent<GameEngineFontRenderer>();
		NewFont->ChangeCamera(CAMERAORDER::UICAMERA);
		NewFont->SetText("1-1", "Naughty Squirrel");
		NewFont->SetColor({ 0.4f,0.4f,0.4f,1 });
		NewFont->SetSize(35.f);
		NewFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		NewFont->SetAffectTransform(true);
		NewFont->GetTransform().SetLocalMove({ 0,-58.f,-1 });
		NewFont->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelect.Font = NewFont;

		CurStage_ = NewSelect;
	}

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

	//�ְ�����
	HighestScoreRenderer_ = CreateComponent<GameEngineFontRenderer>("CowntDownFont");
	HighestScoreRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
	HighestScoreRenderer_->SetText("�ְ�����: 100", "Naughty Squirrel");
	HighestScoreRenderer_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
	HighestScoreRenderer_->SetColor({ 120.f / 256.f,178.f / 256.f,218.f / 256.f,1 });
	HighestScoreRenderer_->SetSize(30.f);
	HighestScoreRenderer_->SetAffectTransform(true);
	HighestScoreRenderer_->GetTransform().SetLocalPosition({ 340,345 });

	//��
	{
		CreateStarNScoreRenderer({ -170,-130,0 }, 300);
		CreateStarNScoreRenderer({ -0,-130,0 }, 600);
		CreateStarNScoreRenderer({ 170,-130,0 }, 900);
	}

	//�ε�
	LoadingBackRenderer_ = CreateUIRenderer("UI_LoadingScreen_LoadingBarBack_01.png");
	LoadingBackRenderer_->GetTransform().SetLocalPosition({ 0,-310.f,0 });
	LoadingFrontRenderer_ = CreateUIRenderer("UI_LoadingScreen_LoadingBar_01.png");
	LoadingFrontRenderer_->GetTransform().SetLocalPosition({ 0,-310.f,0 });
	LoadingFrontRenderer_->SetUIMode(3);
}

void LoadingUIActor::UIUpdate(float _DeltaTime)
{
	if (TransitionIcon_->IsFinishFadeOut_ == true)
	{
		std::vector<GameEngineLevel*> AllLevel = GameEngineCore::GetAllLevelVector();
		int i = 0;
		for (; i < AllLevel.size(); i++)
		{
			if (AllLevel[i]->GetNameCopy() == StageName_)
			{
				break;
			}
		}
		GamePlayLevel* Ptr = dynamic_cast<GamePlayLevel*>(AllLevel[i]);
		Ptr->SetIsLevelStart_False();
		GEngine::ChangeLevel(StageName_);
	}

	UpdateServer();

	StageData CurData = GlobalGameData::GetCurStageRef();

	UpdateInfo(CurData, _DeltaTime);

	RenderInfo(CurData);
}

void LoadingUIActor::UpdateServer()
{
	if (ServerInitManager::Net == nullptr)
	{
		return;
	}

	//�ð������� ���̴� �ε��� Update
	if (ServerInitManager::Net->GetIsHost() == true)
	{
		RealAccTimeMap_[GetNetID()] = AccTime_;
		while (false == IsPacketEmpty())
		{
			std::shared_ptr<GameServerPacket> Packet = PopPacket();

			ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

			switch (PacketType)
			{
			case ContentsPacketType::LoadingData:
			{
				std::shared_ptr<LoadingDataPacket> DataPacket = std::dynamic_pointer_cast<LoadingDataPacket>(Packet);
				float LoadingValue = DataPacket->LoadingReal;
				RealAccTimeMap_[DataPacket->ObjectID] = LoadingValue;
				break;
			}
			case ContentsPacketType::ClinetInit:
			default:
				MsgBoxAssert("ó���Ҽ� ���� ��Ŷ�� ���ƿԽ��ϴ�.");
				break;
			}
		}

		float VisualValue = RealAccTimeMap_[GetNetID()];
		for (auto i : RealAccTimeMap_)
		{
			if (i.second <= VisualValue)
			{
				VisualValue = i.second;
			}
		}

		VisualAccTime_ = VisualValue;

		//Ŭ�󿡰� Visual ���� �Ѹ���
		std::shared_ptr<LoadingDataPacket> Packet = std::make_shared<LoadingDataPacket>();
		Packet->ObjectID = GetNetID();
		Packet->LoadingVisual = VisualAccTime_;
		ServerInitManager::Net->SendPacket(Packet);

		//int UserCount = 0;
		//for (int i = ServerLoadingStart + 1;; i++)
		//{
		//	if (GameServerObject::GetServerObject(i) == nullptr)
		//	{
		//		break;
		//	}
		//	else
		//	{
		//		UserCount++;
		//	}
		//}
	}
	// Ŭ��� ȣ��Ʈ���� �ڱ��� ������¸� ����
	else
	{
		//�ڱ� ������� ��Ŷ���� ������
		std::shared_ptr<LoadingDataPacket> Packet = std::make_shared<LoadingDataPacket>();
		Packet->ObjectID = GetNetID();
		Packet->LoadingReal = AccTime_;
		ServerInitManager::Net->SendPacket(Packet);

		//ȣ��Ʈ�κ��� Visual ��Ŷ �ޱ�
		while (false == IsPacketEmpty())
		{
			std::shared_ptr<GameServerPacket> Packet = PopPacket();

			ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

			switch (PacketType)
			{
			case ContentsPacketType::LoadingData:
			{
				std::shared_ptr<LoadingDataPacket> DataPacket = std::dynamic_pointer_cast<LoadingDataPacket>(Packet);
				VisualAccTime_ = DataPacket->LoadingVisual;
				break;
			}
			case ContentsPacketType::ClinetInit:
			default:
				MsgBoxAssert("ó���Ҽ� ���� ��Ŷ�� ���ƿԽ��ϴ�.");
				break;
			}
		}
	}
}

void LoadingUIActor::UpdateInfo(StageData& CurData, float _DeltaTime)
{
	//�ð��� ������ ���� ������ ���� & �����ð� ������ �ʿ��� ���ҽ� Load
	AccTime_ += _DeltaTime;

	if (VisualAccTime_ > MaxAccTime_ * 0.5f && IsLoad_ == false)
	{
		IsLoad_ = true;
		StartLoad();
	}
	if (VisualAccTime_ > MaxAccTime_ && TransitionIcon_->IsUpdate() == false)
	{
		//AccTime_ = 0.f;
		StartFadeOut();
	}

	StageName_ = CurData.StageName;
	StageThema_ = CurData.StageThema;
}

void LoadingUIActor::RenderInfo(StageData& CurData)
{
	//�ε��� �ۼ�������  ������Ʈ
	LoadingFrontRenderer_->UpdateLeftToRight(VisualAccTime_ / MaxAccTime_);

	HighestScoreRenderer_->SetText("�ְ�����: " + std::to_string(HigestScore_), "Naughty Squirrel");

	for (int i = 0; i < ScoreRenderer_.size(); i++)
	{
		ScoreRenderer_[i]->SetText(std::to_string(Score_[i]), "Naughty Squirrel");
	}
	CurStage_.Font->SetText(StageName_, "Naughty Squirrel");

	switch (CurData.StageThema)
	{
	case Thema::Winter:
	{
		CurStage_.Select->SetTexture("DLC_Select_level_DLC03_ChristmasImage.png");
		break;
	}
	case Thema::SushiCity:
	{
		CurStage_.Select->SetTexture("level_select_sushi.png");
		break;
	}
	case Thema::WizardKitchen:
	{
		CurStage_.Select->SetTexture("level_select_wizard.png");
		break;
	}
	default:
		break;
	}
}

void LoadingUIActor::UIEnd()
{
}

void LoadingUIActor::LevelStartEvent()
{
	//������
	{
		int i = ServerLoadingStart;
		if (ServerInitManager::Net->GetIsHost() == true)
		{
			i = ServerLoadingStart;
			ClientInit(ServerObjectType::UI, i);
		}
		else
		{
			i = ServerLoadingStart + 1;
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
}

void LoadingUIActor::CreateStarNScoreRenderer(const float4& _Pos, int _Score)
{
	//�� �� �߰�
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("UI_LoadingScreen_EmptyStar_01.png");
	NewRenderer->GetTransform().SetLocalPosition(_Pos);
	StarRenderer_.push_back(NewRenderer);

	//���ھ� ��Ʈ �߰�
	std::shared_ptr<GameEngineFontRenderer> NewFont = CreateComponent<GameEngineFontRenderer>();
	NewFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewFont->SetText(std::to_string(_Score), "Naughty Squirrel");
	NewFont->SetColor({ 40.f / 256.f,86.f / 256.f,117.f / 256.f,1 });
	NewFont->SetSize(40.f);
	NewFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewFont->SetAffectTransform(true);
	NewFont->GetTransform().SetLocalPosition(_Pos);
	NewFont->GetTransform().SetLocalMove({ 0,-45.f,-1 });
	//NewFont->GetTransform().SetParentTransform(NewRenderer->GetTransform());
	ScoreRenderer_.push_back(NewFont);
}