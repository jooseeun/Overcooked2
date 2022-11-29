#pragma once

#include "Enums.h"
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineStateManager.h>
#include "GamePlayPhysics.h"

// ���� :
class GameEngineFBXAnimationRenderer;
class GameEngineFBXStaticRenderer;
class GameEngineCollision;
class GamePlayMoveable;
class GamePlayStaticObject;
class Player : public GamePlayPhysics
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void LevelStartEvent() override;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void ThrowStart(const StateInfo& _Info);
	void ThrowUpdate(float _DeltaTime, const StateInfo& _Info);

	void HoldUpStart(const StateInfo& _Info);
	void HoldUpUpdate(float _DeltaTime, const StateInfo& _Info);

	void HoldDownStart(const StateInfo& _Info);
	void HoldDownUpdate(float _DeltaTime, const StateInfo& _Info);

	void SliceStart(const StateInfo& _Info);
	void SliceUpdate(float _DeltaTime, const StateInfo& _Info);

	void DishWashStart(const StateInfo& _Info);
	void DishWashUpdate(float _DeltaTime, const StateInfo& _Info);

	void FireOffStart(const StateInfo& _Info);
	void FireOffUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashCheck();
	void PlayerDirCheck();
	bool MoveAngle();

	void MoveCollisionSideCheck(float _DeltaTime);



	

public:
	inline std::shared_ptr<GameEngineCollision> GetInteractCollision() const
	{
		return Collision_Interact_;
	}


	inline float GetCurKineticEnergy() const
	{
		return CurKineticEnergy_;
	}

	void ChangePlayer(); // �÷��̾� Ŀ���� �ٲٴ� �Լ�
	void ChangePlayerColor();
	

public:
	
	//inline void SetPlayerHolding(std::shared_ptr<GameEngineActor> _CurrentHoldingObject_) // �÷��̾� �տ� �ø��� �Լ� ���͸� �տ��÷��ݴϴ�
	//{
	//	CurrentHoldingObject_ = _CurrentHoldingObject_;
	//	if (CurrentHoldingObject_->GetParent() != nullptr)
	//	{
	//		CurrentHoldingObject_->DetachObject();
	//	}
	//	CurrentHoldingObject_->SetParent(shared_from_this());
	//	CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-60 });
	//}

	inline void SetPlayerHolding(std::shared_ptr<GameEngineUpdateObject> _CurrentHoldingObject_) // �÷��̾� �տ� �ø��� �Լ� ���͸� �տ��÷��ݴϴ�
	{
		CurrentHoldingObject_ = _CurrentHoldingObject_->CastThis<GameEngineActor>();
		if (CurrentHoldingObject_->GetParent() != nullptr)
		{
			CurrentHoldingObject_->DetachObject();
		}
		CurrentHoldingObject_->SetParent(shared_from_this());
		CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,60,-60 });
	}

	inline void SetCurHoldType(PlayerHoldType _CurHoldType) // �տ� ����ٶ� ���� �÷��̾ Ÿ������ �˷��ִ� �Լ�
	{
		CurHoldType_ = _CurHoldType;
	}
	

	std::shared_ptr<GameEngineActor> GetPlayerHolding() const // ���� �÷��̾� �տ��ִ� ������Ʈ ��� �Լ�
	{
		return CurrentHoldingObject_;
	}

	inline void DetachPlayerHolding() // �÷��̾� �տ��� �Լ� �θ��ڽ� ���� �����ϴ� �Լ� , �ݸ����� �˾Ƽ� on�������
	{
		if (CurrentHoldingObject_ != nullptr)
		{
			CurrentHoldingObject_->GetTransform().SetWorldPosition(GetTransform().GetLocalPosition() + GetTransform().GetBackVector() * 60.0f + float4{ 0,50,0 });
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_ = nullptr;
		}

	}
	

private:

	float Speed_;
	float CurKineticEnergy_;
	float CurAngle_;
	PlayerDir CurDir_;
	PlayerHoldType CurHoldType_;
	PlayerCurStateType CurStateType_;
	int PlayerPNum;
	bool FireOff_;

	//�浹�Լ�
	CollisionReturn GravityColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MoveColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn TableHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GroundHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn TableHoldDownCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn TableSliceCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	std::shared_ptr<GameEngineActor> CurrentHoldingObject_;
	std::shared_ptr<GameEngineCollision> Collision_Interact_; // ��ȣ�ۿ� �ݸ���


	void CalculateKineticEnergy();

	void IdleRendererON();
	void WalkRendererON();
	void ChopRendererON();
	void WashRendererON();

	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerIdleRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerWalkRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerChopRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerWashRenderer_[6];

	int PlayerCustomNum;
	std::string PlayerName_[6];

	std::shared_ptr<GameEngineCollision> PlayerFloorCollision_;
	std::shared_ptr<GameEngineCollision> PlayerForwardCollision_;
	std::shared_ptr<GameEngineCollision> PlayerForwardLeftCollision_;
	std::shared_ptr<GameEngineCollision> PlayerForwardRightCollision_;

	//�ӽ� �ݸ���
	std::shared_ptr<GameEngineCollision> PlayerLeftCollision_;
	std::shared_ptr<GameEngineCollision> PlayerRightCollision_;
	std::shared_ptr<GameEngineCollision> PlayerBackCollision_;


	GameEngineStateManager StateManager;
};

