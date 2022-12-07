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
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("ButtonOff2.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, -50 });
	GetCollisionObject()->ChangeOrder(CollisionOrder::Map_Button);
	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Button::Update(float _DeltaTime)
{
	// 캐논 Shoot => Off
	// 캐논 Ready => On
	if (GetCannonState() == CannonState::Shoot || GetCannonState() == CannonState::Idle)
	{
		if (false == IsOn_)
		{
			return;
		}
		IsOn_ = false;
		GetFBXMesh()->SetFBXMesh("ButtonOff2.fbx", "Texture");
	}
	else if (GetCannonState() == CannonState::Ready)
	{
		if (true == IsOn_)
		{
			return;
		}
		IsOn_ = true;
		GetFBXMesh()->SetFBXMesh("ButtonOn2.fbx", "Texture");
	}
}

