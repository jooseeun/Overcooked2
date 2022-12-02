#pragma once
#include "GamePlayEquipment.h"
#include "GamePlayFood.h"
#include "Enums.h"
#include "FoodThumbnail.h"

enum class ObjectBowlType
{
	None,
	Bowl,
	Pod,
	Plate,
	FryingPan,
	Steamer
};
struct CombinFood
{
	////GamePlayBowl& operator=(const GamePlayBowl& _Other)
	////{
	////	GamePlayBowl
	////}

	//bool AddFood(IngredientType _Food)
	//{
	//	for (size_t i = 0; i < Food_Current_.size(); i++)
	//	{
	//		if (GamePlayFood::SandwitchTest(_Food) == false)
	//		{
	//			return false;
	//		}
	//	}
	//	size_t i = 0;

	//	for (; i < Food_Current_.size(); i++)
	//	{
	//		if (Food_Current_[i] == IngredientType::None)
	//		{
	//			Food_Current_[i] = _Food;
	//			RefreshThumbnail();
	//			return true;
	//		}
	//		else
	//		{
	//			continue;
	//		}
	//	}


	//	if (i < 3)
	//	{
	//		Food_Current_.push_back(_Type);
	//		RefreshThumbnail();
	//		return true;
	//	}
	//}

	//void RefreshThumbnail()
	//{

	//}

	std::vector<IngredientType> Food_Current_;
	std::vector<std::shared_ptr<FoodThumbnail>> Food_Thumbnail_;
	std::shared_ptr<GamePlayMoveable> Moveable_;

};

class GamePlayBowl : public GamePlayEquipment
{
public:
	// constrcuter destructer
	GamePlayBowl();
	~GamePlayBowl();

	// delete Function
	GamePlayBowl(const GamePlayBowl& _Other) = delete;
	GamePlayBowl(GamePlayBowl&& _Other) noexcept = delete;
	GamePlayBowl& operator=(const GamePlayBowl& _Other) = delete;
	GamePlayBowl& operator=(GamePlayBowl&& _Other) noexcept = delete;

	inline ObjectBowlType GetObjectBowlType() const
	{
		if (Enum_ObjectBowlType_ == ObjectBowlType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayBowl::Enum_ObjectStuffType_ 설정)");
		}
		return Enum_ObjectBowlType_;
	}

protected:
	void Start() override;

	inline void SetObjectBowlType(ObjectBowlType _Type)
	{
		Enum_ObjectBowlType_ = _Type;
	}
private:
	ObjectBowlType Enum_ObjectBowlType_;
	std::shared_ptr<CombinFood> CombinFood_;

	//HoldDownEnum HoldUp(std::shared_ptr<GamePlayFood> _Food);
	//HoldDownEnum HoldUp(std::shared_ptr<GamePlayBowl> _Bowl);

	void CheckCombinFood();

};

