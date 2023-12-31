#pragma once
#include "GamePlayMoveable.h"
#include "FoodThumbnail.h"
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

enum class CookingType
{
	Default
	, Pried
	, Steam
	, Mixer
	, Boil
	, Oven
};

class CombinFood;
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

	inline std::shared_ptr<FoodThumbnail> GetFoodThumbnail() const
	{
		return FoodThumbnail_;
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

	static std::shared_ptr<GamePlayFood> GetIngredientClass(IngredientType _Type);
	static bool ReadMapFoodData(std::shared_ptr<GamePlayFood> _Food);

	inline const std::string& GetMeshName() const
	{
		return MeshName_;
	}
	inline bool GetTrim()
	{
		return Trim_;
	}
	inline bool GetPlatting()
	{
		return Platting_;
	}
	inline CookingType GetCookingType()
	{
		return CookingType_;
	}
	inline std::shared_ptr<CombinFood> GetCombinFood()
	{
		return CombinFood_;
	}
	

protected:
	void Start() override;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() final {};
	//void LevelEndEvent() override {};


protected:
	void SetObjectFoodClass(IngredientType _Class);
	inline void SetTrim()
	{
		Trim_ = true;
	}
	inline void SetPlatting()
	{
		Platting_ = true;
	}
	inline void SetCookingType(CookingType _Type)
	{
		CookingType_ = _Type;
		switch (CookingType_)
		{
		case CookingType::Default:
			Function_TrimmingType_ = std::bind(&GamePlayFood::TrimmingPlatting, this);
			break;
		case CookingType::Pried:
			Function_TrimmingType_ = std::bind(&GamePlayFood::TrimmingPried, this);
			break;
		case CookingType::Steam:
			Function_TrimmingType_ = std::bind(&GamePlayFood::TrimmingSteam, this);
			break;
		case CookingType::Mixer:
			Function_TrimmingType_ = std::bind(&GamePlayFood::TrimmingMixer, this);
			break;
		case CookingType::Boil :
			Function_TrimmingType_ = std::bind(&GamePlayFood::TrimmingBoil, this);
				break;
		default:
			MsgBoxAssert("아직 설정되지 않았습니다")
			break;
		}
	}
	


	std::string MeshName_; // 지금 매쉬 이름
	std::shared_ptr<FoodThumbnail> FoodThumbnail_; // 썸네일

	std::function<void()> Function_TrimmingType_;
	std::shared_ptr<CombinFood> CombinFood_;

private:
	IngredientType Enum_IngredientType_;
	bool Trim_; // ture - 손질이 다 됨
	bool Platting_; // ture - 접시에 올릴수 있는가?
	CookingType CookingType_;

	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;

	void FinishTrimmingFirst() override { Function_TrimmingType_(); }

	virtual void TrimmingPlatting() {};
	virtual void TrimmingPried() {};
	virtual void TrimmingMixer() {};
	virtual void TrimmingSteam() {};
	virtual void TrimmingBoil() {};

	void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override
	{
		Packet->IngredientData = Enum_IngredientType_;
	}


};

