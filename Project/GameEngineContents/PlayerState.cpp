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

	Speed_ = 650.0f;
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
	{

		StateManager.ChangeState("Move");
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold" + PNumString))
	{
		StateManager.ChangeState("HoldUp");
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract" + PNumString)) //컨트롤키
	{
		if (CurrentHoldingObject_ == nullptr) // 손에 아무것도 없을때
		{
			Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::TableSliceCheck, this, std::placeholders::_1, std::placeholders::_2)); // 도마 검사
		}
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	WalkRendererON();
}
void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
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

	if (true == GameEngineInput::GetInst()->IsUpKey("PlayerInteract" + PNumString))
	{
		PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Throw");
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		Throw(GetTransform().GetBackVector());
	}
	//if (CurrentHoldingObject_->GetIsThrow() == true) // 일단 Throw 주석처리
	//{
	//	CurrentHoldingObject_->Throw(GetTransform().GetBackVector());
	//}
	//else
	//{
	//	StateManager.ChangeState("Idle");
	//}
	PlayerIdleRenderer_[PlayerCustomNum]->AnimationBindEnd(PlayerName_[PlayerCustomNum] +"Throw", [=](const GameEngineRenderingEvent& _Info)
		{

			CurHoldType_ = PlayerHoldType::Max;
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
	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract" + PNumString)) //컨트롤키
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

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold" + PNumString)) // 놓기
	{ 
		StateManager.ChangeState("HoldDown");
	}


	// Player object 를 든 상태로도 이동 가능하게 하기
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
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
		DetachPlayerHoldingToGround();
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
	IsSlice_ = true;
	ChopRendererON();
}
void Player::SliceUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::TableSliceCheck, this, std::placeholders::_1, std::placeholders::_2));

	Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::InteractTableCheck, this, std::placeholders::_1, std::placeholders::_2));

	if (IsSlice_ == false)
	{
		StateManager.ChangeState("Idle");
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
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
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
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

	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerInteract" + PNumString))
	{
		StateManager.ChangeState("Hold");
		return;
	}

	{ //소화기 방향이동만 가능, 못움직임
		PlayerDirCheck();
		MoveAngle();
	}

}