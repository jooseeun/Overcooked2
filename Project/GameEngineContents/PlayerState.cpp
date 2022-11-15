#include "PreCompile.h"
#include "Player.h"
#include "GamePlayFood.h"
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"
#include <math.h>

void Player::IdleStart(const StateInfo& _Info)
{
	Speed_ = 400.0f;
	PlayerRenderer_->ChangeAnimation("Walk");
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


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold"))
	{
		StateManager.ChangeState("Hold");
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //컨트롤키
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

	PlayerRenderer_->ChangeAnimation("Walk");
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Map_Object, CollisionType::CT_AABB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Object_StaticObject, CollisionType::CT_AABB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
		{
			GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
		}
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

	 
	if (CurrentHoldingObject_ == nullptr) // 잡고있는 오브젝트가 없으면
	{
		if (Interact_GroundObject_ != nullptr)
		{
			if (Interact_GroundObject_->Input_PickUp(std::dynamic_pointer_cast<Player>(shared_from_this())) == Input_PickUpOption::PickUp)
			{
				CurrentHoldingObject_ = Interact_GroundObject_;
				CurrentHoldingObject_->DetachObject();
				CurrentHoldingObject_->SetParent(shared_from_this());
				CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-80 });
				return;
			}
		}
		else if (Interact_TableObject_ != nullptr)
		{
			if (Interact_TableObject_->Input_PickUp(std::dynamic_pointer_cast<Player>(shared_from_this())) == Input_PickUpOption::PickUp)
			{
				CurrentHoldingObject_->DetachObject();
				CurrentHoldingObject_->SetParent(shared_from_this());
				CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-80 });
				return;
			}
		}
		StateManager.ChangeState("Idle");
		return;
	}
	else
	{

	}

}
void Player::HoldUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold")) // 놓기
	{ 
		if (Interact_GroundObject_ != nullptr)
		{
			if (Interact_GroundObject_->Input_PickUp(CurrentHoldingObject_) == Input_PickUpOption::PickUp)
			{
				CurrentHoldingObject_.reset();
				StateManager.ChangeState("Idle");
				return;
			}
		}
		else
		{
			CurrentHoldingObject_->GetCollisionObject()->On();
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_.reset();
			StateManager.ChangeState("Idle");
     		return;
   	  	}
      
	  	if (Interact_TableObject_ != nullptr) 
	   	 {
		 	if (Interact_TableObject_->Input_PickUp(CurrentHoldingObject_) == Input_PickUpOption::PickUp)
			{
				CurrentHoldingObject_.reset();
				StateManager.ChangeState("Idle");
				return;
			}
		}
		else
		{
			CurrentHoldingObject_->GetCollisionObject()->On();
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_.reset();
			StateManager.ChangeState("Idle");
			return;
		}
	}


	 // Player object 를 든 상태로도 이동 가능하게 하기
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
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
			if (PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Map_Object, CollisionType::CT_AABB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
				PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Object_StaticObject, CollisionType::CT_AABB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
			}
		}
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