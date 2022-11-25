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