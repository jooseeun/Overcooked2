#include "PreCompile.h"
#include "Button.h"

Button::Button() 
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
	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Button::Update(float _DeltaTime)
{
}

