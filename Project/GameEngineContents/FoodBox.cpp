#include "PreCompile.h"
#include "FoodBox.h"
#include "FoodHeader.h"

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
	std::dynamic_pointer_cast<Tool_FoodBox>(GetStuff())->Type_ = _Type;

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

HoldDownEnum Tool_FoodBox::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	switch (GamePlayTool::PickUp(_Moveable))
	{
	case HoldDownEnum::Nothing:
	{
		(*_Moveable) = GamePlayFood::GetIngredientClass(Type_);

		if (nullptr != ServerInitManager::Net)
		{
			(*_Moveable)->DontWantSend();
			if (ServerInitManager::Net->GetIsHost())
			{
				(*_Moveable)->ClientInit(ServerObjectType::Object, GamePlayObject::FindEmptyServerNumber());
			}
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


//HoldDownEnum Tool_FoodBox::HoldOn(std::shared_ptr<Player> _Player)
//{
//	if (GetCurrentMoveable() == nullptr)
//	{
//		if (_Player->GetPlayerHolding() == nullptr)
//		{
//		
//
//			return HoldDownEnum::HoldUp;
//		}
//		
//	}
//	else
//	{
//		if (_Player->GetPlayerHolding() == nullptr)
//		{
//			_Player->SetPlayerHolding(GetCurrentMoveable());
//			ReSetCurrentMoveable();
//			return HoldDownEnum::HoldUp;
//		}
//	}
//	return HoldDownEnum::Nothing;
//}

//Input_PickUpOption Tool_FoodBox::CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object)
//{
//	return Input_PickUpOption::PickUp;
//}
//
//Input_PickUpOption Tool_FoodBox::Input_PickUp(std::shared_ptr<Player> _Player)
//{

//	return Input_PickUpOption::Exception;
//}
//
//Input_AutoOption Tool_TrashCan::Input_Action()
//{
//	return Input_AutoOption::NoResponse;
//}