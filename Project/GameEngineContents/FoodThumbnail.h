#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Enums.h"
#include "OverCookedUIRenderer.h"

class FoodThumbnail : public GameEngineActor
{
public:
	FoodThumbnail();
	~FoodThumbnail();

	FoodThumbnail(const FoodThumbnail& _Other) = delete;
	FoodThumbnail(const FoodThumbnail&& _Other) noexcept = delete;
	FoodThumbnail& operator=(const FoodThumbnail& _Ohter) = delete;
	FoodThumbnail& operator=(const FoodThumbnail&& _Other) noexcept = delete;
	void LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<OverCookedUIRenderer> SingleThumbnail_;

	std::shared_ptr<GameEngineActor> ChaseActor_;

	float4 Pivot_ = { 0,0,0 };
	float4 Offset_ = { 0,0,0 };

	float DebugValue_ = 0.02f;
};
