#pragma once
#include "GamePlayStaticObject.h"
// Ό³Έν :
class Oven : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Oven();
	~Oven();

	// delete Function
	Oven(const Oven& _Other) = delete;
	Oven(Oven&& _Other) noexcept = delete;
	Oven& operator=(const Oven& _Other) = delete;
	Oven& operator=(Oven&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineActor> Door_;
};

