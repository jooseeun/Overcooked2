#pragma once
#include "UIActor.h"

class OverCookedUIRenderer;
class LoadingUIActor : public UIActor
{
	struct LevelSelect
	{
		int Index; // 처음 등록했을 때 Index
		std::shared_ptr<OverCookedUIRenderer> Parent;
		std::shared_ptr<OverCookedUIRenderer> Select;
		std::shared_ptr<GameEngineFontRenderer> Font;
		std::shared_ptr<OverCookedUIRenderer> BoarderSelected;
	};
public:
	LoadingUIActor();
	~LoadingUIActor();

	LoadingUIActor(const LoadingUIActor& _Other) = delete;
	LoadingUIActor(const LoadingUIActor&& _Other) noexcept = delete;
	LoadingUIActor& operator=(const LoadingUIActor& _Ohter) = delete;
	LoadingUIActor& operator=(const LoadingUIActor&& _Other) noexcept = delete;
protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;
private:
	std::shared_ptr<OverCookedUIRenderer> EndBackground_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> Background_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> Header_ = nullptr;
	std::vector<std::shared_ptr<OverCookedUIRenderer>> MaskBackground_;

	LevelSelect CurMap_;
};
