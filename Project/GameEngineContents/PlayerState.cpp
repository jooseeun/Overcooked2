#include "PreCompile.h"
#include "Player.h"
#include "GamePlayFood.h"
#include "GamePlayStaticObject.h"
#include "FoodBox.h"
#include "TrashCan.h"
#include "Equipment_Plate.h"
#include <math.h>

void Player::IdleStart(const StateInfo& _Info)
{
	IdleRendererON();		
	PlayerIdleRenderer_->ChangeAnimation(PlayerName_+"Idle");
	PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
	PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });

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


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold"))
	{
		StateManager.ChangeState("Hold");
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //컨트롤키
	{
		
		if (Interact_TableObject_ == nullptr)
		{
			return;
		}
		else
		{
			if (Interact_TableObject_->GetStuff() == nullptr)
			{
				return;
			}
			else
			{
				if (Interact_TableObject_->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard) // 도마일때
				{
					StateManager.ChangeState("Slice");
					return;
				}
			}

		}

		//StateManager.ChangeState("DishWash");
		
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
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
	{ //컨트롤 키를 때기 전까지 안던져짐, 방향이동 가능
		PlayerDirCheck();
		MoveAngle();
	}

	if (true == GameEngineInput::GetInst()->IsUpKey("PlayerInteract"))
	{
		//던지는 행동
		// Throw 애니메이션
		IdleRendererON();
		PlayerIdleRenderer_->ChangeAnimation(PlayerName_ + "Throw");
		PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
		PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });

	}
	PlayerIdleRenderer_->AnimationBindEnd(PlayerName_+"Throw", [=](const GameEngineRenderingEvent& _Info)
		{
			// CurrentHoldingObject - 부모자식관계 삭제, 피봇 원래대로 돌리기
			// CurrentHoldingObject -> 여기서 Throw 함수 해주면 된다. 
			CurrentHoldingObject_->GetCollisionObject()->On();
			CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,0,0 });
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_->Input_Throwing(float4{ GetTransform().GetLocalPosition().x-100,0,0 });
			CurrentHoldingObject_ = nullptr;

			//CurHoldType_ = PlayerHoldType::Max;
			StateManager.ChangeState("Idle");
		});
}

void Player::HoldStart(const StateInfo& _Info)
{
	if (FireOff_ == true)
	{
		return;
	}

	if (CurrentHoldingObject_ == nullptr)
		// 플레이어 손에 아무것도 없을때
	{
		if (Interact_GroundObject_ != nullptr) // 땅에 상호작용하는 오브젝트가 있을때
		{
			if (Input_PickUp(Interact_GroundObject_) == Input_PickUpOption::PickUp) //상호작용가능한 땅의 오브젝트가 집을 수 있는것일때
			//if (Interact_GroundObject_->Input_PickUp(std::dynamic_pointer_cast<Player>(shared_from_this())) == Input_PickUpOption::PickUp) //상호작용가능한 땅의 오브젝트가 집을 수 있는것일때
			{ // 바닥에 있는 오브젝트는 부모가 없으므로 SetParent만 해도됨
				CurrentHoldingObject_->SetParent(shared_from_this());
				CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-60 });
				return;
			}

		}

		else if (Interact_TableObject_ != nullptr) // 앞에 테이블이 있을때
		{
			if (Interact_TableObject_->Input_PickUp(std::dynamic_pointer_cast<Player>(shared_from_this())) == Input_PickUpOption::PickUp)
			{
				if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::GetCrashTableObject, this, std::placeholders::_1, std::placeholders::_2)) == true)
				{
				 	Interact_TableObject_->SetStuff(nullptr);
				}
				CurrentHoldingObject_->DetachObject();
				CurrentHoldingObject_->SetParent(shared_from_this());
				CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-60 });
				return;
			}
			else
			{
				if (Interact_TableObject_->GetStaticObjectType() == MapObjType::FoodBox) // 음식 얻어오기
				{
					Interact_TableObject_->CastThis<FoodBox>()->SwitchIsInteraction();
					StateManager.ChangeState("Idle"); // 지워야됨
					return;
				}

				StateManager.ChangeState("Idle");
				return;  
			}
		}
		else
		{				


			StateManager.ChangeState("Idle");
			return;
		}


	}
	else
	{
		StateManager.ChangeState("Idle");
		return;
	}
	IdleRendererON();
	PlayerIdleRenderer_->ChangeAnimation(PlayerName_+"IdleHolding");
	PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
	PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });
}
void Player::HoldUpdate(float _DeltaTime, const StateInfo& _Info)
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
		if (FireOff_ == true)
		{
			FireOff_ = false;
		}

		if (Interact_TableObject_->GetStaticObjectType() == MapObjType::TrashCan) // 음식 얻어오기
		{
			//Interact_TableObject_->CastThis<TrashCan>()->버리는 기능();
			StateManager.ChangeState("Idle");
			return;
		}


		if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false) //
		{
			// 없을때-> 바닥에 놓기
			CurrentHoldingObject_->GetCollisionObject()->On();
			CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,0,0});
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_ = nullptr;
			StateManager.ChangeState("Idle");
			return;
		}
		else // 앞에 테이블이 있을때
		{
			if (Interact_TableObject_->GetStuff() == nullptr) // 테이블 있고 테이블에 올려진 물건이 없을때
			{
				CurrentHoldingObject_->GetCollisionObject()->On();
				CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,0,0 });
				CurrentHoldingObject_->DetachObject();
				Interact_TableObject_->SetStuff(CurrentHoldingObject_);
				float4 ToolPos = Interact_TableObject_->GetToolPos();
				Interact_TableObject_->GetStuff()->GetTransform().SetWorldPosition(ToolPos);
				CurrentHoldingObject_ = nullptr;

				StateManager.ChangeState("Idle");
				return;
			}

			else if (Interact_TableObject_->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard) // 도마일때
			{
				return;
			}
			else if (CurrentHoldingObject_ != nullptr && Interact_TableObject_->GetStuff() != nullptr) // 일단 쓰레기통예외처리
			{
				return;
			}
		}
		return;
	}


	// Player object 를 든 상태로도 이동 가능하게 하기
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		PlayerIdleRenderer_->ChangeAnimation(PlayerName_+"WalkHolding");
		PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
		PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });
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
	else
	{
		PlayerIdleRenderer_->ChangeAnimation(PlayerName_+"IdleHolding");
		PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
		PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });
	}

}

void Player::SliceStart(const StateInfo& _Info) // 자르는 도중 이동하면 취소됨
{
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
	FireOff_ = true;
	PlayerIdleRenderer_->ChangeAnimation(PlayerName_ + "IdleHolding");
	PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
	PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });
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