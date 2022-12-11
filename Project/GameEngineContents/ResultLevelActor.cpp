#include "PreCompile.h"
#include "ResultLevelActor.h"

#include "GlobalGameData.h"
#include "OverCookedUIRenderer.h"
#include "GamePlayLevel.h"

ResultLevelActor::ResultLevelActor()
{
}

ResultLevelActor::~ResultLevelActor()
{
}

void ResultLevelActor::UIStart()
{
	CreateUIRenderer("EndBackground.png");

	CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	std::weak_ptr<OverCookedUIRenderer> Header = CreateUIRenderer("t_ui_dialog_header_01_non.png");
	Header.lock()->GetTransform().SetLocalPosition({-260,290,-1});

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

void ResultLevelActor::UIUpdate(float _DeltaTime)
{
}

void ResultLevelActor::UIEnd()
{
}
