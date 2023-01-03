#pragma once
#include "GamePlayMapObject.h"

enum class LIGHTCOLOR
{
	GREEN,
	YELLOW,
	RED
};

class TrafficLightBloom : public GamePlayMapObject
{
public:
	TrafficLightBloom();
	~TrafficLightBloom();

	TrafficLightBloom(const TrafficLightBloom& _Other) = delete;
	TrafficLightBloom(TrafficLightBloom&& _Other) noexcept = delete;
	TrafficLightBloom& operator=(const TrafficLightBloom& _Other) = delete;
	TrafficLightBloom& operator=(TrafficLightBloom&& _Other) noexcept = delete;

	void SetBloomActor();

	static LIGHTCOLOR GetColor()
	{
		return Color_;
	}

	static void SetColor(LIGHTCOLOR _Color)
	{
		Color_ = _Color;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

	bool IsFirst_;

	std::shared_ptr<GlobalBloomActor> Green_;
	std::shared_ptr<GlobalBloomActor> Yellow_;
	std::shared_ptr<GlobalBloomActor> Red_;

	std::shared_ptr<GlobalBloomActor> Green_Ground;
	std::shared_ptr<GlobalBloomActor> Yellow_Ground;
	std::shared_ptr<GlobalBloomActor> Red_Ground;

	static float ChangeTime_;
	static float WattingTime_;
	static LIGHTCOLOR Color_;
	static LIGHTCOLOR BeforeColor_;
	static TrafficLightBloom* Inst_;

	static void TrafficLightUpdate(float _Delta);

};

