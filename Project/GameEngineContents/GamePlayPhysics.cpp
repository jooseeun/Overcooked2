#include "PreCompile.h"
#include "GamePlayPhysics.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Lift.h"

GamePlayPhysics::GamePlayPhysics() 
	:PhysicsCollision_(nullptr)
	, UpTime_(1.0f)
	, IsThrow_(false)
	, ThrowTime_(2.0f)
	, CurKineticEnergy_(0.0f)
	, CurSpeed_(0.0f)
	, CurMass_(0.0f)
	, PhysicsGravityCollision_(nullptr)
	, PhysicsForwardCollision_(nullptr)
	, PhysicsBackCollision_(nullptr)
	, PhysicsLeftCollision_(nullptr)
	, PhysicsRightCollision_(nullptr)
	, IsLift_(false)

{
}

GamePlayPhysics::~GamePlayPhysics() 
{
}

void GamePlayPhysics::Gravity()// 중력함수 -> Update 해주면 됨
{

	if (PhysicsGravityCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB) == false)
	{
		LiftFloorCheck();
		GetTransform().SetWorldDownMove(700.0f, GameEngineTime::GetDeltaTime());

	}


}
void GamePlayPhysics::LiftFloorCheck()
{

	if (PhysicsGravityCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Lift, CollisionType::CT_OBB,
		std::bind(&GamePlayPhysics::LiftCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{
		IsLift_ = false;

	}
}
CollisionReturn GamePlayPhysics::LiftCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (PhysicsGravityCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true)
	{
		return CollisionReturn::ContinueCheck;
	
	}
	IsLift_ = true;
	CurLift_ = _Other->GetParent()->CastThis<Lift>();

	return CollisionReturn::ContinueCheck;
}
void GamePlayPhysics::ColCheckPlayer()//플레이어한테 차이거나 하면은 밀리는 함수 임시생성한것
{
	PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
		std::bind(&GamePlayPhysics::MoveFromPlayer, this, std::placeholders::_1, std::placeholders::_2));
	PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
		std::bind(&GamePlayPhysics::PullPlayer, this, std::placeholders::_1, std::placeholders::_2));
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
	if (_This != _Other)
	{
		float4  Vec = _This->GetActor()->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
		Vec.Normalize3D();
		Vec.y = 0;
		float len = Vec.Length();

		if (_This->GetParent()->CastThis<GamePlayPhysics>()->PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			_This->GetParent()->CastThis<GamePlayPhysics>()->PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_This->GetActor()->GetTransform().SetWorldLeftMove(400.0f, GameEngineTime::GetDeltaTime());

		}
		else if (_This->GetParent()->CastThis< GamePlayPhysics>()->PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			_This->GetParent()->CastThis< GamePlayPhysics>()->PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_This->GetActor()->GetTransform().SetWorldRightMove(400.0f, GameEngineTime::GetDeltaTime());
		}

		if (_This->GetParent()->CastThis< GamePlayPhysics>()->PhysicsForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			_This->GetParent()->CastThis< GamePlayPhysics>()->PhysicsForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_This->GetActor()->GetTransform().SetWorldForwardMove(400.0f, GameEngineTime::GetDeltaTime());
		}
		else if (_This->GetParent()->CastThis< GamePlayPhysics>()->PhysicsBackCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			_This->GetParent()->CastThis< GamePlayPhysics>()->PhysicsBackCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_This->GetActor()->GetTransform().SetWorldBackMove(400.0f, GameEngineTime::GetDeltaTime());
		}
	}

	return CollisionReturn::ContinueCheck;
}

//CollisionReturn GamePlayPhysics::PullPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
//{ // 내가 다른애를 미는거
//	float4  Vec = _Other->GetActor()->GetTransform().GetWorldPosition() - _This->GetActor()->GetTransform().GetWorldPosition();
//	Vec.Normalize3D();
//	Vec.y = 0;
//	float len = Vec.Length();
//
//		if (_Other->GetParent()->CastThis<GamePlayPhysics>()->PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
//			_Other->GetParent()->CastThis<GamePlayPhysics>()->PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
//		{
//			_Other->GetActor()->GetTransform().SetWorldLeftMove(1000.0f, GameEngineTime::GetDeltaTime());
//
//		}
//		else if(_Other->GetParent()->CastThis< GamePlayPhysics>()->PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
//			_Other->GetParent()->CastThis< GamePlayPhysics>()->PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
//		{
//			_Other->GetActor()->GetTransform().SetWorldRightMove(1000.0f, GameEngineTime::GetDeltaTime());
//		}
//	
//		if (_Other->GetParent()->CastThis< GamePlayPhysics>()->PhysicsForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
//			_Other->GetParent()->CastThis< GamePlayPhysics>()->PhysicsForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
//		{
//			_Other->GetActor()->GetTransform().SetWorldForwardMove(1000.0f, GameEngineTime::GetDeltaTime());
//		}
//		else if (_Other->GetParent()->CastThis< GamePlayPhysics>()->PhysicsBackCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
//			_Other->GetParent()->CastThis< GamePlayPhysics>()->PhysicsBackCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
//		{
//			_Other->GetActor()->GetTransform().SetWorldBackMove(1000.0f, GameEngineTime::GetDeltaTime());
//		}
//
//	return CollisionReturn::ContinueCheck;
//}

void GamePlayPhysics::Throw(float4 _Vector) 
{
	if (IsThrow_ == false)
	{
		IsThrow_ = true;
		UpTime_ = 0.3f;
		ThrowTime_ = 0.6f;
	}
	else
	{

		PhysicsGravityCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_CharacterCameraCheck, CollisionType::CT_OBB,
			std::bind(&GamePlayPhysics::GetThrow, this, std::placeholders::_1, std::placeholders::_2));


		ThrowTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
		if (ThrowTime_ < 0.0f)
		{
			IsThrow_ = false;
		}

		if (UpTime_ > 0.0f)
		{
			UpTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
			GetTransform().SetWorldUpMove(900.0f, GameEngineTime::GetDeltaTime());
		}
		
		GetTransform().SetWorldMove(_Vector * GameEngineTime::GetDeltaTime() * 900.0f);
	}
	
}

CollisionReturn GamePlayPhysics::GetThrow(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (_Other->GetParent()->CastThis<Player>()->ThrowHolding(_This->GetParent()) == true)
	{
		ThrowTime_ = -1.0f;
		IsThrow_ = false;
	}

	return CollisionReturn::Break;
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



