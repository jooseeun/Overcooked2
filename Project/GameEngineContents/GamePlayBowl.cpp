#include "PreCompile.h"
#include "GamePlayBowl.h"
#include "GamePlayFood.h"

GamePlayBowl::GamePlayBowl() 
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

HoldDownEnum GamePlayBowl::HoldDown(std::shared_ptr<Player> _Player)
{
	if (_Player->GetPlayerHolding() != nullptr)
	{
		if (std::dynamic_pointer_cast<GamePlayMoveable>(_Player->GetPlayerHolding())->GetObjectMoveableType() == ObjectMoveableType::Food)
		{
			IngredientType Class = std::dynamic_pointer_cast<GamePlayFood>(_Player->GetPlayerHolding())->GetObjectFoodClass();

			if (IsCanCombin(Class))
			{
				for (size_t i = 0; i < CombinFood_->Food_Current_.size(); i++)
				{
					if (CombinFood_->Food_Current_[i] == IngredientType::None)
					{
						CombinFood_->Food_Current_[i] = Class;
						//RefreshFoodThumbnail();
						return HoldDownEnum::HoldDown;
					}
				}
			}
			return HoldDownEnum::Nothing;
		}
		else
		{
			return HoldDownEnum::Nothing;
		}
	}
	else
	{
		return HoldDownEnum::HoldUp;
	}
}
//
//void GamePlayBowl::RefreshFoodThumbnail()
//{
//	int Index = 0;
//	for (auto Food : CombinFood_->Food_Current_)
//	{
//		if (Food == IngredientType::None)
//		{
//			Index
//		}
//		 
//	}
//	
//	for (size_t i = 0; i < CombinFood_->Food_Current_.size(); i++)
//	{
//		CombinFood_->Food_Thumbnail_[i]->LinkObject(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()), {0, 0, 0});
//		CombinFood_->Food_Thumbnail_[i]->SetThumbnail(IngredientType::None);
//	}
//}