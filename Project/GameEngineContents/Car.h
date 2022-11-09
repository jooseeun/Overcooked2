#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
class Car : public GamePlayMapObject
{
public:
	// constrcuter destructer
	Car();
	~Car();

	// delete Function
	Car(const Car& _Other) = delete;
	Car(Car&& _Other) noexcept = delete;
	Car& operator=(const Car& _Other) = delete;
	Car& operator=(Car&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

