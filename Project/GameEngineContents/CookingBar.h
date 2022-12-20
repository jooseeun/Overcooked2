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

	void LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset, float* _LinkValue, bool _IsOver = false); //IsOver : 100이 넘어갈 수 있는 오브젝트

	inline void SetOver(bool _IsOver)
	{
		IsOver_ = _IsOver;
	}

	inline void SetOffset(const float4& _Offset)
	{
		Offset_ = _Offset;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void UpdateBar(float _DeltaTime);
	void ChaseTarget();
	void End() override;

private:
	std::weak_ptr<OverCookedUIRenderer> Background_;
	std::weak_ptr<OverCookedUIRenderer> Foreground_;

	std::weak_ptr<OverCookedUIRenderer> Icon_;

	std::weak_ptr<GameEngineActor> ChaseActor_;

	float4 Offset_ = { 0,0,0 };

	float IterTime_ = 0.f;

	float* UpdateValue_ = nullptr;

	bool IsOver_ = false;

	float PrevValue_ = 0.f;
	bool IsUpdating_ = true;
};
