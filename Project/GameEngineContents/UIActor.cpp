#include "PreCompile.h"
#include "UIActor.h"
#include "OverCookedUIRenderer.h"
#include "UIDebugGUI.h"
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

UIActor::UIActor()
{
}

UIActor::~UIActor()
{
}

void UIActor::Start()
{
	InitTransitionRenderer();
	UIStart();
	//std::shared_ptr<OverCookedTransition> NewEffect = GetLevel()->GetUICamera()->GetCameraRenderTarget()->AddEffect<OverCookedTransition>();
}

void UIActor::Update(float _DeltaTime)
{
	//FadeIn
	if (TransitionIcon_->IsFinishFadeIn_ == true)
	{
		TransitionIcon_->Off();
		BlackRenderer_->Off();
		TransitionIcon_->IsFinishFadeIn_ = false;
	}
	UIUpdate(_DeltaTime);
}

void UIActor::End()
{
	UIEnd();
}

void UIActor::StartFadeOut()
{
	TransitionIcon_->On();
	TransitionIcon_->StartFadeOut(7.0f);
	BlackRenderer_->On();
}

void UIActor::StartFadeIn()
{
	TransitionIcon_->On();
	TransitionIcon_->StartFadeIn();
	BlackRenderer_->On();
}

void UIActor::ResistDebug(std::string_view _Name, GameEngineTransform& Trans)
{
	UIDebugGUI::Main_->AddTransform(_Name.data(), &Trans);
}

std::shared_ptr<OverCookedUIRenderer> UIActor::CreateUIRenderer(std::string_view _TextrueName)
{
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateComponent<OverCookedUIRenderer>(_TextrueName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->ScaleToTexture();
	return NewRenderer;
}

std::shared_ptr<OverCookedUIRenderer> UIActor::CreateUIRenderer(std::string_view _TextrueName, float _ScaleRatio)
{
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateComponent<OverCookedUIRenderer>(_TextrueName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->SetScaleRatio(_ScaleRatio);
	NewRenderer->ScaleToTexture();
	return NewRenderer;
}

void UIActor::InitTransitionRenderer()
{
	if (BlackRenderer_ == nullptr)
	{
		BlackRenderer_ = CreateUIRenderer("Black.png");
		BlackRenderer_->ChangeCamera(CAMERAORDER::AboveUICAMERA);
		BlackRenderer_->Off();
	}

	TransitionIcon_ = CreateComponent<OverCookedUIRenderer>();
	TransitionIcon_->SetTexture("UI_Transitions_02.png");
	TransitionIcon_->ScaleToTexture();
	TransitionIcon_->ChangeCamera(CAMERAORDER::AboveUICAMERA);
	TransitionIcon_->Off();
}