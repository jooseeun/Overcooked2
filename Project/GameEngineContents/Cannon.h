#pragma once
#include "GamePlayStaticObject.h"

enum class CannonState
{
	Idle,
	Ready,
	Shoot,
	Max,
};

// Ό³Έν :
class Cannon : public GamePlayStaticObject
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

	inline void SetCannonState(CannonState _CurState)
	{
		CurState_ = _CurState;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineActor> CannonBase_;

	CannonState CurState_;
};

