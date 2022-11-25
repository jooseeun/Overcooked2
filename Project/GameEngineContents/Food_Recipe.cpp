#include "PreCompile.h"
#include "Food_Recipe.h"

Food_Recipe::Food_Recipe() 
{
}

Food_Recipe::~Food_Recipe() 
{
}


void Food_Recipe::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(ObjectFoodClass::Recipe_Default);
}