#include "PreCompile.h"
#include "GamePlayTool.h"
#include "GamePlayMoveable.h"

GamePlayTool::GamePlayTool()
	: Moveable_Current_(nullptr)
	, InteractOption_Current_(AutoOption::NoResponse)
	, MoveablePos_({0, 0})
{
}

GamePlayTool::~GamePlayTool()
{
}

// ---------------------------------------Start
void GamePlayTool::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Tool);
	
}

// ---------------------------------------Update



void GamePlayTool::SetMoveable(std::shared_ptr<Player> _Player)
{
	SetMoveable(_Player->GetPlayerHolding());
	_Player->DetachPlayerHolding();
}

void GamePlayTool::SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child)
{
	_Child->SetParent(shared_from_this());
	std::weak_ptr<GamePlayMoveable> Object = _Child->CastThis<GamePlayMoveable>();
	Moveable_Current_ = Object.lock();
	Object.lock()->GetTransform().SetLocalPosition(MoveablePos_);
	Object.lock()->GetCollisionObject()->Off();
}