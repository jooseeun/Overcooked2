#pragma once
#include "UIActor.h"
class ResultLevelActor : public UIActor
{
public:
	ResultLevelActor();
	~ResultLevelActor();

	ResultLevelActor(const ResultLevelActor& _Other) = delete;
	ResultLevelActor(const ResultLevelActor&& _Other) noexcept = delete;
	ResultLevelActor& operator=(const ResultLevelActor& _Ohter) = delete;
	ResultLevelActor& operator=(const ResultLevelActor&& _Other) noexcept = delete;

protected:
	std::weak_ptr<GameEngineFBXAnimationRenderer> OnionKing_;
	std::weak_ptr<GameEngineFBXAnimationRenderer> Kevin_;
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;

private:
	std::weak_ptr<GameEngineFontRenderer> DeliveredFoodCountFont_;
	std::weak_ptr<GameEngineFontRenderer> DeliveredFoodScoreFont_;
	std::weak_ptr<GameEngineFontRenderer> TipFont_;
	std::weak_ptr<GameEngineFontRenderer> TipScoreFont_;
	std::weak_ptr<GameEngineFontRenderer> FailFoodCountFont_;
	std::weak_ptr<GameEngineFontRenderer> FailFoodScoreFont_;
	std::weak_ptr<GameEngineFontRenderer> TotalFont_;
	std::weak_ptr<GameEngineFontRenderer> TotalScoreFont_;

	std::vector<std::weak_ptr<OverCookedUIRenderer>> FrontStarRenderer_;

	float IterTime_ = 0.f;
};
