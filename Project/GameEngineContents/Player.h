#pragma once

#include "Enums.h"
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineStateManager.h>
#include "GamePlayPhysics.h"
#include "GameServerObject.h"
#include "Cannon.h"

// ���� :
class GameEngineDefaultRenderer;
class GameEngineFBXAnimationRenderer;
class GameEngineFBXStaticRenderer;
class GameEngineCollision;
class GamePlayMoveable;
class GamePlayStaticObject;
class Player : public GamePlayPhysics, public GameServerObject
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

	void CarDeathStart(const StateInfo& _Info);
	void CarDeathUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashCheck(float _DeltaTime);
	void PlayerDirCheck();
	bool MoveAngle();

	void MoveCollisionSideCheck(float _DeltaTime);

public:
	inline std::shared_ptr<GameEngineCollision> GetInteractCollision() const
	{
		return Collision_Interact_;
	}

	void ChangePlayer(); // �÷��̾� Ŀ���� �ٲٴ� �Լ�
	void ChangePlayerColor();

public:
	
	inline void SetPlayerHolding(std::shared_ptr<GameEngineUpdateObject> _CurrentHoldingObject_) // �÷��̾� �տ� �ø��� �Լ� ���͸� �տ��÷��ݴϴ�
	{
		CurrentHoldingObject_ = _CurrentHoldingObject_->CastThis<GameEngineActor>();
		if (CurrentHoldingObject_->GetParent() != nullptr)
		{
			CurrentHoldingObject_->DetachObject();
		}
		CurrentHoldingObject_->SetParent(shared_from_this());
		CurrentHoldingObject_->GetTransform().SetLocalPosition({ 0,60,-60 });
		CurrentHoldingObject_->CastThis<GamePlayObject>()->GetCollisionObject()->Off();
	}

	inline void SetCurHoldType(PlayerHoldType _CurHoldType) // �տ� ����ٶ� ���� �÷��̾ Ÿ������ �˷��ִ� �Լ�
	{
		CurHoldType_ = _CurHoldType;
	}
	

	std::shared_ptr<GameEngineActor> GetPlayerHolding()// ���� �÷��̾� �տ��ִ� ������Ʈ ��� �Լ�
	{
		return CurrentHoldingObject_;
	}

	inline void DetachPlayerHolding() // �÷��̾� �տ��� �Լ� �θ��ڽ� ���� �����ϴ� �Լ� , �ݸ����� �˾Ƽ� on�������
	{
		if (CurrentHoldingObject_ != nullptr)
		{ //table���� �ø����� �ܺο��� ToolPos�� ���ͼ� ���� �������־�� �Ѵ�.

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

	/// �� �߶��ٰ� �÷��̾�� �˷��ִ� �Լ� -> �÷��̾ Slice���¿��� idle���·� ��ȯ�Ѵ�.
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


	bool IsPotal_;


	int IsMove_;
	bool IsCannonFly_;
	bool IsCannon_;
	float FlyTime_;
	float CannonZAngle_;
	int PlayerPNum;
	float RunningPuffTime_;
	float RunningPuffServerTime_;

	int IsThrowHolding_;
	bool ThrowHolding(std::shared_ptr<GameEngineUpdateObject> _HoldingObject);


	std::string CurAniName_;
	std::string IsHolding_;
	


	inline void SetResponePos(float4 _Pos)
	{
		ResponePos_ = _Pos;
	}

private:
	bool PlayerMoveCollisionCheck(std::shared_ptr<GameEngineCollision> _Col);
	void DetachPlayerHoldingToGround();
	void CustomKeyCheck();

	void IdleRendererON();
	void WalkRendererON();
	void ChopRendererON();
	void WashRendererON();

	void DeathCheck();
	void GravityCheck(float _DeltaTime);
	void IcePlatformCheck(float _DeltaTime);
	void MakeRunningPuff(int _Count);
	//�浹�Լ�

	CollisionReturn TableHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GroundHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn TableHoldDownCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn TableSliceCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn TableSinkCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn InteractTableCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	CollisionReturn EnterCannon(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn PushButton(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn HighlihgtMoveAbleCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn HighlihgtStaticCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	std::shared_ptr<GameEngineActor> CurrentHoldingObject_;
	std::shared_ptr<GameEngineActor> CurrentThrowObject_;

	std::shared_ptr<GameEngineCollision> HighLightMoveAbleObject_;
	std::shared_ptr<GameEngineCollision> HighLightStaticObject_;

	std::shared_ptr<GameEngineCollision> TableCollision_;
	std::shared_ptr<GameEngineCollision> Collision_Interact_; // ��ȣ�ۿ� �ݸ���

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


	int ServerRenderStateNum_;
	int PlayerCustomNum;
	int ServerCustomNum;
	float DashTime_;

	bool FireOff_;
	bool IsSlice_;
	bool IsSink_;

	float DeathTime_;
	int IsDeath_;
	float4 ResponePos_;

	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerIdleRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerWalkRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerChopRenderer_[6];
	std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerWashRenderer_[6];


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

	//////// ���� 
private:
	static std::shared_ptr<Player> MyPlayer;
	static bool OnePlayerInit;
	bool IsPlayerble;

	void ServerStart();
	void ServerUpdate(float _DeltaTime);

public:
	static int MaxPlayerCount_;
	static int PlayerCount_;
	static std::shared_ptr<Player> GetMyPlayer()
	{
		return MyPlayer;
	}

	static void SetMyPlayer(std::shared_ptr<Player> _Player)
	{
		MyPlayer = _Player;
	}
};

