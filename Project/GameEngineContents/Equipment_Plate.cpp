#include "PreCompile.h"
#include "Equipment_Plate.h"
#include "GlobalGameData.h"

Equipment_Plate::Equipment_Plate()
	: Dirty_(false)
	, Pile_Plate_(nullptr)
	, Washing_(false)
{
}

Equipment_Plate::~Equipment_Plate() 
{
}

void Equipment_Plate::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Plate);
	GamePlayMoveable::SetObjectMoveableType(ObjectMoveableType::Dish);
	GamePlayBowl::SetObjectBowlType(ObjectBowlType::Plate);

	GetFBXMesh()->SetFBXMesh("m_sk_plate_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetCollisionObject()->GetTransform().SetWorldPosition({ 0, -25, 0});
	GetCollisionObject()->GetTransform().SetLocalScale({ 100, 25, 100 });

	GetCombinFood()->Start(0, shared_from_this(), {0 , 15, 0});
	GetCookingBar()->SetOver(false);
	//SetDirty();
}

void Equipment_Plate::SetDirty()
{
	Dirty_ = true;
	ChangeFBXMesh();
	GetFBXMesh()->SetFBXMesh("m_sk_plate_dirty.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	ReSetCookingGage();
	// 텍스쳐 변경필요
}

void Equipment_Plate::SetClean()
{
	Dirty_ = false;
	ChangeFBXMesh();
	GetFBXMesh()->SetFBXMesh("m_sk_plate_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	ReSetCookingGage();
	// 텍스쳐 변경필요
}

HoldDownEnum Equipment_Plate::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		if (Pile_Plate_ != nullptr)
		{
			return HoldDownEnum::Nothing;
		}

		if (Dirty_ == true || Pile_Plate_ != nullptr)
		{
			return HoldDownEnum::Nothing;
		}
		std::weak_ptr<GamePlayFood> Food = (*_Moveable)->CastThis<GamePlayFood>();
		if (Food.lock() != nullptr)
		{
			if (Food.lock()->GetPlatting())
			{
				if (GetCombinFood()->AddFood(Food.lock()->GetObjectFoodClass()))
				{
					Food.lock()->GetFoodThumbnail()->Off();
					Food.lock()->DetachObject();
					(*_Moveable)->GetCollisionObject()->Off();
					(*_Moveable)->GetFBXMesh()->Off();
					(*_Moveable)->GetTransform().SetWorldPosition({ 10000,10000,10000 });
					(*_Moveable)->Off();
					(*_Moveable) = nullptr;
					return HoldDownEnum::HoldUp;
				}
				else
				{
					return HoldDownEnum::Nothing;
				}
			}
		}
		else
		{
			if((*_Moveable)->CastThis<Equipment_Plate>() != nullptr)
			{
				if (!(GetCombinFood()->AddFood((*_Moveable)->CastThis<Equipment_Plate>()->GetCombinFood())))
				{
					(*_Moveable)->CastThis<Equipment_Plate>()->GetCombinFood()->Switching(GetCombinFood());
				}
			}
			else if ((*_Moveable)->CastThis<GamePlayBowl>() != nullptr)
			{
				std::shared_ptr<GamePlayMoveable> Moveable = CastThis<GamePlayMoveable>();
				(*_Moveable)->PickUp(&Moveable);
			}
		}
	}
	else
	{
		(*_Moveable) = GetPlate();
		if ((*_Moveable) == CastThis<Equipment_Plate>())
		{
			return HoldDownEnum::HoldDown;
		}
		else if ((*_Moveable) == Pile_Plate_)
		{
			Pile_Plate_ = nullptr;
		}
		return HoldDownEnum::HoldUp;
	}
	return HoldDownEnum::Nothing;
}

//HoldDownEnum Equipment_Plate::HoldOn(std::shared_ptr<Player> _Player) 
//{
//	if (_Player->GetPlayerHolding() == nullptr)
//	{
//		_Player->SetPlayerHolding(shared_from_this());
//		return HoldDownEnum::HoldUp;
//	}
//	else
//	{
//		if (_Player->GetPlayerHolding()->CastThis<GamePlayFood>() != nullptr)
//		{
//			IngredientType Type = _Player->GetPlayerHolding()->CastThis<GamePlayFood>()->GetObjectFoodClass();
//			for (size_t i = 0; i < GetCombinFood()->Food_Current_.size(); i++)
//			{
//				if (GetCombinFood()->Food_Current_[i] == IngredientType::None)
//				{
//					continue;
//				}
//				else if(GamePlayFood::CheckCombine(GetCombinFood()->Food_Current_[i], Type) == ReturnMix::NoMix)
//				{
//					return HoldDownEnum::Nothing;
//				}
//			}
//			if (!GetCombinFood()->PushFood(Type))
//			{
//				return HoldDownEnum::Nothing;
//			}
//			_Player->DetachPlayerHolding();
//			return HoldDownEnum::HoldDown;
//		}
//		else if (_Player->GetPlayerHolding()->CastThis<GamePlayBowl>() != nullptr)
//		{
//			MsgBoxAssert("아직")
//		}
//		else
//		{
//			return HoldDownEnum::Nothing;
//		}
//		return HoldDownEnum::Nothing;
//	}
//}
//
//HoldDownEnum Equipment_Plate::PickUp(std::shared_ptr<GamePlayMoveable> _Moveable)
//{

//
//	return HoldDownEnum::Nothing;
//}
//


//Input_PutDownOption Equipment_Plate::Input_PutDown(std::shared_ptr<GamePlayMoveable> _Object)
//{
//	if (Dirty_ == true)
//	{
//		if (_Object->GetToolInfoType() == ToolInfo::Plate &&
//			std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
//		{
//			std::shared_ptr<Equipment_Plate> Pile_Plate_Before = nullptr; // 방어코드
//			std::shared_ptr<Equipment_Plate> Pile_Plate = std::dynamic_pointer_cast<Equipment_Plate>(shared_from_this());
//
//			int Stack = 0;
//			while (true)
//			{
//				if (Stack > 10)
//				{
//					MsgBoxAssert("무한 루프입니다")
//				}
//				if (Pile_Plate->Pile_Plate_ != nullptr)
//				{
//					Pile_Plate_Before = Pile_Plate;
//					Pile_Plate = Pile_Plate->Pile_Plate_;
//					if (Pile_Plate_Before == Pile_Plate)
//					{ 
//						MsgBoxAssert("무한 루프입니다")
//					}
//
//				}
//				else
//				{
//					Pile_Plate->Pile_Plate_ = std::dynamic_pointer_cast<Equipment_Plate>(_Object);
//					return Input_PutDownOption::PutDown;
//					break;
//				}
//				Stack++;
//			}
//		}
//	}
//	else
//	{
//		// 음식 조합
//	}
//
//	return Input_PutDownOption::NoResponse; // 수정요
//}
//
//Input_PickUpOption Equipment_Plate::Input_PickUp(std::shared_ptr<Player> _Player)
//{
//	if (Washing_ == true)
//	{
//		return Input_PickUpOption::NoResponse;
//	}
//	return Input_PickUpOption::PickUp;
//}

