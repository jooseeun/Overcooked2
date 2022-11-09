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


	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerInteract")) //��Ʈ��Ű
	{
		if (CurrentHoldingObject_ != nullptr)
			//�տ� ���� ������
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
			//�տ� �ƹ��͵� ������
		{
			//���� Ÿ�� �˻�
			//Interact_TableObject_->Input_PickUp(this) == Input_PickUpOption::PickUp;
			//������, ���������� �ϳ�


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
		// �÷��̾� �� �⵹ üũ
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Map_Object, CollisionType::CT_AABB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_AABB, CollisionOrder::Object_StaticObject, CollisionType::CT_AABB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
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
		//������ ������ ���� ����
		CurHoldType_ = PlayerHoldType::Max;
		StateManager.ChangeState("Idle");
	}
}

void Player::HoldStart(const StateInfo& _Info)
{
	if (CurrentHoldingObject_ == nullptr &&
		Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
			std::bind(&Player::GetCrashGroundObject, this, std::placeholders::_1, std::placeholders::_2)))
		// �÷��̾ ����ִ°� ���� �˻� �ݸ����� �ٴڿ� ������ ������Ʈ �ݸ����� ���������
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
		// �˻� �ݸ����� ���̺� �ݸ����� ���������
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
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold")) // ����
	{
		CurrentHoldingObject_->GetTransform().DetachTransform(); // �ڽ� �����
		StateManager.ChangeState("Idle");
	}

	

}

void Player::SliceStart(const StateInfo& _Info) // �ڸ��� ���� �̵��ϸ� ��ҵ�
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

void Player::DishWashStart(const StateInfo& _Info) // �������ϴ� ���� �̵��ϸ� ��ҵ�
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

	{ //��ȭ�� �����̵��� ����, ��������
		PlayerDirCheck();
		MoveAngle();
	}
	

}