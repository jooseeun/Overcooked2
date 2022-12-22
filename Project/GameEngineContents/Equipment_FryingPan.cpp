#include "PreCompile.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Plate.h"

Equipment_FryingPan::Equipment_FryingPan() 
	: FryFood_(nullptr)
{
}

Equipment_FryingPan::~Equipment_FryingPan() 
{
}

void Equipment_FryingPan::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::FryingPan);

	GetFBXMesh()->SetFBXMesh("m_sk_fryingpan_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

bool Equipment_FryingPan::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Cooker)
	{
		if (FryFood_ != nullptr)
		{
			if (FryFood_->Input_Auto(_DeltaTime, 12.f))
			{
				return true;
			}
		}
	}
	return false;

}

HoldDownEnum Equipment_FryingPan::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if (FryFood_ != nullptr)
	{
		if (FryFood_->GetPlatting())
		{
			if ((*_Moveable) == nullptr)
			{
				(*_Moveable) = FryFood_;
				FryFood_.reset();
				return HoldDownEnum::HoldDown;
			}
			else
			{
				std::shared_ptr<GamePlayMoveable> Food = FryFood_;
				if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
				{

					switch ((*_Moveable)->PickUp(&Food))
					{
					case HoldDownEnum::HoldDown:
						MsgBoxAssert("Equipment_FryingPan Error")
							break;
					case HoldDownEnum::HoldUp:
						FryFood_.reset();
					default:
						break;
					}
				}
				else
				{
					if ((*_Moveable)->CastThis<Equipment_Plate>() != nullptr)
					{
						switch ((*_Moveable)->PickUp(&Food))
						{
						case HoldDownEnum::HoldDown:
							MsgBoxAssert("Equipment_FryingPan Error")
								break;
						case HoldDownEnum::HoldUp:
							FryFood_.reset();
						default:
							break;
						}
					}
					else if ((*_Moveable)->CastThis<Equipment_FryingPan>() != nullptr)
					{
						std::weak_ptr<GamePlayFood> Index = (*_Moveable)->CastThis<Equipment_FryingPan>()->FryFood_;
						(*_Moveable)->CastThis<Equipment_FryingPan>()->SetFryFood(FryFood_);
						SetFryFood(Index.lock());
					}
				}
			}
		}
	}
	else
	{
		if ((*_Moveable) != nullptr)
		{
			std::weak_ptr<GamePlayFood> Food = (*_Moveable)->CastThis<GamePlayFood>();
			if (Food.lock() != nullptr)
			{
				if (Food.lock()->GetCookingType() == CookingType::Pried)
				{
					(*_Moveable) = nullptr;
					SetFryFood(Food.lock());
					return HoldDownEnum::HoldUp;
				}

				//const StageData& Data = GlobalGameData::GetCurStageRef();
				//FoodData FoodData_;

				//for (size_t i = 0; i < Data.StageRecipe.size(); i++)
				//{
				//	FoodData_ = GlobalGameData::GetFoodData(Data.StageRecipe[i]);
				//	for (size_t j = 0; j < FoodData_.Ingredient.size(); j++)
				//	{

				//	}
				//}
			}
			else
			{
				if ((*_Moveable)->CastThis<Equipment_FryingPan>() != nullptr)
				{
					std::weak_ptr<GamePlayFood> Index = (*_Moveable)->CastThis<Equipment_FryingPan>()->FryFood_;
					(*_Moveable)->CastThis<Equipment_FryingPan>()->SetFryFood(FryFood_);
					SetFryFood(Index.lock());
				}
			}
		}
		else
		{
			(*_Moveable) = CastThis<GamePlayMoveable>();
			return HoldDownEnum::HoldDown;
		}
		
	}
	return HoldDownEnum::Nothing;
}

