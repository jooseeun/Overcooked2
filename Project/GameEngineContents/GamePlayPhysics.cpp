#include "PreCompile.h"
#include "GamePlayPhysics.h"
#include <GameEngineCore/GameEngineCollision.h>

GamePlayPhysics::GamePlayPhysics() 
{
}

GamePlayPhysics::~GamePlayPhysics() 
{
}

void GamePlayPhysics::Update(float _DeltaTime)
{
	Gravity();
}

void GamePlayPhysics::Gravity()
{
	if (PhysicsCollision->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB) == false)
	{
		GetTransform().SetWorldDownMove(300.0f, GameEngineTime::GetDeltaTime());
	}
}


bool GamePlayPhysics::StaticObjectCollisionCheck() // 벽, 맵 오브젝트랑 충돌하면 true 반환, 충돌안하면 false 반환
{
	if (PhysicsCollision->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true||
		PhysicsCollision->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false)
	{
		return true;
	}
	else
	{
		return false;
	}

}

