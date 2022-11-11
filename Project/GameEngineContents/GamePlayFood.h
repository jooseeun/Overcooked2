#pragma once
#include "GamePlayMoveable.h"
// 설명 :
enum class ObjectFoodType
{
	None,						//       	, 0
	Ingredients,	  // 접시 X             , 1 ~ 99
	Sandwich,		  // 접시 역할 및 제출 O, 100 ~ 199
	Recipe,			  // 접시 및 제출 O     , 200 ~ 299

};
enum class ObjectFoodClass
{
	None = 0,
	Fish = 1,
	Fish_Cutting,
	Prawn,
	Prawn_Cutting,



	Recipe_Default = 100,
};


class GamePlayFood : public GamePlayMoveable
{
protected:
	GamePlayFood();

public:
	// constrcuter destructer

	~GamePlayFood();

	// delete Function
	GamePlayFood(const GamePlayFood& _Other) = delete;
	GamePlayFood(GamePlayFood&& _Other) noexcept = delete;
	GamePlayFood& operator=(const GamePlayFood& _Other) = delete;
	GamePlayFood& operator=(GamePlayFood&& _Other) noexcept = delete;


	inline ObjectFoodType GetObjectFoodType() const
	{
		if (Enum_ObjectFoodType_ == ObjectFoodType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectFoodType_ 설정)");
		}
		return Enum_ObjectFoodType_;
	}

	inline ObjectFoodClass GetObjectFoodClass() const
	{
		if (Enum_ObjectFoodClass_ == ObjectFoodClass::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectFoodClass_ 설정)");
		}
		return Enum_ObjectFoodClass_;
	}

	inline Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override
	{
		return Input_PickUpOption::NoResponse;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


protected:

	inline void SetObjectFoodClass(ObjectFoodClass _Class)
	{
		Enum_ObjectFoodClass_ = _Class;
		if (Enum_ObjectFoodClass_ == ObjectFoodClass::None)
		{
			MsgBoxAssert("None이 입력 되었습니다");
		}

		int Class = static_cast<int>(_Class);
		if (Class < 100)
		{
			Enum_ObjectFoodType_ = ObjectFoodType::Ingredients;
		}
		else if (Class < 200)
		{
			Enum_ObjectFoodType_ = ObjectFoodType::Sandwich;
		}
		else if (Class < 300)
		{
			Enum_ObjectFoodType_ = ObjectFoodType::Recipe;
		}
	}
private:

	ObjectFoodType Enum_ObjectFoodType_;
	ObjectFoodClass Enum_ObjectFoodClass_;

	float CookingGage;
};

