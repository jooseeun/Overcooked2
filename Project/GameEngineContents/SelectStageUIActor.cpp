#include "PreCompile.h"
#include "SelectStageUIActor.h"

#include "OverCookedUIRenderer.h"
#include "UIDebugGUI.h"
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

SelectStageUIActor::SelectStageUIActor()
{
}

SelectStageUIActor::~SelectStageUIActor()
{
}

void SelectStageUIActor::UIStart()
{
	UIDebugGUI::Main_->AddMutableValue("PlayerCount", &PlayerCount_);

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
	switch (Phase_)
	{
	case 0:// 0 : Ű����� ���� �����ϴ� �ܰ� 1 : ���� �����ϰ� ��ٸ��� �ܰ�
	{
		MovingMap(_DeltaTime);
		UpdatePlayerIcon();
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
		if (TransitionIcon_->IsUpdate() == false)
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

void SelectStageUIActor::CreatePlayerIcon(int _Index, std::string_view _Name)
{
	PlayerIcon NewIcon;

	NewIcon.Index = _Index;
	NewIcon.Name = _Name;

	//�θ�
	std::shared_ptr<OverCookedUIRenderer> NewParent = CreateUIRenderer("AvatarSelectionRing.png");
	NewParent->GetTransform().SetLocalScale({ 1,1,1 });
	NewParent->GetTransform().SetLocalPosition({ 0,-180,0 });
	NewParent->ResistDebug(std::to_string(_Index));
	NewIcon.Parent = NewParent;

	//Hat Icon
	std::string HatFile;
	switch (_Index)
	{
	case 0:
		HatFile = "hat_blue.png";
		break;
	case 1:
		HatFile = "hat_red.png";
		break;
	case 2:
		HatFile = "hat_green.png";
		break;
	case 3:
		HatFile = "hat_yellow.png";
		break;
	default:
		break;
	}

	std::shared_ptr<OverCookedUIRenderer> Hat = CreateUIRenderer(HatFile);
	Hat->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.Hat = Hat;

	std::shared_ptr<OverCookedUIRenderer> NameBox = CreateUIRenderer("UI_BigButtonsSmall_01.png");
	NameBox->ResistDebug();
	NameBox->GetTransform().SetLocalPosition({ 0,-80,0 });
	NameBox->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.NameBox = NameBox;

	//������Ʈ
	std::shared_ptr<GameEngineFontRenderer> NewCountFont = CreateComponent<GameEngineFontRenderer>(_Name.data());
	NewCountFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewCountFont->SetText(std::to_string(_Index + 1), "Naughty Squirrel");
	NewCountFont->SetColor({ 0.4f,0.4f,0.4f,0.6f });
	NewCountFont->SetSize(49.f);
	NewCountFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewCountFont->SetAffectTransform(true);
	NewCountFont->GetTransform().SetLocalMove({ -80,50.f,-1 });
	NewCountFont->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.CountFont = NewCountFont;

	//�̸���Ʈ
	std::shared_ptr<GameEngineFontRenderer> NewNameFont = CreateComponent<GameEngineFontRenderer>(_Name.data());
	NewNameFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewNameFont->SetText(_Name.data(), "Naughty Squirrel");
	NewNameFont->SetColor({ 1.f,1.f,1.f,1.f });
	NewNameFont->SetSize(20.f);
	NewNameFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewNameFont->SetAffectTransform(true);
	NewNameFont->GetTransform().SetLocalMove({ 0,-62.f,-1 });
	NewNameFont->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.NameFont = NewNameFont;

	NewIcon.Off();

	Icons_.push_back(NewIcon);
}

void SelectStageUIActor::UpdatePlayerIcon()
{
	//���� ������
	if (PlayerCount_ >= 5)
	{
		PlayerCount_ = 4;
	}
	if (PlayerCount_ <= -1)
	{
		PlayerCount_ = 0;
	}
	for (int i = 0; i < Icons_.size(); i++)
	{
		Icons_[i].Off();
	}

	//��ġ ���� Update
	std::vector<float4> IconPos;
	float4 DefaultPos = Icons_[0].Parent->GetTransform().GetWorldPosition();
	DefaultPos.x = 0;
	switch (PlayerCount_)
	{
	case 1:
	{
		float4 Player0 = DefaultPos;
		IconPos.push_back(Player0);
		break;
	}

	case 2:
	{
		float4 Player0 = DefaultPos;
		Player0.x -= 140.f;
		float4 Player1 = DefaultPos;
		Player1.x += 140.f;
		IconPos.push_back(Player0);
		IconPos.push_back(Player1);
		break;
	}
	case 3:
	{
		float4 Player0 = DefaultPos;
		Player0.x -= 230.f;
		float4 Player1 = DefaultPos;
		float4 Player2 = DefaultPos;
		Player2.x += 230.f;
		IconPos.push_back(Player0);
		IconPos.push_back(Player1);
		IconPos.push_back(Player2);
		break;
	}
	case 4:
	{
		float4 Player0 = DefaultPos;
		Player0.x -= 360.f;
		float4 Player1 = DefaultPos;
		Player1.x -= 120.f;
		float4 Player2 = DefaultPos;
		Player2.x += 120.f;
		float4 Player3 = DefaultPos;
		Player3.x += 360.f;
		IconPos.push_back(Player0);
		IconPos.push_back(Player1);
		IconPos.push_back(Player2);
		IconPos.push_back(Player3);
		break;
	}
	default:
		break;
	}
	for (int i = 0; i < IconPos.size(); i++)
	{
		Icons_[i].Parent->GetTransform().SetWorldPosition(IconPos[i]);
	}
	for (int i = 0; i < PlayerCount_; i++)
	{
		Icons_[i].On();
	}
}

void SelectStageUIActor::MovingMap(float _DeltaTime)
{
	if (IsChanging() == false)
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
			StartSelectMap();
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

	//ī��Ʈ�ٿ� ����
	CountDown_.StartTimer(4.5);
	CountDown_.SetTimeOverFunc(std::bind(&SelectStageUIActor::StartTransition, this, 3));
	CountDownFont_->On();

	Phase_ = 1;
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

void SelectStageUIActor::PlayerIcon::Off()
{
	Parent->Off();
	Hat->Off();
	NameBox->Off();
	CountFont->Off();
	NameFont->Off();
}

void SelectStageUIActor::PlayerIcon::On()
{
	Parent->On();
	Hat->On();
	NameBox->On();
	CountFont->On();
	NameFont->On();
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