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


	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //��Ʈ��Ű
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
				if (Interact_TableObject_->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard) // �����϶�
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
		// �÷��̾� �� �⵹ üũ
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false &&
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
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
	{ //��Ʈ�� Ű�� ���� ������ �ȴ�����, �����̵� ����
		PlayerDirCheck();
		MoveAngle();
	}

	if (true == GameEngineInput::GetInst()->IsUpKey("PlayerInteract"))
	{
		//������ �ൿ
		// Throw �ִϸ��̼�
		IdleRendererON();
		PlayerIdleRenderer_->ChangeAnimation(PlayerName_ + "Throw");
		PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
		PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });

	}
	PlayerIdleRenderer_->AnimationBindEnd(PlayerName_+"Throw", [=](const GameEngineRenderingEvent& _Info)
		{
			// CurrentHoldingObject - �θ��ڽİ��� ����, �Ǻ� ������� ������
			// CurrentHoldingObject -> ���⼭ Throw �Լ� ���ָ� �ȴ�. 
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
		// �÷��̾� �տ� �ƹ��͵� ������
	{
		if (Interact_GroundObject_ != nullptr) // ���� ��ȣ�ۿ��ϴ� ������Ʈ�� ������
		{
			if (Input_PickUp(Interact_GroundObject_) == Input_PickUpOption::PickUp) //��ȣ�ۿ밡���� ���� ������Ʈ�� ���� �� �ִ°��϶�
			//if (Interact_GroundObject_->Input_PickUp(std::dynamic_pointer_cast<Player>(shared_from_this())) == Input_PickUpOption::PickUp) //��ȣ�ۿ밡���� ���� ������Ʈ�� ���� �� �ִ°��϶�
			{ // �ٴڿ� �ִ� ������Ʈ�� �θ� �����Ƿ� SetParent�� �ص���
				CurrentHoldingObject_->SetParent(shared_from_this());
				CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-60 });
				return;
			}

		}

		else if (Interact_TableObject_ != nullptr) // �տ� ���̺��� ������
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
				if (Interact_TableObject_->GetStaticObjectType() == MapObjType::FoodBox) // ���� ������
				{
					Interact_TableObject_->CastThis<FoodBox>()->SwitchIsInteraction();
					StateManager.ChangeState("Idle"); // �����ߵ�
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
	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerInteract")) //��Ʈ��Ű
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

	if (true == GameEngineInput::GetInst()->IsDownKey("PlayerHold")) // ����
	{ 
		if (FireOff_ == true)
		{
			FireOff_ = false;
		}

		if (Interact_TableObject_->GetStaticObjectType() == MapObjType::TrashCan) // ���� ������
		{
			//Interact_TableObject_->CastThis<TrashCan>()->������ ���();
			StateManager.ChangeState("Idle");
			return;
		}


		if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false) //
		{
			// ������-> �ٴڿ� ����
			CurrentHoldingObject_->GetCollisionObject()->On();
			CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,0,0});
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_ = nullptr;
			StateManager.ChangeState("Idle");
			return;
		}
		else // �տ� ���̺��� ������
		{
			if (Interact_TableObject_->GetStuff() == nullptr) // ���̺� �ְ� ���̺� �÷��� ������ ������
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

			else if (Interact_TableObject_->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard) // �����϶�
			{
				return;
			}
			else if (CurrentHoldingObject_ != nullptr && Interact_TableObject_->GetStuff() != nullptr) // �ϴ� �������뿹��ó��
			{
				return;
			}
		}
		return;
	}


	// Player object �� �� ���·ε� �̵� �����ϰ� �ϱ�
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

void Player::SliceStart(const StateInfo& _Info) // �ڸ��� ���� �̵��ϸ� ��ҵ�
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

	{ //��ȭ�� �����̵��� ����, ��������
		PlayerDirCheck();
		MoveAngle();
	}


}