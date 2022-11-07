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

	{
		//�г�
		LevelSelect NewSelect;

		//�θ�
		OverCookedUIRenderer* NewParent = CreateUIRenderer("AvatarSelectionRing.png");
		NewParent->GetTransform().SetLocalScale({ 1,1,1 });
		NewParent->GetTransform().SetLocalPosition({ 0,130,-10 });
		NewParent->ResistDebug();
		NewParent->Off();
		NewSelect.Parent = NewParent;

		//�� �̹���
		OverCookedUIRenderer* NewRenderer = CreateUIRenderer("level_select_sushi.png");
		NewRenderer->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelect.Select = NewRenderer;

		NewSelect.BoarderType = 1;

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
		LevelHighlight->GetTransform().SetLocalMove({ 0,0,-1 });
		LevelHighlight->Off();
		NewSelect.LevelHighlisht = LevelHighlight;

		//��Ʈ
		GameEngineFontRenderer* NewFont = CreateComponent<GameEngineFontRenderer>("SushiCity");
		NewFont->ChangeCamera(CAMERAORDER::UICAMERA);
		NewFont->SetText("�ʹ� ��Ƽ", "Naughty Squirrel");
		NewFont->SetColor({ 0.4f,0.4f,0.4f,1 });
		NewFont->SetSize(20.f);
		NewFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		NewFont->SetAffectTransform(true);
		NewFont->GetTransform().SetLocalMove({ 0,-65.f,-1 });
		NewFont->GetTransform().SetParentTransform(NewParent->GetTransform());

		LevelSelect_.push_back(NewSelect);
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
	if (GameEngineInput::GetInst()->IsDownKey("PlayerLeft") == true)
	{
		LevelSelect_[0].Parent->GetTransform().SetLocalMove(float4::RIGHT * 10.0f);
	}
}

void SelectStageUIActor::End()
{
}

void SelectStageUIActor::ResistDebug(std::string_view _Name, GameEngineTransform& Trans)
{
	UIDebugGUI::Main_->AddTransform(_Name.data(), &Trans);
}

OverCookedUIRenderer* SelectStageUIActor::CreateUIRenderer(std::string_view _TextrueName)
{
	OverCookedUIRenderer* NewRenderer = CreateComponent<OverCookedUIRenderer>(_TextrueName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->ScaleToTexture();
	return NewRenderer;
}