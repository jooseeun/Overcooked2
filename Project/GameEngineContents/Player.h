#pragma once
#include "GamePlayObject.h"
#include "Enums.h"

// 설명 :
class GameEngineFBXAnimationRenderer;
class GameEngineFBXStaticRenderer;
class GameEngineCollision;
class GamePlayMoveable;
class GamePlayStaticObject;
class Player : public GamePlayObject
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

	void HoldStart(const StateInfo& _Info);
	void HoldUpdate(float _DeltaTime, const StateInfo& _Info);

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


	//충돌함수
	CollisionReturn GetCrashGroundObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GetCrashTableObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn GravityColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MoveColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn PutUpObjectTable(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	
public:
	inline Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override { return Input_PickUpOption::NoResponse; }
	inline Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override
	{
		CurrentHoldingObject_ = _Object;
		//	Moveable_Current_->SetBloomEffectOff();
		return Input_PickUpOption::PickUp;
	}
	inline std::shared_ptr<GameEngineCollision> GetInteractCollision() const
	{
		return Collision_Interact_;
	}

	inline void SetCurHoldType(PlayerHoldType _CurHoldType)
	{
		CurHoldType_ = _CurHoldType;
	}


public:
	inline void SetBloomEffectOff() override
	{
		MsgBoxAssert("예방코드 / 캐릭터 블룸 미적용")
	}
	inline void SetBloomEffectOn() override
	{
		MsgBoxAssert("예방코드 / 캐릭터 블룸 미적용")
	}
private:
	float Speed_;
	float CurAngle_;
	PlayerDir CurDir_;
	PlayerHoldType CurHoldType_;

	std::shared_ptr<GameEngineCollision> Collision_Interact_; // 상호작용 콜리전
	std::shared_ptr<GamePlayMoveable> Interact_GroundObject_;
	std::shared_ptr<GamePlayStaticObject> Interact_TableObject_;

	std::shared_ptr<GamePlayMoveable> CurrentHoldingObject_;

	void Collision_AroundObject();



	std::shared_ptr<GameEngineFBXStaticRenderer> PlayerRenderer_;
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

