#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
class Lift : public GamePlayFloor
{
public:
	// constrcuter destructer
	Lift();
	~Lift();

	// delete Function
	Lift(const Lift& _Other) = delete;
	Lift(Lift&& _Other) noexcept = delete;
	Lift& operator=(const Lift& _Other) = delete;
	Lift& operator=(Lift&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

