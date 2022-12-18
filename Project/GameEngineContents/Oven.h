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

	inline void SwitchIsInteraction()
	{
		IsInteraction_ = !IsInteraction_;
	}

	inline void SwitchIsPut()
	{
		IsPut_ = !IsPut_;
	}

	inline void SwitchIsTakeOut_()
	{
		IsTakeOut_ = !IsTakeOut_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineActor> Door_;
	std::shared_ptr<GameEngineFBXStaticRenderer> DoorRenderer_;

	bool IsInteraction_;
	bool IsCooking_;
	float Angle_;

	bool IsPut_;
	bool IsTakeOut_;
};

