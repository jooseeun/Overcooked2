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
	GamePlayObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });			// 원래 크기는 0.01
	GetCollisionObject()->ChangeOrder(CollisionOrder::Floor);
}

