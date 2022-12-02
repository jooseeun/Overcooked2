#include "PreCompile.h"
#include "Equipment_Plate.h"

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
}

void Equipment_Plate::SetDirty()
{
	Dirty_ = true;
	// �ؽ��� �����ʿ�
}

void Equipment_Plate::SetClean()
{
	Dirty_ = false;
	// �ؽ��� �����ʿ�
}


CombineType Equipment_Plate::CombineThis(std::shared_ptr<GamePlayFood> _Food)
{
	switch (_Food->GetObjectFoodClass())
	{
	case IngredientType::None:
		break;
	case IngredientType::Tomato:
		break;
	case IngredientType::Onion:
		break;
	case IngredientType::Potato:
		break;
	case IngredientType::Dough:
		break;
	case IngredientType::Seaweed:
		break;
	case IngredientType::Mushroom:
		break;
	case IngredientType::Meat:
		break;
	case IngredientType::Lettuce:
		break;
	case IngredientType::Rice:
		break;
	case IngredientType::Flourbread:
		break;
	case IngredientType::Bread:
		break;
	case IngredientType::Fish:
		break;
	case IngredientType::Sausage:
		break;
	case IngredientType::DumplingSkin:
		break;
	case IngredientType::Egg:
		break;
	case IngredientType::Chicken:
		break;
	case IngredientType::Burrito:
		break;
	case IngredientType::Cheese:
		break;
	case IngredientType::Carrot:
		break;
	case IngredientType::Chocolate:
		break;
	case IngredientType::Honey:
		break;
	case IngredientType::PastaNoodles:
		break;
	case IngredientType::Prawn:
		break;
	case IngredientType::Cucumber:
		break;
	default:
		break;
	}

	return CombineType::NoRespon;
}

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

