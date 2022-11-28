#include "PreCompile.h"
#include "Player.h"
#include "FoodBox.h"
#include "TrashCan.h"
#include "Equipment_Plate.h"
#include <math.h>

void Player::IdleStart(const StateInfo& _Info)
{
	CurStateType_ = PlayerCurStateType::Idle;
	IdleRendererON();		
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] +"Idle");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });

	Speed_ = 400.0f;
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("ChangePlayerCustom"))
	{
		ChangePlayer();
	}
	if (true == GameEngineInput::GetInst()->IsDownKey("ChangePlayerNum"))
	{
		PlayerPNum += 1;
		if (PlayerPNum == 5)
		{
			PlayerPNum = 1;
		}
		ChangePlayerColor();
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Move");
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold"))
	{
		StateManager.ChangeState("HoldUp");
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //컨트롤키
	{
		Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
			std::bind(&Player::TableSliceCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	WalkRendererON();
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
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
	CurStateType_ = PlayerCurStateType::Throw;
	{ //컨트롤 키를 때기 전까지 안던져짐, 방향이동 가능
		PlayerDirCheck();
		MoveAngle();
	}

	if (true == GameEngineInput::GetInst()->IsUpKey("PlayerInteract"))
	{


	}
	PlayerIdleRenderer_[PlayerCustomNum]->AnimationBindEnd(PlayerName_[PlayerCustomNum] +"Throw", [=](const GameEngineRenderingEvent& _Info)
		{

			CurHoldType_ = PlayerHoldType::Max;
			StateManager.ChangeState("Idle");
		});
}

void Player::HoldUpStart(const StateInfo& _Info)
{
	if (CurrentHoldingObject_ == nullptr)
	{
		CurStateType_ = PlayerCurStateType::HoldUp;
		if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
			std::bind(&Player::GroundHoldUpCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)//바닥에 들수있는  물건이 없을때
		{
			if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::TableHoldUpCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				StateManager.ChangeState("Idle");
			}// 테이블 검사
		}
	}


}
void Player::HoldUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //컨트롤키
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

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold")) // 놓기
	{ 
		StateManager.ChangeState("HoldDown");
	}


	// Player object 를 든 상태로도 이동 가능하게 하기
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] +"WalkHolding");
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		PlayerDirCheck();

		if (MoveAngle() == true)
		{
			// 플레이어 벽 출돌 체크
			if (PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Map_Object, CollisionType::CT_AABB) == false &&
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
			if (PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Map_Object, CollisionType::CT_AABB) == false &&
				PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Object_StaticObject, CollisionType::CT_AABB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
			}
		}
	}
	else
	{
		PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] +"IdleHolding");
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	}

}
void Player::HoldDownStart(const StateInfo& _Info)
{
	CurStateType_ = PlayerCurStateType::HoldDown;
	if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::TableHoldDownCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{
		CurrentHoldingObject_->DetachObject();
		CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,0,0 });
		CurrentHoldingObject_->GetTransform().SetWorldPosition(GetTransform().GetLocalPosition() + GetTransform().GetBackVector() * 60.0f );
		//이때 콜리젼 On이 안됨
		CurrentHoldingObject_ = nullptr;
	}
}
void Player::HoldDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (CurrentHoldingObject_ == nullptr)
	{
		StateManager.ChangeState("Idle");
	}
}
void Player::SliceStart(const StateInfo& _Info) // 자르는 도중 이동하면 취소됨
{
	CurStateType_ = PlayerCurStateType::Slice;
	ChopRendererON();
}
void Player::SliceUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Move");
		return;
	}
}

void Player::DishWashStart(const StateInfo& _Info) // 설거지하는 도중 이동하면 취소됨
{
	CurStateType_ = PlayerCurStateType::DishWash;

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
	CurStateType_ = PlayerCurStateType::FireOff;
	FireOff_ = true;
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "IdleHolding");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
}
void Player::FireOffUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerInteract"))
	{
		StateManager.ChangeState("Hold");
		return;
	}

	{ //소화기 방향이동만 가능, 못움직임
		PlayerDirCheck();
		MoveAngle();
	}


}