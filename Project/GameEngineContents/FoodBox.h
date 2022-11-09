#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayFood.h"

//음식 스폰 박스
class FoodBox : public GamePlayStaticObject
{
public:
	FoodBox();
	~FoodBox();

	FoodBox(const FoodBox& _Other) = delete;
	FoodBox(FoodBox&& _Other) noexcept = delete;
	FoodBox& operator=(const FoodBox& _Other) = delete;
	FoodBox& operator=(FoodBox&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	ObjectFoodClass Enum_Ingredients_;
};

