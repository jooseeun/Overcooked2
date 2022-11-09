#include "PreCompile.h"
#include "Player.h"
#include "GamePlayFood.h"
#include "GamePlayStaticObject.h"
#include <math.h>

void Player::IdleStart(const StateInfo& _Info)
{
	Speed_ = 400.0f;
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Move");
	}


	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold"))
	{
		//StateManager.ChangeState("Hold");
	}


	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerInteract")) //컨트롤키
	{
		if (CurrentHoldingObject_ != nullptr)
			//손에 무언가 있을때
		{
			if (CurHoldType_ == PlayerHoldType::CanThrow)
			{
				StateManager.ChangeState("Throw");
			}
			else if (CurHoldType_ == PlayerHoldType::FireExtinguisher)
			{
				StateManager.ChangeState("FireOff");
			}
		}

		else
			//손에 아무것도 없을때
		{
			//앞의 타일 검사
			//Interact_TableObject_->Input_PickUp(this) == Input_PickUpOption::PickUp;
			//다지기, 설거지둘중 하나


			StateManager.ChangeState("Slice");
			//StateManager.ChangeState("DishWash");
		}
	}
}

void Player::MoveStart(const StateInfo& _Info)
{

}
void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Idle");
		return;
	}

	PlayerDirCheck();

	if (MoveAngle() == true)
	{
		// 플레이어 벽 출돌 체크
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Map_Object, CollisionType::CT_AABB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Object_StaticObject, CollisionType::CT_AABB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
		{
			GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
		} 
		else
		{
			// 플레이어가 벽이랑 충돌했을때 대각선 키 누르면 플레이어 밀려서 이동하는 함수
			MoveCollisionSideCheck(_DeltaTime);
		}
	}

	else
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
		return;
	}

}
void Player::ThrowStart(const StateInfo& _Info)
{

}
void Player::ThrowUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerThrow"))
	{
		//던지고 다음과 같이 실행
		CurHoldType_ = PlayerHoldType::Max;
		StateManager.ChangeState("Idle");
	}
}

void Player::HoldStart(const StateInfo& _Info)
{
	if (CurrentHoldingObject_ == nullptr &&
		Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
			std::bind(&Player::GetCrashGroundObject, this, std::placeholders::_1, std::placeholders::_2)))
		// 플레이어가 들고있는게 없고 검사 콜리전이 바닥에 떨어진 오브젝트 콜리젼과 닿아있을때
	{

		if (CurrentHoldingObject_ == nullptr &&
			Interact_GroundObject_->Input_PickUp(this) == Input_PickUpOption::PickUp)
		{
			Interact_GroundObject_ = nullptr;
			CurrentHoldingObject_->GetTransform().SetParentTransform(CurrentHoldingObject_->GetTransform());
			return;
		}

	}
	else
	{
		if (Interact_GroundObject_ != nullptr)
		{
			Interact_GroundObject_->SetBloomEffectOff();
			Interact_GroundObject_ = nullptr;
			CurrentHoldingObject_->GetTransform().SetParentTransform(CurrentHoldingObject_->GetTransform());
		}
	}



	if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::GetCrashTableObject, this, std::placeholders::_1, std::placeholders::_2)))
		// 검사 콜리전이 테이블 콜리젼과 닿아있을때
	{

		if (CurrentHoldingObject_ == nullptr &&
			Interact_TableObject_->Input_PickUp(this) == Input_PickUpOption::PickUp)
		{
			Interact_TableObject_->SetBloomEffectOff();
			return;
		}

	}

	else
	{
		if (Interact_TableObject_ != nullptr)
		{
			Interact_TableObject_->SetBloomEffectOff();
			Interact_TableObject_ = nullptr;
			CurrentHoldingObject_->GetTransform().SetParentTransform(CurrentHoldingObject_->GetTransform());
		}
	}
}
void Player::HoldUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold")) // 놓기
	{
		CurrentHoldingObject_->GetTransform().DetachTransform(); // 자식 떼어내기
		StateManager.ChangeState("Idle");
	}

	

}

void Player::SliceStart(const StateInfo& _Info) // 자르는 도중 이동하면 취소됨
{
	
}
void Player::SliceUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::DishWashStart(const StateInfo& _Info) // 설거지하는 도중 이동하면 취소됨
{

}
void Player::DishWashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::FireOffStart(const StateInfo& _Info)
{

}
void Player::FireOffUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerInteract"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	{ //소화기 방향이동만 가능, 못움직임
		PlayerDirCheck();
		MoveAngle();
	}
	

}