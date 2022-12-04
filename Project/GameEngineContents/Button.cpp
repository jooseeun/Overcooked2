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

	GetFBXMesh()->SetFBXMesh("ButtonOff.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Button::Update(float _DeltaTime)
{
}

