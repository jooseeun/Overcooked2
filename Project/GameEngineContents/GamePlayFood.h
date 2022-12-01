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
//enum class ObjectFoodClass
//{
//	  None = 0
//	, Fish = 1
//	, Fish_Cutting
//	, Fish_Steam
//	, Prawn
//	, Prawn_Cutting
//	, Prawn_Steam
//	, Rice
//	, Rice_Steam
//	, Cucumber
//	, Cucumber_Cutting
//	, Seaweed
//	, Carrot
//	, Carrot_Cutting
//
//
//};


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

	inline IngredientType GetObjectFoodClass() const
	{
		if (Enum_IngredientType_ == IngredientType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectFoodClass_ 설정)");
		}
		return Enum_IngredientType_;
	}

protected:
	void Start() override;
	//void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


protected:

	inline void SetObjectFoodClass(IngredientType _Class)
	{
		Enum_IngredientType_ = _Class;
		if (Enum_IngredientType_ == IngredientType::None)
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
	IngredientType Enum_IngredientType_;


};

