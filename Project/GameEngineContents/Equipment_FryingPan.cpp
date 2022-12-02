#include "PreCompile.h"
#include "Equipment_FryingPan.h"

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

	GetFBXMesh()->SetFBXMesh("m_sk_fryingpan_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

CombineType Equipment_FryingPan::CombineThis(std::shared_ptr<GamePlayFood> _Food)
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