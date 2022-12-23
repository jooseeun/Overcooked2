#pragma once
#include "GameEngineCore//GameEngineActor.h"
enum class CannonState
{
	Idle,
	Ready,
	Shoot,
	Down,
	Max,
};

// 설명 :
class Button;
class Cannon : public GameEngineActor
{

public:
	// constrcuter destructer
	Cannon();
	~Cannon();

	// delete Function
	Cannon(const Cannon& _Other) = delete;
	Cannon(Cannon&& _Other) noexcept = delete;
	Cannon& operator=(const Cannon& _Other) = delete;
	Cannon& operator=(Cannon&& _Other) noexcept = delete;

public:
	inline CannonState GetCannonState()
	{
		return CurState_;
	}

	inline void SetPlayer(std::shared_ptr<Player> _Player)
	{
		Player_ = _Player;
	}

	inline void ResetPlayer()
	{
		if (Player_ == nullptr)
		{
			return;
		}

		Player_.reset();
		Player_ = nullptr;
	}

	inline std::shared_ptr<Button> GetButton()
	{
		return Button_;
	}

	// 캐논의 상태를 Idle => Ready 로 바꾸는 함수
	//inline void SwitchInteraction_()
	//{
	//	Interaction_ = !Interaction_;
	//} 

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void ReadyStart(const StateInfo& _Info);
	void ReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	void ShootStart(const StateInfo& _Info);
	void ShootUpdate(float _DeltaTime, const StateInfo& _Info);

	void DownStart(const StateInfo& _Info);
	void DownUpdate(float _DeltaTime, const StateInfo& _Info);

	std::shared_ptr<GameEngineFBXStaticRenderer> Mesh_Object_;
	std::shared_ptr<GameEngineCollision> Collision_Object_;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> BaseRenderer;

	std::shared_ptr<Player> Player_;
	std::shared_ptr<Button> Button_;

	CannonState CurState_;
	GameEngineStateManager StateManager;

	bool IsCounterReaction_;
	bool IsCounterReactionPos_;
	bool IsMoveDone_;
	bool IsDownMove_;
	float CurAngle_;
	float ReadyAngle_;
	float MaxAngle_;
	float CurPos_;

	int ReactCount_;
};

