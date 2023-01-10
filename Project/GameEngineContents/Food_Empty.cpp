#include "PreCompile.h"
#include "Food_Empty.h"

Food_Empty::Food_Empty() 
{
}

Food_Empty::~Food_Empty() 
{
}

void Food_Empty::Start()
{
	GamePlayFood::Start();
	GetCollisionObject()->Off();
	GetFBXMesh()->Off();
	GetFoodThumbnail()->Off();
}

