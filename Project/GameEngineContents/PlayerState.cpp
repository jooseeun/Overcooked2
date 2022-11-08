#include "PreCompile.h"
#include "Player.h"
#include "GamePlayFood.h"
#include "GamePlayStaticObject.h"

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
		StateManager.ChangeState("Hold");
	}


	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerInteract"))
	{
		if (CurHoldType_ == PlayerHoldType::CanThrow)
		{
			StateManager.ChangeState("Throw");
		}
		else if (CurHoldType_ == PlayerHoldType::FireExtinguisher)
		{
			StateManager.ChangeState("FireOff");
		}
		else if (CurHoldType_ == PlayerHoldType::Max)
		{
			//�տ� �ƹ��͵� ������
			//���� Ÿ�� �˻�
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
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
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
	if (Moveable_Current_ == nullptr &&
		Collision_Interact_->IsCollision(CollisionType::CT_SPHERE, CollisionOrder::Object_Moveable, CollisionType::CT_SPHERE,
			std::bind(&Player::GetCrashGroundObject, this, std::placeholders::_1, std::placeholders::_2)))
		// �÷��̾ ����ִ°� ���� �˻� �ݸ����� ���� �� �ִ� �ݸ����� ���������
	{

		if (Moveable_Current_ == nullptr &&
			Interact_Possible_Object_->Input_PickUp(this) == Input_PickUpOption::PickUp)
		{
			Interact_Possible_Object_ = nullptr;
			Moveable_Current_->GetTransform().SetParentTransform(Moveable_Current_->GetTransform());
			return;
		}

	}
	else
	{
		if (Interact_Possible_Object_ != nullptr)
		{
			Interact_Possible_Object_->SetBloomEffectOff();
			Interact_Possible_Object_ = nullptr;
			Moveable_Current_->GetTransform().SetParentTransform(Moveable_Current_->GetTransform());
		}
	}



	if (Collision_Interact_->IsCollision(CollisionType::CT_SPHERE, CollisionOrder::Object_StaticObject, CollisionType::CT_SPHERE,
		std::bind(&Player::GetCrashTableObject, this, std::placeholders::_1, std::placeholders::_2)))
	{

		if (Moveable_Current_ == nullptr &&
			Interact_Possible_StaticObject_->Input_PickUp(this) == Input_PickUpOption::PickUp)
		{
			Interact_Possible_StaticObject_->SetBloomEffectOff();
			return;
		}

	}

	else
	{
		if (Interact_Possible_StaticObject_ != nullptr)
		{
			Interact_Possible_StaticObject_->SetBloomEffectOff();
			Interact_Possible_StaticObject_ = nullptr;
			Moveable_Current_->GetTransform().SetParentTransform(Moveable_Current_->GetTransform());
		}
	}
}
void Player::HoldUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold")) // ����
	{
		Moveable_Current_->GetTransform().DetachTransform(); // �ڽ� �����
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