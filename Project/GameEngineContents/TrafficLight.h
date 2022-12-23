#pragma once
#include "GamePlayMapObject.h"

enum class LIGHTCOLOR
{
	GREEN,
	YELLOW,
	RED
};

// Ό³Έν :
class TrafficLight : public GamePlayMapObject
{
public:
	// constrcuter destructer
	TrafficLight();
	~TrafficLight();

	// delete Function
	TrafficLight(const TrafficLight& _Other) = delete;
	TrafficLight(TrafficLight&& _Other) noexcept = delete;
	TrafficLight& operator=(const TrafficLight& _Other) = delete;
	TrafficLight& operator=(TrafficLight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	LIGHTCOLOR Color_;
	float ChangeTime_;
};

