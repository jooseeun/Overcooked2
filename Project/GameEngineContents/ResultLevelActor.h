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
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;

};

