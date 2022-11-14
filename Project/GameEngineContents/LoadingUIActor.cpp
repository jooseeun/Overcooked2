#include "PreCompile.h"
#include "LoadingUIActor.h"

#include "OverCookedUIRenderer.h"

LoadingUIActor::LoadingUIActor()
{
}

LoadingUIActor::~LoadingUIActor()
{
}

void LoadingUIActor::UIStart()
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
		NewFont->GetTransform().SetLocalMove({ 0,-65.f,-1 });
		NewFont->GetTransform().SetParentTransform(NewParent->GetTransform());
		NewSelect.Font = NewFont;

		CurMap_ = NewSelect;
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
}

void LoadingUIActor::UIUpdate(float _DeltaTime)
{
	if (TransitionIcon_->IsFinishFadeIn_ == true)
	{
		TransitionIcon_->Off();
		BlackRenderer_->Off();
		TransitionIcon_->IsFinishFadeIn_ = false;
	}
}

void LoadingUIActor::UIEnd()
{
}