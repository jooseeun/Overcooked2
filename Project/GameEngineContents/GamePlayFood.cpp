#include "PreCompile.h"
#include "GamePlayFood.h"

GamePlayFood::GamePlayFood() 
	: Enum_IngredientType_(IngredientType::None)
	, Trim_(false)

{
}

GamePlayFood::~GamePlayFood() 
{
}

void GamePlayFood::Start()
{
	GamePlayMoveable::Start();
	GamePlayMoveable::SetObjectMoveableType(ObjectMoveableType::Food);
}

