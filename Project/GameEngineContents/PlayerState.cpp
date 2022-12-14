#include "PreCompile.h"
#include "Player.h"
#include "FoodBox.h"
#include "TrashCan.h"
#include "Equipment_Plate.h"

#include <math.h>

void Player::IdleStart(const StateInfo& _Info)
{
	
	IsHolding_ = "Idle";
	CurStateType_ = PlayerCurStateType::Idle;
	IdleRendererON();		
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] +"Idle");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });

	Speed_ = 650.0f;
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ColCheckPlayer();

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
	{
		if (IsPotal_ == false)
		{
			StateManager.ChangeState("Move");
			
		}
	}

	
	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold" + PNumString))
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
		//��������ȣ�ۿ�
		//else if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Sink, CollisionType::CT_OBB,
		//	std::bind(&Player::EnterCannon, this, std::placeholders::_1, std::placeholders::_2)) == true)
		//{
		//	StateManager.ChangeState("DishWash");
		//}
		else
		{
			StateManager.ChangeState("HoldUp");
			return;
		}
	}


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract" + PNumString)) //��Ʈ��Ű
	{
		if (CurrentHoldingObject_ == nullptr) // �տ� �ƹ��͵� ������
		{
			Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::TableSliceCheck, this, std::placeholders::_1, std::placeholders::_2)); // ���� �˻�
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
	if (IsPotal_ == true)
	{
		StateManager.ChangeState("Idle");

	}
	if (MoveAngle() == true)
	{
		// �÷��̾� �� �⵹ üũ
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false
			&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
				std::bind(&GamePlayPhysics::PullPlayer, this, std::placeholders::_1, std::placeholders::_2))==false)
		{
			GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
		}
		else
		{
			// �÷��̾ ���̶� �浹������ �밢�� Ű ������ �÷��̾� �з��� �̵��ϴ� �Լ�
			MoveCollisionSideCheck(_DeltaTime);
		}
	}

	else
	{
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false
			&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
				std::bind(&GamePlayPhysics::PullPlayer, this, std::placeholders::_1, std::placeholders::_2)) == false)
		{
			GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
		}
		return;
	}

}
void Player::ThrowStart(const StateInfo& _Info)
{
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Idle");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	IsThrow_ = false;
}
void Player::ThrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerIdleRenderer_[PlayerCustomNum]->AnimationBindEnd(PlayerName_[PlayerCustomNum] + "Throw", [=](const GameEngineRenderingEvent& _Info)
		{
			PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Idle");
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		});

	CurStateType_ = PlayerCurStateType::Throw;
	{ //��Ʈ�� Ű�� ���� ������ �ȴ�����, �����̵� ����
		PlayerDirCheck();
		MoveAngle();
	}

	if (true == GameEngineInput::GetInst()->IsUpKey("PlayerInteract" + PNumString))
	{
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
		if (CurrentHoldingObject_->CastThis<GamePlayPhysics>()->GetIsThrow() == true) // �ϴ� Throw �ּ�ó��
		{
			CurrentHoldingObject_->CastThis<GamePlayPhysics>()->Throw(ThrowVec_);
		}
		else
		{
			CurrentHoldingNull();
			//CurHoldType_ = PlayerHoldType::Max;
			StateManager.ChangeState("Idle");
		}
	}


}

void Player::HoldUpStart(const StateInfo& _Info)
{
	ColCheckPlayer();
	if (CurrentHoldingObject_ == nullptr)
	{
		CurStateType_ = PlayerCurStateType::HoldUp;
		if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
			std::bind(&Player::GroundHoldUpCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)//�ٴڿ� ����ִ�  ������ ������
		{
			if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::TableHoldUpCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				StateManager.ChangeState("Idle");
				return;
			}// ���̺� �˻�
			IsHolding_ = "Holding";
		}
	}

}
void Player::HoldUpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract" + PNumString)) //��Ʈ��Ű
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

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold" + PNumString)) // ����
	{ 
		StateManager.ChangeState("HoldDown");
	}
	if (IsPotal_ == true)
	{
		return;
	}

	// Player object �� �� ���·ε� �̵� �����ϰ� �ϱ�
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
			// �÷��̾� �� �⵹ üũ
			if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
				PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false
				&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
					std::bind(&GamePlayPhysics::PullPlayer, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
			}
			else
			{
				// �÷��̾ ���̶� �浹������ �밢�� Ű ������ �÷��̾� �з��� �̵��ϴ� �Լ�
				MoveCollisionSideCheck(_DeltaTime);
			}
		}

		else
		{
			if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
				PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false
				&& PlayerCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
					std::bind(&GamePlayPhysics::PullPlayer, this, std::placeholders::_1, std::placeholders::_2)) == false)
			{
				GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.5f * _DeltaTime);
			}
			return;
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
void Player::SliceStart(const StateInfo& _Info) // �ڸ��� ���� �̵��ϸ� ��ҵ�
{
	CurStateType_ = PlayerCurStateType::Slice;
	IsSlice_ = true;
	ChopRendererON();
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

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
	{
		StateManager.ChangeState("Move");
		return;
	}
}

void Player::DishWashStart(const StateInfo& _Info) // �������ϴ� ���� �̵��ϸ� ��ҵ�
{
	WashRendererON();
	PlayerWashRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Wash");
	PlayerWashRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerWashRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	CurStateType_ = PlayerCurStateType::DishWash;
	IsSink_ = true;

}
void Player::DishWashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ColCheckPlayer();
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
	{

		StateManager.ChangeState("Idle");
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
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "IdleHolding");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });

}
void Player::FireOffUpdate(float _DeltaTime, const StateInfo& _Info)
{

	ColCheckPlayer();
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerInteract" + PNumString))
	{
		StateManager.ChangeState("Hold");
		return;
	}

	{ //��ȭ�� �����̵��� ����, ��������
		PlayerDirCheck();
		MoveAngle();
	}

}

void Player::DrowningStart(const StateInfo& _Info)
{
	IdleRendererON();
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Drowning");
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });

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
		CurrentHoldingDetach();
		GetTransform().SetWorldPosition(ResponePos_);
		StateManager.ChangeState("Idle");
		
	}
}

void Player::CannonInterStart(const StateInfo& _Info)
{
	//CurCannon_->SetPlayer(std::dynamic_pointer_cast<Player>(shared_from_this()));		// �׽�Ʈ
	IdleRendererON();
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CannonEnter"+ IsHolding_);
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetCurAnim()->bOnceEnd = false;
}
void Player::CannonInterUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerIdleRenderer_[PlayerCustomNum]->AnimationBindEnd(PlayerName_[PlayerCustomNum] + "CannonEnter"+ IsHolding_, [=](const GameEngineRenderingEvent& _Info)
		{
			PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CannonIdle"+ IsHolding_);
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		});


	
	GetTransform().SetWorldRotation({ 270, 0, CannonZAngle_ });

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerDash" + PNumString))
	{
		
		//CurCannon_->ResetPlayer();	// �׽�Ʈ
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
	PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "CannonFlying"+ IsHolding_);
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
	PlayerIdleRenderer_[PlayerCustomNum]->GetCurAnim()->bOnceEnd = false;
	CannonFlyPos_ = { -2150.0f, 100.0f , -1111.00 };
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