#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Enums.h"
#include "OverCookedUIRenderer.h"

class RespawnUI : public GameEngineActor
{
public:
	RespawnUI();
	~RespawnUI();

	RespawnUI(const RespawnUI& _Other) = delete;
	RespawnUI(const RespawnUI&& _Other) noexcept = delete;
	RespawnUI& operator=(const RespawnUI& _Ohter) = delete;
	RespawnUI& operator=(const RespawnUI&& _Other) noexcept = delete;

	void Init(const float4& _Pos, float* _Time);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::weak_ptr<OverCookedUIRenderer> Background_;

	std::weak_ptr<GameEngineFontRenderer> Font_;

	float4 Pos_ = { 0,0,0 };

	float* Time_Iter_ = nullptr;
	bool IsInit_ = false;
};
