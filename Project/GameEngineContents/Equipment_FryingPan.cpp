#include "PreCompile.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Plate.h"

Equipment_FryingPan::Equipment_FryingPan() 
{
}

Equipment_FryingPan::~Equipment_FryingPan() 
{
}

void Equipment_FryingPan::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::FryingPan);
	GamePlayBowl::SetObjectBowlType(ObjectBowlType::Bowl);

	GetFBXMesh()->SetFBXMesh("m_sk_fryingpan_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Equipment_FryingPan::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	if (MyMoveableState_ == MoveableState::Cooking)
	{
		if (GetParent() != nullptr && GetParent()->CastThis<Player>() != nullptr)
		{
			MyMoveableState_ = MoveableState::Idle;
			IsSound_ = false;
			ObjSoundPlayer_.Stop();
		}
	}
}

bool Equipment_FryingPan::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Cooker)
	{
		if(!GetCombinFood()->IsClear())
		{
			if (false == IsSound_)
			{
				MyMoveableState_ = MoveableState::Cooking;
				ObjSoundPlayer_ = GameEngineSound::SoundPlayControl("FryingPanSizzle.wav", -1);
				ObjSoundPlayer_.Volume(2.f);
				IsSound_ = true;
			}
			if (Input_Auto(_DeltaTime, 12.f))
			{
				return true;
			}
		}
	}

	return false;

}

HoldDownEnum Equipment_FryingPan::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
		{
			if ((*_Moveable)->CastThis<GamePlayFood>()->GetCookingType() == CookingType::Pried && (*_Moveable)->CastThis<GamePlayFood>()->GetTrim())
			{
				if (GetCombinFood()->AddFood((*_Moveable)->CastThis<GamePlayFood>()->GetObjectFoodClass()))
				{
					(*_Moveable)->Death();
					(*_Moveable)->Off();
					(*_Moveable) = nullptr;
					return HoldDownEnum::HoldUp;
				}
			}

		}
		else if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Bowl)
		{
			std::weak_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
			if (Bowl.lock()->GetCombinFood()->GetFoodType() != FoodType::None)
			{
				BowltoBowl(Bowl.lock());
			}
		}
		else if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Dish && GetCombinFood()->GetTrim())
		{
			std::weak_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
			Bowl.lock()->GetCombinFood()->AddFood(GetCombinFood());
			//(*_Moveable)->CastThis<GamePlayBowl>()->GetCombinFood()->Move(GetCombinFood());
			//switch ((*_Moveable)->PickUp(&Food))
			//{
			//case HoldDownEnum::HoldDown:
			//	MsgBoxAssert("Equipment_FryingPan Error")
			//		break;
			//case HoldDownEnum::HoldUp:
			//	FryFood_.reset();
			//default:
			//	break;
			//}
		}
	}
	else
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		MyMoveableState_ = MoveableState::Idle;
		IsSound_ = false;
		return HoldDownEnum::HoldDown;
	}
	//	std::shared_ptr<GamePlayMoveable> Food;
	//	if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
	//	{
	//		switch ((*_Moveable)->PickUp(&Food))
	//		{
	//		case HoldDownEnum::HoldDown:
	//			MsgBoxAssert("Equipment_FryingPan Error")
	//				break;
	//		case HoldDownEnum::HoldUp:
	//			FryFood_.reset();
	//		default:
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		if ((*_Moveable)->CastThis<GamePlayEquipment>()->GetObjectEquipmentType() == ObjectEquipmentType::Dish)
	//		{

	//		}
	//		else if ((*_Moveable)->CastThis<Equipment_FryingPan>() != nullptr)
	//		{
	//			std::weak_ptr<GamePlayFood> Index = (*_Moveable)->CastThis<Equipment_FryingPan>()->FryFood_;
	//			(*_Moveable)->CastThis<Equipment_FryingPan>()->SetFryFood(FryFood_);
	//			SetFryFood(Index.lock());
	//		}
	//	}
	//}
	//

	//if ((*_Moveable) != nullptr)
	//{
	//	std::weak_ptr<GamePlayFood> Food = (*_Moveable)->CastThis<GamePlayFood>();
	//	if (Food.lock() != nullptr)
	//	{
	//		if (Food.lock()->GetCookingType() == CookingType::Pried)
	//		{
	//			(*_Moveable) = nullptr;
	//			SetFryFood(Food.lock());
	//			return HoldDownEnum::HoldUp;
	//		}

	//		//const StageData& Data = GlobalGameData::GetCurStageRef();
	//		//FoodData FoodData_;

	//		//for (size_t i = 0; i < Data.StageRecipe.size(); i++)
	//		//{
	//		//	FoodData_ = GlobalGameData::GetFoodData(Data.StageRecipe[i]);
	//		//	for (size_t j = 0; j < FoodData_.Ingredient.size(); j++)
	//		//	{

	//		//	}
	//		//}
	//	}
	//	else
	//	{
	//		if ((*_Moveable)->CastThis<Equipment_FryingPan>() != nullptr)
	//		{
	//			std::weak_ptr<GamePlayFood> Index = (*_Moveable)->CastThis<Equipment_FryingPan>()->FryFood_;
	//			(*_Moveable)->CastThis<Equipment_FryingPan>()->SetFryFood(FryFood_);
	//			SetFryFood(Index.lock());
	//		}
	//		else if ((*_Moveable)->CastThis<GamePlayBowl>() != nullptr)
	//		{
	//			std::weak_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
	//			if (Bowl.lock()->GetCombinFood()->GetFoodType() != FoodType::None)
	//			{
	//				BowltoFryingPan(Bowl.lock());
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	(*_Moveable) = CastThis<GamePlayMoveable>();
	//	return HoldDownEnum::HoldDown;
	//}
	//	
	//
	return HoldDownEnum::Nothing;
}

