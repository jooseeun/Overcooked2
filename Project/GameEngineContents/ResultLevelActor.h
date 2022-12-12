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
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;
};
