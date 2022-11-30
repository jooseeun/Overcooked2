#include "PreCompile.h"
#include "GamePlayFood.h"

GamePlayFood::GamePlayFood() 
	: Enum_IngredientType_(IngredientType::None),
	  Enum_ObjectFoodType_(ObjectFoodType::None)

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

HoldDownEnum GamePlayFood::HoldDown(std::shared_ptr<Player> _Player)
{
	if (_Player->GetPlayerHolding() == nullptr)
	{
		return HoldDownEnum::HoldUp;
	}
	else
	{
		MsgBoxAssert("���� ó������ ���� ����");
		return HoldDownEnum::HoldUp;
	}
}