#include "PreCompile.h"
#include "Food_Ingredients_Shrimp.h"

Food_Ingredients_Shrimp::Food_Ingredients_Shrimp() 
{
}

Food_Ingredients_Shrimp::~Food_Ingredients_Shrimp() 
{
}

void Food_Ingredients_Shrimp::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(ObjectFoodClass::Shrimp);
}