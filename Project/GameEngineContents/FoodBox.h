#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayFood.h"
#include "GamePlayTool.h"

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
	Prawn,
	Cucumber //오이
};

//음식 스폰 박스
class Tool_FoodBox : public GamePlayTool
{
	friend class FoodBox;
public:
	// constrcuter destructer
	Tool_FoodBox();
	~Tool_FoodBox();

	// delete Function
	Tool_FoodBox(const Tool_FoodBox& _Other) = delete;
	Tool_FoodBox(Tool_FoodBox&& _Other) noexcept = delete;
	Tool_FoodBox& operator=(const Tool_FoodBox& _Other) = delete;
	Tool_FoodBox& operator=(Tool_FoodBox&& _Other) noexcept = delete;

protected:
	void Start() override;

	//void Input_ActionToAuto_Update(std::shared_ptr<GamePlayMoveable> _Moveable, float _DeltaTime) override;
	Input_PickUpOption CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object) override;
	Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override;
	//Input_UsingOption Input_ActionToManual(Player* _Player) override
	//{
	//	return Input_UsingOption::NoResponse; // 수정요
	//}

	//void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) override;
private:
	FoodType Type_;
};



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
		return std::dynamic_pointer_cast<Tool_FoodBox>(GetStuff())->Type_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


	std::shared_ptr<GameEngineTextureRenderer> Renderer_;

	bool IsInteraction_;
	bool IsOpen_;
	float Angle_;

	std::shared_ptr<GameEngineActor> Lid_;
	

};

