#include "PreCompile.h"
#include "Player.h"


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

}
void Player::HoldUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold"))
	{
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