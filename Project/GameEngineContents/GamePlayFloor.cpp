#include "PreCompile.h"
#include "GamePlayFloor.h"

GamePlayFloor::GamePlayFloor()
{
}

GamePlayFloor::~GamePlayFloor()
{
}

void GamePlayFloor::Start()
{
	GamePlayObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 50.f, 50.f, 50.f });			// ���� ũ��� 0.01
	GetCollisionObject()->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0.8f, 0 });
	GetCollisionObject()->ChangeOrder(CollisionOrder::Floor);
}

