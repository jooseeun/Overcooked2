#include "PreCompile.h"
#include "FoodBox.h"
#include "FoodHeader.h"
#include "Food_Empty.h"

std::map<IngredientType, std::queue<std::shared_ptr<GamePlayFood>>> Tool_FoodBox::map_FoodQueue_;
//std::map<IngredientType, std::deque<std::shared_ptr<GamePlayFood>>> Tool_FoodBox::map_FoodDeque_;

FoodBox::FoodBox()
	: IsOpen_(false)
	, IsInteraction_(false)
	, Angle_(0.f)
	, Renderer_(nullptr)
	, LidRenderer_(nullptr)
	, Lid_(nullptr)
	, Type_(FoodBoxType::Max)
{
}

FoodBox::~FoodBox()
{
}

void FoodBox::SetFoodBoxMesh(FoodBoxType _Type)
{
	std::string Name = "";

	switch (_Type)
	{
	case FoodBoxType::Normal:
	{
		Name = "CreateBox.fbx";
		
	}
		break;
	case FoodBoxType::Winter:
	{
		Name = "CreateBox2.fbx";
	}
		break;
	default:
		break;
	}

	LidRenderer_->SetFBXMesh(Name, "Texture", 1);
	LidRenderer_->GetTransform().SetWorldScale({ 120, 100, 120 });
	LidRenderer_->GetTransform().SetWorldMove({ 0, 0.f, -55.f });

	GetFBXMesh()->SetFBXMesh(Name, "Texture", 0);
	GetFBXMesh()->GetTransform().SetWorldScale({ 120, 100, 120 });
}

void FoodBox::SetFoodType(IngredientType _Type)
{
	std::dynamic_pointer_cast<Tool_FoodBox>(GetStuff())->SetFoodType(_Type);

	switch (_Type)
	{
	case IngredientType::Tomato:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 0);
		break;
	case IngredientType::Onion:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 1);
		break;
	case IngredientType::Potato:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 2);
		break;
	case IngredientType::Dough:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 3);
		break;
	case IngredientType::Seaweed:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 4);
		break;
	case IngredientType::Mushroom:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 5);
		break;
	case IngredientType::Meat:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 6);
		break;
	case IngredientType::Lettuce:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 7);
		break;
	case IngredientType::Rice:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 8);
		break;
	case IngredientType::Flour:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 9);

		break;
	case IngredientType::Bread:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 10);

		break;
	case IngredientType::Fish:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 11);

		break;
	case IngredientType::Sausage:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 12);

		break;
	case IngredientType::DumplingSkin:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 13);
		break;
	case IngredientType::Egg:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 14);
		break;
	case IngredientType::Chicken:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 15);
		break;
	case IngredientType::Burrito:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 16);
		break;
	case IngredientType::Cheese:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 17);
		break;
	case IngredientType::Carrot:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 18);
		break;
	case IngredientType::Chocolate:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 19);
		break;
	case IngredientType::Honey:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 20);
		break;
	case IngredientType::PastaNoodles:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 21);
		break;
	case IngredientType::Prawn:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 22);
		break;
	case IngredientType::Cucumber:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 23);
		break;
	case IngredientType::Orange:
		Renderer_->SetTexture("t_sk_crate_lid_images_dlc03.png", 1);
		break;
	case IngredientType::DriedFruit:
		Renderer_->SetTexture("t_sk_crate_lid_images_dlc03.png", 0);
		break;
	case IngredientType::Strawberry:
		Renderer_->SetTexture("t_sk_crate_lid_images_dlc02.png", 2);
		break;
	case IngredientType::Blueberry:
		Renderer_->SetTexture("t_sk_crate_lid_images_dlc08.png", 11);
		break;
	default:
		break;
	}
}

void FoodBox::Start()
{
	GamePlayStaticObject::Start();

	Lid_ = GetLevel()->CreateActor<GameEngineActor>();
	Lid_->SetParent(shared_from_this());
	Lid_->GetTransform().SetWorldMove({ 0, 0.f, 50.f });

	std::shared_ptr<GameEngineCollision> Collision_Object_ = Lid_->CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0, 0.5f });
	Collision_Object_->ChangeOrder(CollisionOrder::Object_None);
	LidRenderer_ = Lid_->CreateComponent<GameEngineFBXStaticRenderer>();

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	Renderer_ = Lid_->CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalMove({ 0.f, 43.f, -55.f });
	Renderer_->GetTransform().SetLocalRotation({ 90.f, 0.f });
	Renderer_->GetTransform().SetWorldScale({ 60, 60 });
	Renderer_->GetTransform().PixLocalNegativeX();

	std::shared_ptr<Tool_FoodBox> FoodBoxTool = GetLevel()->CreateActor<Tool_FoodBox>();
	SetStuff(FoodBoxTool);
	FoodBoxTool->SetFoodBox(CastThis<FoodBox>());
}

void FoodBox::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	if (true == IsInteraction_)
	{
		if (false == IsOpen_)
		{
			Angle_ += _DeltaTime * 50.f;

			Lid_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });

			if (45.f <= Angle_)
			{
				IsOpen_ = true;
			}
		}

		if (true == IsOpen_)
		{
			Angle_ -= _DeltaTime * 50.f;
			Lid_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });

			if (0.f >= Angle_)
			{
				Angle_ = 0.f;
				IsInteraction_ = false;	//
				IsOpen_ = false;
			}
		}
	}
}

Tool_FoodBox::Tool_FoodBox()
	: Type_(IngredientType::None)
{
}

Tool_FoodBox::~Tool_FoodBox()
{
}

void Tool_FoodBox::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::FoodBox);
}

void Tool_FoodBox::SetFoodType(IngredientType _Type)
{
	Type_ = _Type;

	if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
	{
		Queue_FillFood(Type_);
		Queue_FillFood(Type_);
	}
}

void Tool_FoodBox::Queue_FillFood(IngredientType _Type) // Static
{
	std::shared_ptr<GamePlayFood> Food = GamePlayFood::GetIngredientClass(_Type);
	//Food->GetTransform().SetWorldPosition({ 10000,10000, 10000 });
	Food->Off();
	Food->ServerStart();
	map_FoodQueue_[_Type].push(Food);
}

//void Tool_FoodBox::Deque_FillFood(IngredientType _Type) // Static
//{
//	std::shared_ptr<GamePlayFood> Food = GamePlayFood::GetIngredientClass(_Type);
//	//Food->GetTransform().SetWorldPosition({ 10000,10000, 10000 });
//	Food->Off();
//	map_FoodDeque_[_Type].push_back(Food);
//}

std::shared_ptr<GamePlayFood> Tool_FoodBox::Queue_GetFood(IngredientType _Type)
{
	std::shared_ptr<GamePlayFood> Food = map_FoodQueue_[_Type].front();
	Food->On();
	map_FoodQueue_[_Type].pop();
	Queue_FillFood(_Type);
	return Food;
}

//void Tool_FoodBox::Deque_ServerInit(IngredientType _Type, int _NetID)
//{
//	map_FoodDeque_[_Type].front()->ClientInit(ServerObjectType::Object, _NetID);
//	map_FoodQueue_[_Type].push(map_FoodDeque_[_Type].front());
//	map_FoodDeque_[_Type].pop_front();
//
//	//MsgBoxAssert("Tool_FoodBox::Deque_ServerInit / 오류 확인용")
//	return;
//
//}

HoldDownEnum Tool_FoodBox::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	switch (GamePlayTool::PickUp(_Moveable))
	{
	case HoldDownEnum::Nothing:
	{
		if (nullptr != ServerInitManager::Net)
		{
	
			(*_Moveable) = Tool_FoodBox::Queue_GetFood(Type_);
			//(*_Moveable)->ClientInit(ServerObjectType::Object, GamePlayObject::FindEmptyServerNumber());
			
			//else
			//{
			//	(*_Moveable) = GetLevel()->CreateActor<Food_Empty>();
			//}
		}

		Box_.lock()->SwitchIsInteraction();
		return HoldDownEnum::HoldDown;
	}
		break;
	case HoldDownEnum::HoldUp:
		return HoldDownEnum::HoldUp;
		break;
	case HoldDownEnum::HoldDown:
		return  HoldDownEnum::HoldDown;
		break;
		break;
	default:
		break;
	}
	return HoldDownEnum::Nothing;
}

void Tool_FoodBox::LevelEndEvent()
{
	map_FoodQueue_.clear();
}