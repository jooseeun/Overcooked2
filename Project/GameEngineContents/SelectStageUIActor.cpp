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

void SelectStageUIActor::Start()
{
	LoadResource();
	InitRenderer();

	//CountDownFont_ = CreateComponent<GameEngineFontRenderer>("CowntDownFont");
	//CountDownFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	//CountDownFont_->SetText("0sd4", "Naughty Squirrel");
	//CountDownFont_->SetColor({ 120.f / 256.f,178.f / 256.f,218.f / 256.f,1 });
	//CountDownFont_->SetSize(30.f);
	//CountDownFont_->SetPositionMode(FontPositionMode::SCREEN);
}

void SelectStageUIActor::InitRenderer()
{
	EndBackground_ = CreateUIRenderer("EndBackground.png");

	Background_ = CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	Header_ = CreateUIRenderer("t_ui_dialog_header_01_d.png");
	Header_->GetTransform().SetLocalPosition({ -260,290 });

	ControlGuide_ = CreateUIRenderer("control_bg.png");
	ControlGuide_->GetTransform().SetLocalPosition({ -318,-308 });

	SelectMap_ = CreateUIRenderer("Selectmap.png");
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
		OverCookedUIRenderer* NewRenderer = CreateUIRenderer("screen_bg_overlay_01.png");
		NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
		//NewRenderer->GetTransform().SetLocalRotate({ 0,0,180.f });
		NewRenderer->StartDown(0.2f);
	}
}

void SelectStageUIActor::LoadResource()
{
	//�ʿ��� ���ҽ� �ε�
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("SelectStage");

		std::vector<GameEngineFile> Textures = Dir.GetAllFile();

		for (size_t i = 0; i < Textures.size(); i++)
		{
			GameEngineTexture::Load(Textures[i].GetFullPath());
		}
	}

	GameEngineFont::Load("Naughty Squirrel");
}

void SelectStageUIActor::Update(float _DeltaTime)
{
	MovingMap(_DeltaTime);
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
	}
	else
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

void SelectStageUIActor::End()
{
}

void SelectStageUIActor::ResistDebug(std::string_view _Name, GameEngineTransform& Trans)
{
	UIDebugGUI::Main_->AddTransform(_Name.data(), &Trans);
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
	OverCookedUIRenderer* NewParent = CreateUIRenderer("AvatarSelectionRing.png");
	NewParent->GetTransform().SetLocalScale({ 1,1,1 });
	NewParent->GetTransform().SetLocalPosition({ XSize * (_Index - StartIndex_),130,-10 });
	//NewParent->Off();
	NewSelect.Parent = NewParent;

	//�� �̹���
	OverCookedUIRenderer* NewRenderer = CreateUIRenderer(_MapFileName.data());
	NewRenderer->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewSelect.Select = NewRenderer;

	NewSelect.BoarderType = _BoarderType;

	//Non Selected Boarder
	OverCookedUIRenderer* NewBoarder = CreateUIRenderer("level_boarder_0" + std::to_string(NewSelect.BoarderType) + "_not_selected.png");
	NewBoarder->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewBoarder->GetTransform().SetLocalMove({ 0,0,-1 });
	NewSelect.Boarder = NewBoarder;

	//Select Boarder
	OverCookedUIRenderer* NewSelectBoarder = CreateUIRenderer("level_boarder_0" + std::to_string(NewSelect.BoarderType) + "_selected.png");
	NewSelectBoarder->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewSelectBoarder->GetTransform().SetLocalMove({ 0,0,-1 });
	NewSelectBoarder->Off();
	NewSelect.BoarderSelected = NewSelectBoarder;

	//�������̶���Ʈ
	OverCookedUIRenderer* LevelHighlight = CreateUIRenderer("level_highlight.png");
	LevelHighlight->GetTransform().SetParentTransform(NewParent->GetTransform());
	LevelHighlight->GetTransform().SetLocalMove({ 0,0,-10 });
	LevelHighlight->Off();
	NewSelect.LevelHighlisht = LevelHighlight;

	//��Ʈ
	GameEngineFontRenderer* NewFont = CreateComponent<GameEngineFontRenderer>(_Text.data());
	NewFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewFont->SetText(_Text.data(), "Naughty Squirrel");
	NewFont->SetColor({ 0.4f,0.4f,0.4f,1 });
	NewFont->SetSize(20.f);
	NewFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewFont->SetAffectTransform(true);
	NewFont->GetTransform().SetLocalMove({ 0,-65.f,-1 });
	NewFont->GetTransform().SetParentTransform(NewParent->GetTransform());

	LevelSelect_.push_back(NewSelect);
}

OverCookedUIRenderer* SelectStageUIActor::CreateUIRenderer(std::string_view _TextrueName)
{
	OverCookedUIRenderer* NewRenderer = CreateComponent<OverCookedUIRenderer>(_TextrueName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->ScaleToTexture();
	return NewRenderer;
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