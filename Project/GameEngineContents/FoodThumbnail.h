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

	inline void SetOffset(const float4& _Offset)
	{
		Offset_ = _Offset;
	}

	void SetThumbnail(IngredientType _Type); //+이미지를 띄우고 싶다면 FoodType::None
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<OverCookedUIRenderer> SingleThumbnail_;

	std::shared_ptr<GameEngineActor> ChaseActor_;

	float4 Pivot_ = { 0,0,0 };
	float4 Offset_ = { 0,0,0 };
};
