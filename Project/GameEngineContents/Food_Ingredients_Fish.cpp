#include "PreCompile.h"
#include "Food_Ingredients_Fish.h"

Food_Ingredients_Fish::Food_Ingredients_Fish() 
{
}

Food_Ingredients_Fish::~Food_Ingredients_Fish() 
{
}

void Food_Ingredients_Fish::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(ObjectFoodClass::Fish);
}