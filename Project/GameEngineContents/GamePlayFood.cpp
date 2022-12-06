#include "PreCompile.h"
#include "GamePlayFood.h"

GamePlayFood::GamePlayFood() 
	: Enum_IngredientType_(IngredientType::None)
	, Trim_(false)
	, MeshName_()
	, FoodThumbnail_(nullptr)
	, Platting_(false)
	, CookingType_(CookingType::Default)
{
}

GamePlayFood::~GamePlayFood() 
{
}

void GamePlayFood::Start()
{
	GamePlayMoveable::Start();
	GamePlayMoveable::SetObjectMoveableType(ObjectMoveableType::Food);
	GamePlayMoveable::SetHoldType(PlayerHoldType::CanThrow);
}

HoldDownEnum GamePlayFood::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		return HoldDownEnum::HoldDown;
	}
	else
	{
		MsgBoxAssert("���� ó�� ����. ������ ó���� ���ϸ� ������ ����ڸ� �ڴ����ּ���")
	}

	return HoldDownEnum::Nothing;
}
