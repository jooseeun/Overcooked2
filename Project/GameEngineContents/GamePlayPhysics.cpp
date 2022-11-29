#include "PreCompile.h"
#include "GamePlayPhysics.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCollision.h>

GamePlayPhysics::GamePlayPhysics() 
	:PhysicsCollision_(nullptr)
	, UpTime_(1.0f)
	, IsThrow_(false)
	, ThrowTime_(2.0f)
{
}

GamePlayPhysics::~GamePlayPhysics() 
{
}

void GamePlayPhysics::Gravity()// 중력함수 -> Update 해주면 됨
{
	if (PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB) == false)
	{
		GetTransform().SetWorldDownMove(300.0f, GameEngineTime::GetDeltaTime());
	}
}

void GamePlayPhysics::ColCheckPlayer()//플레이어한테 차이거나 하면은 밀리는 함수 임시생성한것
{
	PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
		std::bind(&GamePlayPhysics::MoveFromPlayer, this, std::placeholders::_1, std::placeholders::_2));
}

CollisionReturn GamePlayPhysics::MoveFromPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	GetTransform().SetWorldMove(_Other->GetActor()->CastThis<Player>()->GetTransform().GetBackVector()*100.0f);

	return CollisionReturn::ContinueCheck;
} 




void GamePlayPhysics::Throw(float4 _Vector) 
{
	if (IsThrow_ == false)
	{
		IsThrow_ = true;
		UpTime_ = 1.0f;
		ThrowTime_ = 2.0f;
	}
	else
	{
		ThrowTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
		if (ThrowTime_ < 0.0f)
		{
			IsThrow_ = false;
		}

		if (UpTime_ > 0.0f)
		{
			UpTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
			GetTransform().SetWorldUpMove(500.0f, GameEngineTime::GetDeltaTime());
		}
		
		GetTransform().SetWorldMove(_Vector * GameEngineTime::GetDeltaTime() * 1000.0f);
	}
	
}

bool GamePlayPhysics::StaticObjectCollisionCheck() // 벽, 맵 오브젝트랑 충돌하면 true 반환, 충돌안하면 false 반환
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

