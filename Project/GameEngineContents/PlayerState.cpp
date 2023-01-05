#include "PreCompile.h"
#include "Player.h"
#include "FoodBox.h"
#include "TrashCan.h"
#include "Equipment_Plate.h"
#include "PlayerRunningPuff.h"

#include <math.h>

void Player::IdleStart(const StateInfo& _Info)
{
	
	IsHolding_ = "Idle";
	CurStateType_ = PlayerCurStateType::Idle;
	IdleRendererON();		
	CurAniName_ = PlayerName_[PlayerCustomNum] + "Idle";
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(CurAniName_);
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });

	Speed_ = 650.0f;
	IsDeath_ = 0;
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ColCheckPlayer();

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		if (IsPotal_ == false)
		{
			StateManager.ChangeState("Move");
			
		}
	}

	
	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold" ))
	{
		if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Cannon, CollisionType::CT_OBB,
			std::bind(&Player::EnterCannon, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{
			StateManager.ChangeState("CannonInter");
			return;

		}
		else if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Button, CollisionType::CT_OBB,
			std::bind(&Player::PushButton, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{
			return;
		}
		//설거지상호작용

		else
		{
			StateManager.ChangeState("HoldUp");
			return;
		}
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //컨트롤키
	{
		if (CurrentHoldingObject_ == nullptr) // 손에 아무것도 없을때
		{
			if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Sink, CollisionType::CT_OBB,
				std::bind(&Player::TableSinkCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::TableSliceCheck, this, std::placeholders::_1, std::placeholders::_2));
			}

		}
	}
}


void Player::MoveStart(const StateInfo& _Info)
{
	WalkRendererON();
	CurAniName_ = PlayerName_[PlayerCustomNum] + "Walk";
	PlayerWalkRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Walk");
	PlayerWalkRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerWalkRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	IsMove_ = 1;
}
void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	RunningPuffTime_ += 1.0f * _DeltaTime;
	if (RunningPuffTime_ > 0.06f)
	{
		MakeRunningPuff(1);
	}


	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" ) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack" ))
	{

		StateManager.ChangeState("Idle");
		IsMove_ = 0;
		return;
	}

	PlayerDirCheck();
	if (IsPotal_ == true)
	{
		StateManager.ChangeState("Idle");
		IsMove_ = 0;
		return;

	}
	if (MoveAngle() == true)
	{
		// 플레이어 벽 출돌 체크
		if (PlayerMoveCollisionCheck(PlayerForwardCollision_) == true
			&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB)==false)
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
		if (PlayerMoveCollisionCheck(PlayerForwardCollision_) == true
			&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB) == false)
		{
			GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
		}
		return;
	}

}
void Player::ThrowStart(const StateInfo& _Info)
{
	CurAniName_ = PlayerName_[PlayerCustomNum] + "Idle";
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Idle");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	GameEngineSound::SoundPlayOneShot("Throw2.wav");
	IsThrow_ = false;
}
void Player::ThrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerIdleRenderer_[PlayerCustomNum]->AnimationBindEnd(PlayerName_[PlayerCustomNum] + "Throw", [=](const GameEngineRenderingEvent& _Info)
		{
			CurAniName_ = PlayerName_[PlayerCustomNum] + "Idle";
			PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Idle");
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		});

	CurStateType_ = PlayerCurStateType::Throw;
	{ //컨트롤 키를 때기 전까지 안던져짐, 방향이동 가능
		PlayerDirCheck();
		MoveAngle();
	}

	if (true == GameEngineInput::GetInst()->IsUpKey("PlayerInteract" ))
	{
		CurAniName_ = PlayerName_[PlayerCustomNum] + "Throw";
		PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Throw");
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		PlayerIdleRenderer_[PlayerCustomNum]->GetCurAnim()->bOnceEnd = false;
		ThrowVec_ = GetTransform().GetBackVector();
		CurrentHoldingObject_->CastThis<GamePlayPhysics>()->Throw(GetTransform().GetBackVector());
		CurrentHoldingDetach();

		IsThrow_ = true;
	}
	if (IsThrow_ == true)
	{
		if (CurrentHoldingObject_->CastThis<GamePlayPhysics>()->GetIsThrow() == true) // 일단 Throw 주석처리
		{
			CurrentHoldingObject_->CastThis<GamePlayPhysics>()->Throw(ThrowVec_);
		}
		else
		{
			CurrentHoldingNull();
			CurHoldType_ = PlayerHoldType::Max;
			StateManager.ChangeState("Idle");
		}
	}


}

void Player::HoldUpStart(const StateInfo& _Info)
{
	ColCheckPlayer();
	if (IsThrowHolding_ == true && CurrentHoldingObject_!=nullptr)
	{
		IsHolding_ = "Holding";
		CurStateType_ = PlayerCurStateType::HoldUp;
		return;
	}
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
				return;
			}// 테이블 검사
			IsHolding_ = "Holding";

			GameEngineSound::SoundPlayOneShot("Item_PickUp_03.wav");
		}
	}

}
void Player::HoldUpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold"))
	{
		if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Cannon, CollisionType::CT_OBB,
			std::bind(&Player::EnterCannon, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{
			StateManager.ChangeState("CannonInter");
			return;

		}
	}

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

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold" )) // 놓기
	{ 
		StateManager.ChangeState("HoldDown");
	}
	if (IsPotal_ == true)
	{
		return;
	}

	// Player object 를 든 상태로도 이동 가능하게 하기
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" ) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" ) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		RunningPuffTime_ += 1.0f * _DeltaTime;
		if (RunningPuffTime_ > 0.6f)
		{
			MakeRunningPuff(6);
		}
		CurAniName_ = PlayerName_[PlayerCustomNum] + "WalkHolding";
		PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] +"WalkHolding");
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		PlayerDirCheck();

		if (MoveAngle() == true)
		{

			// 플레이어 벽 출돌 체크
			if (PlayerMoveCollisionCheck(PlayerForwardCollision_) == true
				&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB) == false)
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
			if (PlayerMoveCollisionCheck(PlayerForwardCollision_) == true
				&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB) == false)
			{
				GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
			}
			return;
		}
	}
	else
	{
		CurAniName_ = PlayerName_[PlayerCustomNum] + "IdleHolding";
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
	GameEngineSound::SoundPlayOneShot("Item_PutDown_03.wav");
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
	CurAniName_ = PlayerName_[PlayerCustomNum] + "Chop";
}
void Player::SliceUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ColCheckPlayer();
	Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::TableSliceCheck, this, std::placeholders::_1, std::placeholders::_2));

	Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::InteractTableCheck, this, std::placeholders::_1, std::placeholders::_2));

	if (IsSlice_ == false)
	{
		StateManager.ChangeState("Idle");
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" ) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" ) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		StateManager.ChangeState("Move");
		return;
	}
}

void Player::DishWashStart(const StateInfo& _Info) // 설거지하는 도중 이동하면 취소됨
{
	WashRendererON();
	CurAniName_ = PlayerName_[PlayerCustomNum] + "Wash";
	PlayerWashRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Wash");
	PlayerWashRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerWashRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	CurStateType_ = PlayerCurStateType::DishWash;
	IsSink_ = true;

}
void Player::DishWashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Sink, CollisionType::CT_OBB,
		std::bind(&Player::TableSinkCheck, this, std::placeholders::_1, std::placeholders::_2));

	Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Sink, CollisionType::CT_OBB,
		std::bind(&Player::InteractTableCheck, this, std::placeholders::_1, std::placeholders::_2));

	ColCheckPlayer();
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" ) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" ) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" ))
	{
		StateManager.ChangeState("Move");
		return;
	}

	if (IsSink_ == false)
	{
		StateManager.ChangeState("Idle");
	}
}

void Player::FireOffStart(const StateInfo& _Info)
{

	CurStateType_ = PlayerCurStateType::FireOff;
	FireOff_ = true;
	CurAniName_ = PlayerName_[PlayerCustomNum] + "IdleHolding";
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "IdleHolding");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });

}
void Player::FireOffUpdate(float _DeltaTime, const StateInfo& _Info)
{

	ColCheckPlayer();
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerInteract" ))
	{
		StateManager.ChangeState("Hold");
		return;
	}

	{ //소화기 방향이동만 가능, 못움직임
		PlayerDirCheck();
		MoveAngle();
	}

}

void Player::DrowningStart(const StateInfo& _Info)
{
	IdleRendererON();
	CurAniName_ = PlayerName_[PlayerCustomNum] + "Drowning";
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Drowning");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	GameEngineSound::SoundPlayOneShot("Player_Dive_01.wav");

	DeathTime_ = 5.0f;
}
void Player::DrowningUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DeathTime_ -= 1.0f* _DeltaTime;
	if (DeathTime_ < 3.0f)
	{
		PlayerIdleRenderer_[PlayerCustomNum]->Off();
	}
	if (DeathTime_ <= 0.0f)
	{
		DetachPlayerHolding();
		GetTransform().SetWorldPosition(ResponePos_);
		StateManager.ChangeState("Idle");
		
	}
}

void Player::CannonInterStart(const StateInfo& _Info)
{

	IdleRendererON();
	CurAniName_ = PlayerName_[PlayerCustomNum] + "CannonEnter" + IsHolding_;
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CannonEnter"+ IsHolding_);
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetCurAnim()->bOnceEnd = false;
}
void Player::CannonInterUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerIdleRenderer_[PlayerCustomNum]->AnimationBindEnd(PlayerName_[PlayerCustomNum] + "CannonEnter"+ IsHolding_, [=](const GameEngineRenderingEvent& _Info)
		{
			CurAniName_ = PlayerName_[PlayerCustomNum] + "CannonIdle" + IsHolding_;
			PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CannonIdle"+ IsHolding_);
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		});


	
	GetTransform().SetWorldRotation({ CannonZAngle_, 90,0  });

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerDash" ))
	{
		
	
		IsCannon_ = false;
		GetTransform().SetWorldPosition({ -806.00, 100.0, -1111.00 });
		GetTransform().SetWorldRotation({ 0, 0, 0 });		
		CurDir_ = PlayerDir::Right;
		CurAngle_ = 90;
		GetTransform().SetLocalRotation({ 0,CurAngle_, 0 });
		IsPotal_ = false;
		StateManager.ChangeState("Idle");
		return;
	}

	if (IsCannonFly_ == true)
	{
		StateManager.ChangeState("CannonFly");
	}
}

void Player::CannonFlyStart(const StateInfo& _Info)
{
	IdleRendererON();
	GetTransform().SetWorldRotation({ 0, 0, 0 });
	CurDir_ = PlayerDir::Right;
	CurAngle_ = 90;
	GetTransform().SetLocalRotation({ 0,CurAngle_, 0 });
	CurAniName_ = PlayerName_[PlayerCustomNum] + "CannonFlying" + IsHolding_;
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CannonFlying"+ IsHolding_);
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetCurAnim()->bOnceEnd = false;
	CannonFlyPos_ = { -2170.0f, 100.0f , -1111.00 };
	IsPotal_ = true;
	FlyTime_ = 1.5f;
}
void Player::CannonFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (FlyTime_ >= 0.0f)
	{
		GetTransform().SetWorldUpMove(600.0f, _DeltaTime);
		FlyTime_ -= 1.0f * _DeltaTime;
	}
	else 
	{
		Gravity();
	}
	float4  Vec = CannonFlyPos_ - GetTransform().GetWorldPosition();
	if (GetTransform().GetWorldPosition().x <= -2150.0f)
	{
		IsCannonFly_ = false;
		IsPotal_ = false;
		StateManager.ChangeState("Idle");
	}
	Vec.Normalize3D();
	Vec.y = 0;
	GetTransform().SetWorldMove(Vec * 700.0f * GameEngineTime::GetDeltaTime());

}

void Player::CarDeathStart(const StateInfo& _Info)
{
	IdleRendererON();
	CurAniName_ = PlayerName_[PlayerCustomNum] + "CarDeath";
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CarDeath");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetCurAnim()->bOnceEnd = false;

	GameEngineSound::SoundPlayOneShot("PlayerSlip_01.wav");
	DeathTime_ = 5.0f;
	IsDeath_ = 1;
}
void Player::CarDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DeathTime_ -= 1.0f * _DeltaTime;

	for (int i = 0; i < 5; i++)
	{
		PixelData& Renderer = PlayerIdleRenderer_[PlayerCustomNum]->GetPixelDatas(i);
		if (Renderer.MulColor.a > 0.0f)
		{
			Renderer.AlphaFlag = 1;
			Renderer.AlphaColor.a -= 0.3f * _DeltaTime;
			Renderer.MulColor.a -= 0.3f * _DeltaTime;
		}
	}



	if (DeathTime_ < 0.0f)
	{
		DetachPlayerHolding();
		GetTransform().SetWorldPosition(ResponePos_);
		IsDeath_ = 2;
		for (int i = 0; i < 5; i++)
		{
			PixelData& IdleRender = PlayerIdleRenderer_[PlayerCustomNum]->GetPixelDatas(i);
			IdleRender.MulColor.a =1.0f;
			IdleRender.AlphaColor.a = 1.0f;
		}
		GameEngineSound::SoundPlayOneShot("PlayerSpawn_01.wav");
		StateManager.ChangeState("Idle");

	}
}