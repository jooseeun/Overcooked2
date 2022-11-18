#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsUtility.h"

using namespace ContentsUtility;
class OverCookedUIRenderer;
class UIActor : public GameEngineActor
{
public:
	UIActor();
	~UIActor();

	UIActor(const UIActor& _Other) = delete;
	UIActor(const UIActor&& _Other) noexcept = delete;
	UIActor& operator=(const UIActor& _Ohter) = delete;
	UIActor& operator=(const UIActor&& _Other) noexcept = delete;

	void StartFadeOut();
	void StartFadeIn();

protected:
	virtual void UIStart() = 0;
	virtual void UIUpdate(float _DeltaTime) = 0;
	virtual void UIEnd() { };

	void ResistDebug(std::string_view _Name, GameEngineTransform& Trans);
	std::shared_ptr<OverCookedUIRenderer> CreateUIRenderer(std::string_view _TextrueName);
	std::shared_ptr<OverCookedUIRenderer> CreateUIRenderer(std::string_view _TextrueName, float _ScaleRatio);

	//Transition
	std::shared_ptr<OverCookedUIRenderer> BlackRenderer_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> TransitionIcon_ = nullptr;
private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void InitTransitionRenderer();
};
