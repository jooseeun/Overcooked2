#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayFood.h"

enum class FoodType
{
	Tomato,
	Onion,
	Potato,
	Dough, //피자 반죽
	Seaweed, //미역
	Mushroom,
	Meat, 
	Lettuce, //양상추
	Rice,
	Flour, //밀가루
	Bread,
	Fish,
	Sausage,
	DumplingSkin, //만두피
	Egg,
	Chicken,
	Burrito, //부리또
	Cheese,
	Carrot,
	Chocolate,
	Honey,
	PastaNoodles, //파스타 면
	Shrimp,
	Cucumber //오이
};

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
	ObjectFoodClass Enum_Ingredients_;

	std::shared_ptr<GameEngineTextureRenderer> Renderer_;

	bool IsInteraction_;
	bool IsOpen_;
	float Angle_;

	std::shared_ptr<GameEngineActor> Lid_;
	
	FoodType Type_;
};

