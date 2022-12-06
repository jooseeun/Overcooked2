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
		MsgBoxAssert("예외 처리 예정. 더빠른 처리를 원하면 컨텐츠 담당자를 닥달해주세요")
	}

	return HoldDownEnum::Nothing;
}
