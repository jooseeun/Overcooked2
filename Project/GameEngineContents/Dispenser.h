#pragma once
#include "GamePlayStaticObject.h"

// Ό³Έν :
class Dispenser : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Dispenser();
	~Dispenser();

	// delete Function
	Dispenser(const Dispenser& _Other) = delete;
	Dispenser(Dispenser&& _Other) noexcept = delete;
	Dispenser& operator=(const Dispenser& _Other) = delete;
	Dispenser& operator=(Dispenser&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

