#include "PreCompile.h"
#include "LoadingUIActor.h"

#include "GlobalGameData.h"
#include "OverCookedUIRenderer.h"

#include "LoadingData.h"
LoadingUIActor::LoadingUIActor()
{
}

LoadingUIActor::~LoadingUIActor()
{
}

void LoadingUIActor::StartLoad()
{
	LoadingData::GetFunc(GlobalGameData::GetCurStage().StageName)();
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
		//패널
		LevelSelect NewSelect;

		//인덱스
		NewSelect.Index = 0;

		//부모
		std::shared_ptr<OverCookedUIRenderer> NewParent = CreateUIRenderer("AvatarSelectionRing.png");
		NewParent->GetTransform().SetLocalScale({ 1.3f,1.3f,1.3f });
		NewParent->GetTransform().SetLocalPosition({ 0,100,-10 });
		NewSelect.Parent = NewParent;

		//맵 이미지
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("level_select_air_balloon.png");
		NewRenderer->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelect.Select = NewRenderer;

		//Select Boarder
		std::shared_ptr<OverCookedUIRenderer> NewSelectBoarder = CreateUIRenderer("level_boarder_0" + std::to_string(1) + "_selected.png");
		NewSelectBoarder->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelectBoarder->GetTransform().SetLocalMove({ 0,0,-1 });
		NewSelect.BoarderSelected = NewSelectBoarder;

		//폰트
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

	//마스크 렌더러
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

	//최고점수
	HighestScoreRenderer_ = CreateComponent<GameEngineFontRenderer>("CowntDownFont");
	HighestScoreRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
	HighestScoreRenderer_->SetText("최고점수: 100", "Naughty Squirrel");
	HighestScoreRenderer_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
	HighestScoreRenderer_->SetColor({ 120.f / 256.f,178.f / 256.f,218.f / 256.f,1 });
	HighestScoreRenderer_->SetSize(30.f);
	HighestScoreRenderer_->SetAffectTransform(true);
	HighestScoreRenderer_->GetTransform().SetLocalPosition({ 340,345 });
	//ResistDebug("HigestScore", HighestScoreRenderer_->GetTransform());

	//별
	{
		CreateStarNScoreRenderer({ -170,-130,0 }, 300);
		CreateStarNScoreRenderer({ -0,-130,0 }, 600);
		CreateStarNScoreRenderer({ 170,-130,0 }, 900);
	}

	//로딩
	LoadingBackRenderer_ = CreateUIRenderer("UI_LoadingScreen_LoadingBarBack_01.png");
	LoadingBackRenderer_->GetTransform().SetLocalPosition({ 0,-310.f,0 });
	LoadingFrontRenderer_ = CreateUIRenderer("UI_LoadingScreen_LoadingBar_01.png");
	LoadingFrontRenderer_->GetTransform().SetLocalPosition({ 0,-310.f,0 });
}

void LoadingUIActor::UIUpdate(float _DeltaTime)
{
	//시간이 지나면 다음 레벨로 전이
	AccTime_ += _DeltaTime;
	if (AccTime_ > 1.f)
	{
		AccTime_ = 0.f;
		GEngine::ChangeLevel(StageName_);
	}
	if (TransitionIcon_->IsFinishFadeIn_ == true)
	{
		TransitionIcon_->Off();
		BlackRenderer_->Off();
		TransitionIcon_->IsFinishFadeIn_ = false;
	}

	//UpdateInfo
	StageData CurData = GlobalGameData::GetCurStageRef();
	StageName_ = CurData.StageName;
	StageThema_ = CurData.StageThema;

	//RenderInfo
	HighestScoreRenderer_->SetText("최고점수: " + std::to_string(HigestScore_), "Naughty Squirrel");

	for (int i = 0; i < ScoreRenderer_.size(); i++)
	{
		ScoreRenderer_[i]->SetText(std::to_string(Score_[i]), "Naughty Squirrel");
	}
	CurStage_.Font->SetText(StageName_, "Naughty Squirrel");

	switch (CurData.StageThema)
	{
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

void LoadingUIActor::CreateStarNScoreRenderer(const float4& _Pos, int _Score)
{
	//빈 별 추가
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("UI_LoadingScreen_EmptyStar_01.png");
	NewRenderer->GetTransform().SetLocalPosition(_Pos);
	NewRenderer->ResistDebug();
	StarRenderer_.push_back(NewRenderer);

	//스코어 폰트 추가
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
	ResistDebug(std::to_string(_Score), NewFont->GetTransform());
	ScoreRenderer_.push_back(NewFont);
}