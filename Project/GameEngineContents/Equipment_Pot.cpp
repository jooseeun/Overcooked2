#include "PreCompile.h"
#include "Equipment_Pot.h"

Equipment_Pot::Equipment_Pot() 
{
}

Equipment_Pot::~Equipment_Pot() 
{
}

void Equipment_Pot::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Pot);

	GetFBXMesh()->SetFBXMesh("m_sk_pot_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}


CombineType Equipment_Pot::CombineThis(std::shared_ptr<GamePlayFood> _Food)
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
