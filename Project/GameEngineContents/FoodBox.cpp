#include "PreCompile.h"
#include "FoodBox.h"
#include "FoodHeader.h"


FoodBox::FoodBox() 
	: IsOpen_(false)
    , IsInteraction_(false)
	, Angle_(0.f)
	, Renderer_(nullptr)
{
}

FoodBox::~FoodBox() 
{
}

void FoodBox::SetFoodType(FoodType _Type)
{
	std::dynamic_pointer_cast<Tool_FoodBox>(GetStuff())->Type_ = _Type;

	switch (_Type)
	{
	case FoodType::Tomato:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 0);
		break;
	case FoodType::Onion:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 1);
		break;
	case FoodType::Potato:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 2);
		break;
	case FoodType::Dough:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 3);
		break;
	case FoodType::Seaweed:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 4);
		break;
	case FoodType::Mushroom:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 5);
		break;
	case FoodType::Meat:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 6);
		break;
	case FoodType::Lettuce:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 7);
		break;
	case FoodType::Rice:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 8);
		break;
	case FoodType::Flour:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 9);

		break;
	case FoodType::Bread:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 10);

		break;
	case FoodType::Fish:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 11);

		break;
	case FoodType::Sausage:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 12);

		break;
	case FoodType::DumplingSkin:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 13);
		break;
	case FoodType::Egg:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 14);
		break;
	case FoodType::Chicken:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 15);
		break;
	case FoodType::Burrito:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 16);
		break;
	case FoodType::Cheese:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 17);
		break;
	case FoodType::Carrot:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 18);
		break;
	case FoodType::Chocolate:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 19);
		break;
	case FoodType::Honey:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 20);
		break;
	case FoodType::PastaNoodles:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 21);
		break;
	case FoodType::Prawn:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 22);
		break;
	case FoodType::Cucumber:
		Renderer_->SetTexture("t_sk_crate_lid_images.png", 23);
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

	std::shared_ptr<GameEngineFBXStaticRenderer> LidRenderer = Lid_->CreateComponent<GameEngineFBXStaticRenderer>();
	LidRenderer->SetFBXMesh("CreateBox.fbx", "Texture", 1);
	LidRenderer->GetTransform().SetWorldScale({ 120, 100, 120 });
	LidRenderer->GetTransform().SetWorldMove({0, 0.f, -55.f});

	std::shared_ptr<GameEngineCollision> Collision_Object_ = Lid_->CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0, 0.5f });
	Collision_Object_->ChangeOrder(CollisionOrder::Object_None);

	GetFBXMesh()->SetFBXMesh("CreateBox.fbx", "Texture", 0);
	GetFBXMesh()->GetTransform().SetWorldScale({ 120, 100, 120 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	Renderer_ = Lid_->CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalMove({ 0.f, 43.f, -55.f });
	Renderer_->GetTransform().SetLocalRotation({ 90.f, 0.f });
	Renderer_->GetTransform().SetWorldScale({ 60, 60 });
	Renderer_->GetTransform().PixLocalNegativeX();

	SetStuff(GetLevel()->CreateActor<Tool_FoodBox>());
}

void FoodBox::Update(float _DeltaTime)
{ 
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
				IsInteraction_ = false;
				IsInteraction_ = false;
				IsOpen_ = false;
			}
		}
	}
}

Tool_FoodBox::Tool_FoodBox()
{
}

Tool_FoodBox::~Tool_FoodBox()
{
}

void Tool_FoodBox::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	//SetCookingEndTime(1.f);
	//GamePlayTool::SetToolInfoType(ToolInfo::TrashCan);
}
//
//void Tool_TrashCan::Input_ActionToAuto_Update(std::shared_ptr<GamePlayMoveable> _Moveable, float _DeltaTime)
//{
//	_Moveable->PlusCookingTime(_DeltaTime);
//	// 돌면서 작아지는 기능
//}
//
//void Tool_TrashCan::Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable)
//{
//	_Moveable->Death();// 삭제한다
//	ReSetCurrentMoveable();
//}


Input_PickUpOption Tool_FoodBox::CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object)
{
	return Input_PickUpOption::PickUp;
}

Input_PickUpOption Tool_FoodBox::Input_PickUp(std::shared_ptr<Player> _Player)
{
	switch (Type_)
	{
	case FoodType::Onion:
		break;
	case FoodType::Potato:
		break;
	case FoodType::Dough:
		break;
	case FoodType::Seaweed:
		break;
	case FoodType::Mushroom:
		break;
	case FoodType::Meat:
		break;
	case FoodType::Lettuce:
		break;
	case FoodType::Rice:
		break;
	case FoodType::Flour:
		break;
	case FoodType::Bread:
		break;
	case FoodType::Fish:
		break;
	case FoodType::Sausage:
		break;
	case FoodType::DumplingSkin:
		break;
	case FoodType::Egg:
		break;
	case FoodType::Chicken:
		break;
	case FoodType::Burrito:
		break;
	case FoodType::Cheese:
		break;
	case FoodType::Carrot:
		break;
	case FoodType::Chocolate:
		break;
	case FoodType::Honey:
		break;
	case FoodType::PastaNoodles:
		break;
	case FoodType::Tomato:
		//break;
	case FoodType::Prawn:
		_Player->Input_PickUp(GetLevel()->CreateActor<Food_Ingredients_Prawn>());
		break;
	case FoodType::Cucumber:
		break;
	default:
		break;
	}
	return Input_PickUpOption::Exception;
}
//
//Input_AutoOption Tool_TrashCan::Input_Action()
//{
//	return Input_AutoOption::NoResponse;
//}