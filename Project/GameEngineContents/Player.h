#pragma once

#include "Enums.h"
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineStateManager.h>
#include "GamePlayPhysics.h"
#include "Cannon.h"

// 설명 :
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

	void DrowningStart(const StateInfo& _Info);
	void DrowningUpdate(float _DeltaTime, const StateInfo& _Info);

	void CannonInterStart(const StateInfo& _Info);
	void CannonInterUpdate(float _DeltaTime, const StateInfo& _Info);

	void CannonFlyStart(const StateInfo& _Info);
	void CannonFlyUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashCheck(float _DeltaTime);
	void PlayerDirCheck();
	bool MoveAngle();

	void MoveCollisionSideCheck(float _DeltaTime);
	

public:
	inline std::shared_ptr<GameEngineCollision> GetInteractCollision() const
	{
		return Collision_Interact_;
	}

	void ChangePlayer(); // 플레이어 커스텀 바꾸는 함수
	void ChangePlayerColor();

public:
	

	inline void SetPlayerHolding(std::shared_ptr<GameEngineUpdateObject> _CurrentHoldingObject_) // 플레이어 손에 올리는 함수 엑터를 손에올려줍니다
	{
		CurrentHoldingObject_ = _CurrentHoldingObject_->CastThis<GameEngineActor>();
		if (CurrentHoldingObject_->GetParent() != nullptr)
		{
			CurrentHoldingObject_->DetachObject();
		}
		CurrentHoldingObject_->SetParent(shared_from_this());
		CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,60,-60 });
	}

	inline void SetCurHoldType(PlayerHoldType _CurHoldType) // 손에 쥐어줄때 무슨 플레이어가 타입인지 알려주는 함수
	{
		CurHoldType_ = _CurHoldType;
	}
	

	std::shared_ptr<GameEngineActor> GetPlayerHolding()// 현재 플레이어 손에있는 오브젝트 얻는 함수
	{
		return CurrentHoldingObject_;
	}

	inline void DetachPlayerHolding() // 플레이어 손에든 함수 부모자식 관계 해제하는 함수 , 콜리젼은 알아서 on해줘야함
	{
		if (CurrentHoldingObject_ != nullptr)
		{ //table위에 올릴때는 외부에서 ToolPos로 얻어와서 따로 설정해주어야 한다.

			//CurrentHoldingObject_->GetTransform().SetLocalPosition(float4{ 0,0,0 });
			CurrentHoldingObject_->DetachObject();
			CurrentHoldingObject_ = nullptr;
		}

	}

	inline void CurrentHoldingNull()
	{
		if (CurrentHoldingObject_ != nullptr)
		{
			CurrentHoldingObject_ = nullptr;
		}

	}

	inline void CurrentHoldingDetach()
	{
		if (CurrentHoldingObject_ != nullptr)
		{
			CurrentHoldingObject_->DetachObject();
		}

	}

	/// 다 잘랐다고 플레이어에게 알려주는 함수 -> 플레이어가 Slice상태에서 idle상태로 변환한다.
	inline void FinishSlice()
	{
		IsSlice_ = false;
	}

	inline void FinishSink()
	{
		IsSink_ = false;
	}

	inline void SetCurFrontDir()
	{
		CurDir_ = PlayerDir::Front;
		CurAngle_ = 180.0f;
	}

	bool IsSingleMode;
	bool IsPotal_;



	bool IsCannonFly_;
	bool IsCannon_;
	float FlyTime_;
	float CannonZAngle_;




	std::string PNumString;
	std::string IsHolding_;
	
	void PNumSgtringUpdate();

	inline void SetResponePos(float4 _Pos)
	{
		ResponePos_ = _Pos;
	}

private:

	void DetachPlayerHoldingToGround();
	void CustomKeyCheck();

	void IdleRendererON();
	void WalkRendererON();
	void ChopRendererON();
	void WashRendererON();



	//충돌함수
	CollisionReturn GravityColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MoveColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn TableHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GroundHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn TableHoldDownCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn TableSliceCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn InteractTableCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn EnterCannon(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	std::shared_ptr<GameEngineActor> CurrentHoldingObject_;
	std::shared_ptr<GameEngineCollision> TableCollision_;
	std::shared_ptr<GameEngineCollision> Collision_Interact_; // 상호작용 콜리전

private:
	float4 CannonFlyPos_;

	void CameraMove(float _DeltaTime);
	bool IsCameraMove_;
	bool IsThrow_;
	float4 ThrowVec_;
	float CameraUpTime_;
	float CameraDownTime_;
	float Speed_;
	float CurAngle_;
	PlayerDir CurDir_;
	PlayerHoldType CurHoldType_;
	PlayerCurStateType CurStateType_;
	int PlayerPNum;
	float DashTime_;
	bool FireOff_;
	bool IsSlice_;
	bool IsSink_;

	float DeathTime_;
	float4 ResponePos_;

	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerIdleRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerWalkRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerChopRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerWashRenderer_[6];

	int PlayerCustomNum;
	std::string PlayerName_[6];

	std::shared_ptr<GameEngineCollision> PlayerFloorCollision_;
	std::shared_ptr<GameEngineCollision> PlayerForwardLeftCollision_;
	std::shared_ptr<GameEngineCollision> PlayerForwardRightCollision_;
	std::shared_ptr<GameEngineCollision> PlayerForwardCollision_;

	std::shared_ptr<GameEngineCollision> PlayerRightCollision_;
	std::shared_ptr<GameEngineCollision> PlayerLeftCollision_;
	std::shared_ptr<GameEngineCollision> PlayerBackCollision_;

	std::shared_ptr<GameEngineCollision> PlayerCollision_;
	std::shared_ptr<GameEngineCollision> PlayerCameraCollision_;


	GameEngineStateManager StateManager;
};

