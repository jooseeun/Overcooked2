#include "PreCompile.h"
#include "GamePlayPhysics.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCollision.h>

GamePlayPhysics::GamePlayPhysics() 
	:PhysicsCollision_(nullptr)
	, UpTime_(1.0f)
	, IsThrow_(false)
	, ThrowTime_(2.0f)
	, CurKineticEnergy_(0.0f)
	, CurSpeed_(0.0f)
	, CurMass_(0.0f)
	, PhysicsGravityCollision_(nullptr)
{
}

GamePlayPhysics::~GamePlayPhysics() 
{
}

void GamePlayPhysics::Gravity()// 중력함수 -> Update 해주면 됨
{
	if (PhysicsGravityCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB) == false)
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
{ // 내가 밀리는거
	if (_This != _Other)
	{
		if (PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
			PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false)
		{
			float4  Vec = _This->GetActor()->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
			Vec.Normalize3D();
			Vec.y = 0;
			GetTransform().SetWorldMove(Vec*500.0f * GameEngineTime::GetDeltaTime());
		}
	}


	return CollisionReturn::ContinueCheck;
} 

CollisionReturn GamePlayPhysics::PullPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{ // 내가 다른애를 미는거
	float4  Vec = _Other->GetActor()->GetTransform().GetWorldPosition() - _This->GetActor()->GetTransform().GetWorldPosition();
	Vec.Normalize3D();
	Vec.y = 0;
	float len = Vec.Length();

		if (PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_Other->GetActor()->GetTransform().SetWorldLeftMove(100.0f, GameEngineTime::GetDeltaTime());
		}
		else if(PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_Other->GetActor()->GetTransform().SetWorldRightMove(100.0f, GameEngineTime::GetDeltaTime());
		}
	
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
		PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void GamePlayPhysics::CalculateKineticEnergy() //운동에너지 계산 함수 -> 필요하면 Update에서 돌려주면 된다
{ // 일단 질량을 WorldScale로 계산했는데 특수한 경우가 필요하면 CurMass로 질량설정해주면 된다.
	CurKineticEnergy_ = 0.5 * CurSpeed_ * (pow((double)GetTransform().GetWorldScale().x, 2) +
		pow((double)GetTransform().GetWorldScale().y, 2) + pow((double)GetTransform().GetWorldScale().z, 2));
}


void GamePlayPhysics::CalculateKineticEnergyMass() //운동에너지 계산 함수 질량을 따로 두었다면 이 함수 사용하면 된다.
{
	CurKineticEnergy_ = 0.5 * CurSpeed_ * pow(CurMass_,2);
}