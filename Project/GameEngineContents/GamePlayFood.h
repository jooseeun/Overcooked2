#pragma once
#include "GamePlayMoveable.h"
// ���� :
enum class ObjectFoodType
{
	None,						//       	, 0
	Ingredients,	  // ���� X             , 1 ~ 99
	Sandwich,		  // ���� ���� �� ���� O, 100 ~ 199
	Recipe,			  // ���� �� ���� O     , 200 ~ 299

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
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayStuff::Enum_ObjectFoodType_ ����)");
		}
		return Enum_ObjectFoodType_;
	}

	inline ObjectFoodClass GetObjectFoodClass() const
	{
		if (Enum_ObjectFoodClass_ == ObjectFoodClass::None)
		{
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayStuff::Enum_ObjectFoodClass_ ����)");
		}
		return Enum_ObjectFoodClass_;
	}

	inline Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override
	{
		return Input_PickUpOption::NoResponse;
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

	inline void SetObjectFoodClass(ObjectFoodClass _Class)
	{
		Enum_ObjectFoodClass_ = _Class;
		if (Enum_ObjectFoodClass_ == ObjectFoodClass::None)
		{
			MsgBoxAssert("None�� �Է� �Ǿ����ϴ�");
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
	inline Input_UsingOption Input_Using(std::shared_ptr<Player> _Player) override
	{
		MsgBoxAssert("��� �� �� ���� Stuff (Food)");
		return Input_UsingOption::Throwing;
	}
	inline Input_UsingOption Input_Throwing(const float4& _Vector) override
	{
		SetVector(_Vector);
		return Input_UsingOption::Throwing;
	}



	ObjectFoodType Enum_ObjectFoodType_;
	ObjectFoodClass Enum_ObjectFoodClass_;

	float CookingGage;
};

