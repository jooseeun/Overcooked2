#pragma once
#include "GamePlayStaticObject.h"

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineActor> CannonBase_;
};

