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

	GetFBXMesh()->SetFBXMesh("m_sk_plate_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetCollisionObject()->GetTransform().SetWorldPosition({ 0, -25, 0});
	GetCollisionObject()->GetTransform().SetLocalScale({ 100, 25, 100 });

	GetCombinFood()->Start(1, shared_from_this(), false);
	GetCookingBar()->SetOver(false);
	SetDirty();
}

void Equipment_Plate::SetDirty()
{
	Dirty_ = true;
	ChangeFBXMesh();
	GetFBXMesh()->SetFBXMesh("m_sk_plate_dirty.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	ReSetCookingGage();
	// �ؽ��� �����ʿ�
}

void Equipment_Plate::SetClean()
{
	Dirty_ = false;
	ChangeFBXMesh();
	GetFBXMesh()->SetFBXMesh("m_sk_plate_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	ReSetCookingGage();
	// �ؽ��� �����ʿ�
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
			const StageData& Data = GlobalGameData::GetCurStageRef();
			FoodData FoodData_;

			for (size_t i = 0; i < Data.StageRecipe.size(); i++)
			{
				FoodData_ = GlobalGameData::GetFoodData(Data.StageRecipe[i]);
				for (size_t j = 0; j < FoodData_.Ingredient.size(); j++)
				{
					if (FoodData_.Ingredient[j] == Food.lock()->GetObjectFoodClass())
					{
						if (Food.lock()->GetPlatting())
						{
							GetCombinFood()->PushFood(Food.lock()->GetObjectFoodClass());
							//GetCombinFood()->SetRenderer(*_Moveable);

							(*_Moveable)->Death();
							(*_Moveable)->Off();
							(*_Moveable) = nullptr;

							return HoldDownEnum::HoldUp;
						}
					}
				}
			}
		}
		else
		{
		
			if ((*_Moveable)->CastThis<GamePlayEquipment>()->GetObjectEquipmentType() == ObjectEquipmentType::Bowl)
			{
				std::shared_ptr<GamePlayMoveable> Moveable = CastThis<GamePlayMoveable>();
				switch ((*_Moveable)->PickUp(&Moveable))
				{
				case HoldDownEnum::HoldDown:
					return  HoldDownEnum::HoldUp;
					break;
				default:
					return HoldDownEnum::Nothing;
					break;
				}
			}
			else if((*_Moveable)->CastThis<GamePlayEquipment>()->GetObjectEquipmentType() == ObjectEquipmentType::Dish)
			{

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
//			MsgBoxAssert("����")
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
//			std::shared_ptr<Equipment_Plate> Pile_Plate_Before = nullptr; // ����ڵ�
//			std::shared_ptr<Equipment_Plate> Pile_Plate = std::dynamic_pointer_cast<Equipment_Plate>(shared_from_this());
//
//			int Stack = 0;
//			while (true)
//			{
//				if (Stack > 10)
//				{
//					MsgBoxAssert("���� �����Դϴ�")
//				}
//				if (Pile_Plate->Pile_Plate_ != nullptr)
//				{
//					Pile_Plate_Before = Pile_Plate;
//					Pile_Plate = Pile_Plate->Pile_Plate_;
//					if (Pile_Plate_Before == Pile_Plate)
//					{ 
//						MsgBoxAssert("���� �����Դϴ�")
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
//		// ���� ����
//	}
//
//	return Input_PutDownOption::NoResponse; // ������
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

