#include "PreCompile.h"
#include "Equipment_Bowl.h"

Equipment_Bowl::Equipment_Bowl() 
{
}

Equipment_Bowl::~Equipment_Bowl() 
{
}

void Equipment_Bowl::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Bowl);

	GetFBXMesh()->SetFBXMesh("Bowl_Static.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 1, 1, 1 });

	//GetAnimationFBXMesh()->SetFBXMesh("m_cakemixer_Bowl_01.fbx", "TextureAnimation");
	//GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	//GameEngineRenderingEvent Event;
	//Event.ResourcesName = "m_cakemixer_Bowl_01.FBX";
	//Event.Loop = true;
	//Event.Inter = 0.1f;
	//GetAnimationFBXMesh()->CreateFBXAnimation("Idle", Event, 1);

	//GetAnimationFBXMesh()->ChangeAnimation("Idle");
}

void Equipment_Bowl::Update(float _DeltaTime)
{
}

CombineType Equipment_Bowl::CombineThis(std::shared_ptr<GamePlayFood> _Food)
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