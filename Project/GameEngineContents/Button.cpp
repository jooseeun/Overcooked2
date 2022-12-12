#include "PreCompile.h"
#include "Button.h"

Button::Button() 
	: IsOn_(false)
{
}

Button::~Button() 
{
}

void Button::Start()
{
	Mesh_Object_ = CreateComponent<GameEngineFBXStaticRenderer>("Mesh_Object");
	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");

	Mesh_Object_->SetFBXMesh("ButtonOff2.fbx", "Texture");
	Mesh_Object_->GetTransform().SetWorldMove({ 0, 40.f, 0.f });
	Mesh_Object_->GetTransform().SetWorldRotation({ 90.f, 0.f, 0.f });
	Collision_Object_->ChangeOrder(CollisionOrder::Map_Button);
	Collision_Object_->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Button::Update(float _DeltaTime)
{
	// 캐논 Shoot => Off
	// 캐논 Ready => On
	/*if (GetCannonState() == CannonState::Shoot || GetCannonState() == CannonState::Idle)
	{
		if (false == IsOn_)
		{
			return;
		}
		IsOn_ = false;
		Mesh_Object_->SetFBXMesh("ButtonOff2.fbx", "Texture");
	}
	else if (GetCannonState() == CannonState::Ready)
	{
		if (true == IsOn_)
		{
			return;
		}
		IsOn_ = true;
		Mesh_Object_->SetFBXMesh("ButtonOn2.fbx", "Texture");
	}*/
}

