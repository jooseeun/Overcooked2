#pragma once
#include "GamePlayStaticObject.h"
#include "Enums.h"



class FoodBox : public GamePlayStaticObject
{
public:
	FoodBox();
	~FoodBox();

	FoodBox(const FoodBox& _Other) = delete;
	FoodBox(FoodBox&& _Other) noexcept = delete;
	FoodBox& operator=(const FoodBox& _Other) = delete;
	FoodBox& operator=(FoodBox&& _Other) noexcept = delete;

	inline void SwitchIsInteraction()
	{
		IsInteraction_ = !IsInteraction_;
	}
	void SetFoodType(FoodType _Type);

	FoodType GetFoodType()
	{
		return Type_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	FoodType Type_;

	std::shared_ptr<GameEngineTextureRenderer> Renderer_;

	bool IsInteraction_;
	bool IsOpen_;
	float Angle_;

	std::shared_ptr<GameEngineActor> Lid_;
	

};

