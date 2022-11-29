#include "PreCompile.h"
#include "GamePlayPhysics.h"
#include <GameEngineCore/GameEngineCollision.h>

GamePlayPhysics::GamePlayPhysics() 
	:PhysicsCollision_(nullptr)
	, UpTime_(1.0f)
	, IsThrow_(false)
{
}

GamePlayPhysics::~GamePlayPhysics() 
{
}

void GamePlayPhysics::Gravity()
{
	if (PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB) == false)
	{
		GetTransform().SetWorldDownMove(300.0f, GameEngineTime::GetDeltaTime());
	}
}
void GamePlayPhysics::ThrowUpdate()
{

}
void GamePlayPhysics::Throw(float4 _Vector)
{

	GetTransform().SetWorldMove(_Vector * GameEngineTime::GetDeltaTime() * 100.0f);
}

bool GamePlayPhysics::StaticObjectCollisionCheck() // ��, �� ������Ʈ�� �浹�ϸ� true ��ȯ, �浹���ϸ� false ��ȯ
{
	if (PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true||
		PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false)
	{
		return true;
	}
	else
	{
		return false;
	}

}

