#include "PreCompile.h"
#include "Button.h"

Button::Button() 
	: IsReady_(false)
	, IsPressed_(false)
	, ButtonRenderer_On(nullptr)
	, ButtonRenderer_Off(nullptr)
{
}

Button::~Button() 
{
}

void Button::Start()
{
	ButtonRenderer_On = CreateComponent<GameEngineFBXStaticRenderer>();
	ButtonRenderer_Off = CreateComponent<GameEngineFBXStaticRenderer>();
	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");

	ButtonRenderer_On->SetFBXMesh("ButtonOn2.fbx", "Texture");
	ButtonRenderer_On->GetTransform().SetWorldMove({ 0, 40.f, 0.f });
	ButtonRenderer_On->GetTransform().SetWorldRotation({ 90.f, 0.f, 0.f });

	ButtonRenderer_Off->SetFBXMesh("ButtonOff2.fbx", "Texture");
	ButtonRenderer_Off->GetTransform().SetWorldMove({ 0, 40.f, 0.f });
	ButtonRenderer_Off->GetTransform().SetWorldRotation({ 90.f, 0.f, 0.f });

	Collision_Object_->ChangeOrder(CollisionOrder::Map_Button);
	Collision_Object_->GetTransform().SetWorldScale({ 100, 100, 100 });

	ButtonRenderer_On->Off();
	ButtonRenderer_Off->On();
	//ParentCannon_ = std::dynamic_pointer_cast<Cannon>(GetParent());

}

void Button::Update(float _DeltaTime)
{
	// 캐논 Shoot => Off
	// 캐논 Ready => On
	//if (GetCannonState() == CannonState::Shoot || GetCannonState() == CannonState::Idle)
	//{
	//	if (false == IsReady_)
	//	{
	//		return;
	//	}
	//	IsReady_ = false;
	//	Mesh_Object_->SetFBXMesh("ButtonOff2.fbx", "Texture");
	//}
	//else if (GetCannonState() == CannonState::Ready)
	//{
	//	if (true == IsReady_)
	//	{
	//		return;
	//	}
	//	IsReady_ = true;
	//	Mesh_Object_->SetFBXMesh("ButtonOn2.fbx", "Texture");
	//}

	if (true == IsReady_)
	{
		ButtonRenderer_Off->Off();
		ButtonRenderer_On->On();
	}
	else
	{
		ButtonRenderer_Off->On();
		ButtonRenderer_On->Off();
	}
}

