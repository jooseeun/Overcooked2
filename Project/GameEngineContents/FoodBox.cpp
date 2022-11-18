#include "PreCompile.h"
#include "FoodBox.h"

FoodBox::FoodBox() 
	: Enum_Ingredients_(ObjectFoodClass::None)
	, IsOpen_(false)
{
}

FoodBox::~FoodBox() 
{
}


void FoodBox::Start()
{
	GamePlayStaticObject::Start();

	Lid_ = GetLevel()->CreateActor<GameEngineActor>();
	Lid_->SetParent(shared_from_this());
	Lid_->GetTransform().SetWorldMove({ 0, 3.f, 35.f });

	std::shared_ptr<GameEngineFBXStaticRenderer> LidRenderer = Lid_->CreateComponent<GameEngineFBXStaticRenderer>();
	LidRenderer->SetFBXMesh("CreateBox.fbx", "Texture", 1);
	LidRenderer->GetTransform().SetWorldScale({ 120, 100, 120 });
	LidRenderer->GetTransform().SetWorldMove({0, 5.f, -38.f});

	std::shared_ptr<GameEngineCollision> Collision_Object_ = Lid_->CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0, 0.5f });
	Collision_Object_->ChangeOrder(CollisionOrder::Object_None);

	GetFBXMesh()->SetFBXMesh("CreateBox.fbx", "Texture", 0);
	GetFBXMesh()->GetTransform().SetWorldScale({ 120, 100, 120 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	IsInteraction_ = true;
	IsReverse_ = true;
	Value_ = 0.f;
}

void FoodBox::Update(float _DeltaTime)
{ 
	if (true == IsReverse_)
	{
		IsReverse_ = false;
	}

	if (true == IsInteraction_)
	{
		if (false == IsOpen_)
		{
			Value_ += _DeltaTime * 15.f;

			Lid_->GetTransform().SetLocalRotation({ Value_, 0.f, 0.f });

			if (45.f <= Lid_->GetTransform().GetLocalRotation().x)
			{
				IsOpen_ = true;
			}
		}

		if (true == IsOpen_)
		{
			Value_ -= _DeltaTime * 15.f;
			Lid_->GetTransform().SetLocalRotation({ Value_, 0.f, 0.f });

			if (0.f >= Lid_->GetTransform().GetLocalRotation().x)
			{
				Value_ = 0.f;
				IsInteraction_ = true;
				IsOpen_ = false;
			}
		}
	}
}

