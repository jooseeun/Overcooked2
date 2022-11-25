#pragma once
#include "GamePlayObject.h"
#include "Enums.h"
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineStateManager.h>

// 설명 :
class GameEngineFBXAnimationRenderer;
class GameEngineFBXStaticRenderer;
class GameEngineCollision;
class GamePlayMoveable;
class GamePlayStaticObject;
class Player : public GameEngineActor
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

	void Gravity();
	void MoveCollisionSideCheck(float _DeltaTime);



	

public:
	inline std::shared_ptr<GameEngineCollision> GetInteractCollision() const
	{
		return Collision_Interact_;
	}

	inline void SetCurHoldType(PlayerHoldType _CurHoldType)
	{
		CurHoldType_ = _CurHoldType;
	}

	inline float GetCurKineticEnergy()
	{
		return CurKineticEnergy_;
	}

	inline void ChangePlayer()
	{
		PlayerIdleRenderer_[PlayerCustomNum]->Off();
		PlayerWalkRenderer_[PlayerCustomNum]->Off();
		PlayerChopRenderer_[PlayerCustomNum]->Off();
		PlayerWashRenderer_[PlayerCustomNum]->Off();

		PlayerCustomNum += 1;
		if (PlayerCustomNum == 6)
		{
			PlayerCustomNum = 0;
		}

		PlayerIdleRenderer_[PlayerCustomNum]->On();
		PlayerWalkRenderer_[PlayerCustomNum]->Off();
		PlayerChopRenderer_[PlayerCustomNum]->Off();
		PlayerWashRenderer_[PlayerCustomNum]->Off();
			

	}

	

public:
	
	template <typename HoldingType>
	void SetPlayerHolding(HoldingType _CurrentHoldingObject_) // 플레이어 손에 올리는 함수
	{
		CurrentHoldingObject_ = _CurrentHoldingObject_;
		if (CurrentHoldingObject_->SetParent == nullptr)
		{
			CurrentHoldingObject_->DetachObject();
		}
		CurrentHoldingObject_->SetParent(shared_from_this());
		CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,50,-60 });
	}
	template <typename HoldingType>
	std::shared_ptr<HoldingType> GetPlayerHolding() // 현재 플레이어 손에있는 오브젝트 얻는 함수
	{
		return CurrentHoldingObject_;
	}

	inline void DetachPlayerHolding() // 플레이어 손에든 함수 부모자식 관계 해제하는 함수 , 콜리젼은 알아서 on해줘야함
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
	int PlayerP;
	bool FireOff_;

	//충돌함수
	CollisionReturn GravityColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MoveColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn TableHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GroundHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn TableHoldDownCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	std::shared_ptr<GameEngineActor> CurrentHoldingObject_;
	std::shared_ptr<GameEngineCollision> Collision_Interact_; // 상호작용 콜리전


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

	//임시 콜리젼
	std::shared_ptr<GameEngineCollision> PlayerLeftCollision_;
	std::shared_ptr<GameEngineCollision> PlayerRightCollision_;
	std::shared_ptr<GameEngineCollision> PlayerBackCollision_;


	GameEngineStateManager StateManager;
};

