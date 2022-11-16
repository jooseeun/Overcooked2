#include "PreCompile.h"
#include "FoodBox.h"

FoodBox::FoodBox() 
	: Enum_Ingredients_(ObjectFoodClass::None)
{
}

FoodBox::~FoodBox() 
{
}


void FoodBox::Start()
{
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("CreateBox.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });
}