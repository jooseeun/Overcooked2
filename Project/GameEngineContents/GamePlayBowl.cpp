#include "PreCompile.h"
#include "GamePlayBowl.h"
#include "GamePlayFood.h"

std::map<NoneFoodType, std::vector<IngredientType>> CombinFood::Static_NoneType_;

GamePlayBowl::GamePlayBowl() 
	: Enum_ObjectBowlType_(ObjectBowlType::None)
	, CombinFood_(nullptr)
{
}

GamePlayBowl::~GamePlayBowl() 
{	
}

void GamePlayBowl::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetObjectEquipmentType(ObjectEquipmentType::Bowl);
}


//
//HoldDownEnum GamePlayBowl::HoldOn(std::shared_ptr<Player> _Player)
//{
//	if (_Player->GetPlayerHolding() == nullptr)
//	{
//		_Player->SetPlayerHolding(shared_from_this());
//		return HoldDownEnum::HoldUp;
//	}
//	else
//	{
//		if (_Player->GetPlayerHolding()->CastThis<GamePlayMoveable>()->GetObjectMoveableType() == ObjectMoveableType::Equipment)
//		{
//			if (_Player->GetPlayerHolding()->CastThis<GamePlayEquipment>()->GetObjectEquipmentType() == ObjectEquipmentType::Using)
//			{
//				return HoldDownEnum::Nothing;
//			}
//			else
//			{
//				if (_Player->GetPlayerHolding()->CastThis<GamePlayBowl>()->GetObjectBowlType() == ObjectBowlType::)
//				{
//
//				}
//				return HoldDownEnum::Nothing;
//			}
//		}
//		else
//		{
//			switch (GamePlayFood::CheckCombine(_Player->GetPlayerHolding()->CastThis<GamePlayFood>()->GetObjectFoodClass(), ))
//			{
//			case ReturnMix::NoMix:
//				break;
//			case ReturnMix::AtoB:
//				break;
//			case ReturnMix::BtoA:
//				break;
//			default:
//				break;
//			}
//		}
//		return HoldDownEnum::Nothing;
//	}
//};