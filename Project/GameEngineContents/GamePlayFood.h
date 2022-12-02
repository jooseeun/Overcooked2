#pragma once
#include "GamePlayMoveable.h"
// 설명 :
//enum class ObjectFoodType
//{
//	None,						//       	, 0
//	Ingredients,	  // 접시 X             , 1 ~ 99
//	Sandwich,		  // 접시 역할 및 제출 O, 100 ~ 199
//	Recipe,			  // 접시 및 제출 O     , 200 ~ 299
//
//};
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
//};

enum class ReturnMix
{
	NoMix,
	AtoB,
	BtoA
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

	inline IngredientType GetObjectFoodClass() const
	{
		if (Enum_IngredientType_ == IngredientType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectFoodClass_ 설정)");
		}
		return Enum_IngredientType_;
	}


	static ReturnMix CheckCombine(IngredientType _A, IngredientType _B)
	{
		if (IngredientInSandwitchTest(_A, _B))
		{
			return ReturnMix::BtoA;
		}
		else if (IngredientInSandwitchTest(_B, _A))
		{
			return ReturnMix::AtoB;
		}
		else
		{
			return ReturnMix::NoMix;
		}
	}

	static bool SandwitchTest(IngredientType _Type)
	{
		switch (_Type)
		{
		case IngredientType::Burrito:
		case IngredientType::Dough:
		case IngredientType::Seaweed:
		case IngredientType::Bread:
			return true;
			break;
		default:
			return false;
			break;
		}

	}
	static bool IngredientInSandwitchTest(IngredientType _Sandwitch, IngredientType _Ingredient)
	{
		switch (_Sandwitch)
		{
		//case IngredientType::Burrito:
		//{
		//	switch (_Ingredient)
		//	{
		//	case IngredientType::Tomato:
		//	case IngredientType::Onion:
		//	case IngredientType::Potato:
		//	case IngredientType::Dough:
		//	case IngredientType::Seaweed:
		//	case IngredientType::Mushroom:
		//	case IngredientType::Meat:
		//	case IngredientType::Lettuce:
		//	case IngredientType::Rice:
		//	case IngredientType::Flourbread:
		//	case IngredientType::Bread:
		//	case IngredientType::Fish:
		//	case IngredientType::Sausage:
		//	case IngredientType::DumplingSkin:
		//	case IngredientType::Egg:
		//	case IngredientType::Chicken:
		//	case IngredientType::Burrito:
		//	case IngredientType::Cheese:
		//	case IngredientType::Carrot:
		//	case IngredientType::Chocolate:
		//	case IngredientType::Honey:
		//	case IngredientType::PastaNoodles:
		//	case IngredientType::Prawn:
		//	case IngredientType::Cucumber:
		//	default:
		//		break;
		//	}

		//}
		//case IngredientType::Dough:
		//{


		//}
		case IngredientType::Seaweed:
		{
			switch (_Ingredient)
			{
			case IngredientType::Meat:
			case IngredientType::Rice:
			case IngredientType::Fish:
			case IngredientType::Carrot:
			case IngredientType::Prawn:
			case IngredientType::Cucumber:
				return true;
			default:
				break;
			}
		}
		case IngredientType::Bread:
		{
			switch (_Ingredient)
			{
			case IngredientType::Tomato:
			case IngredientType::Mushroom:
			case IngredientType::Meat:
			case IngredientType::Lettuce:
			case IngredientType::Cheese:
				return true;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}

		return false;

	}

protected:
	void Start() override;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


protected:
	inline void SetObjectFoodClass(IngredientType _Class)
	{
		Enum_IngredientType_ = _Class;
	}
	inline void SetTrim()
	{
		Trim_ = true;
	}

private:
	IngredientType Enum_IngredientType_;
	bool Trim_; // ture - 접시위에 올릴수 있음

	HoldDownEnum HoldUp(std::shared_ptr<Player> _Player) override
	{
		switch (HoldUp(_Player->GetPlayerHolding()->CastThis<GamePlayFood>()))
		{
		case HoldDownEnum::HoldUp:
			_Player->SetPlayerHolding(shared_from_this());
			_Player->SetCurHoldType(PlayerHoldType::CanThrow);
			return HoldDownEnum::HoldUp;
			break;
		case HoldDownEnum::HoldUpDelete:
			_Player->SetPlayerHolding(shared_from_this());
			_Player->SetCurHoldType(PlayerHoldType::NotThrow);
			return HoldDownEnum::HoldUpDelete;
			break;
		case HoldDownEnum::HoldDown:
			_Player->DetachPlayerHolding();
			return HoldDownEnum::HoldDown;
		default:
			return HoldDownEnum::Nothing;
			break;
		}
	};

	HoldDownEnum HoldUp(std::shared_ptr<GamePlayFood> _Food) final
	{
		switch (CheckCombine(GetObjectFoodClass(), _Food->GetObjectFoodClass()))
		{
		case ReturnMix::AtoB:
			return HoldDownEnum::HoldDown;
			break;
		case ReturnMix::BtoA:
			return HoldDownEnum::HoldUpDelete;
			break;
		default:
			break;
		}
		return HoldDownEnum::Nothing;
	}

	HoldDownEnum HoldUp(std::shared_ptr<GamePlayEquipment> _Equipment) final
	{
		return HoldDownEnum::Nothing;
	}

	HoldDownEnum HoldUp(std::shared_ptr<GamePlayBowl> _Bowl) final
	{
		if (Trim_ == false)
		{
			return HoldDownEnum::Nothing;
		}
		else
		{
			return HoldDownEnum::HoldDown;
		}
		
	}
};

