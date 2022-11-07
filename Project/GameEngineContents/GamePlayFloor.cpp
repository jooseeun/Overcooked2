#include "PreCompile.h"
#include "GamePlayFloor.h"

GamePlayFloor::GamePlayFloor()
	: Collision_(nullptr)
{
}

GamePlayFloor::~GamePlayFloor()
{
}

void GamePlayFloor::Start()
{
	//GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(GetTransform().GetWorldScale());
	Collision_->ChangeOrder(CollisionOrder::Floor);
}

