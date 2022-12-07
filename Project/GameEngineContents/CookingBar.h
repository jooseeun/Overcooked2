#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Enums.h"
#include "OverCookedUIRenderer.h"
class CookingBar : public GameEngineActor
{
public:
	CookingBar();
	~CookingBar();

	CookingBar(const CookingBar& _Other) = delete;
	CookingBar(const CookingBar&& _Other) noexcept = delete;
	CookingBar& operator=(const CookingBar& _Ohter) = delete;
	CookingBar& operator=(const CookingBar&& _Other) noexcept = delete;

	void LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset, float* _LinkValue);

	inline void SetOffset(const float4& _Offset)
	{
		Offset_ = _Offset;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void ChaseTarget();
	void End() override;

private:
	std::weak_ptr<OverCookedUIRenderer> Background_;
	std::weak_ptr<OverCookedUIRenderer> Foreground_;

	std::weak_ptr<GameEngineActor> ChaseActor_;

	float4 Offset_ = { 0,0,0 };

	float* UpdateValue_ = nullptr;
};