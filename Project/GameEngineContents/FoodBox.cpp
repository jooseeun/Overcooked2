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
}