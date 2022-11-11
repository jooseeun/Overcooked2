#pragma once
#include "GameEngineRenderTarget.h"

// Ό³Έν :
class GlobalVignette : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	GlobalVignette();
	~GlobalVignette();

	// delete Function
	GlobalVignette(const GlobalVignette& _Other) = delete;
	GlobalVignette(GlobalVignette&& _Other) noexcept = delete;
	GlobalVignette& operator=(const GlobalVignette& _Other) = delete;
	GlobalVignette& operator=(GlobalVignette&& _Other) noexcept = delete;

	void EffectInit() override;
	void Effect(GameEngineRenderTarget* _Target) override;

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderUnit EffectSet;

private:

};

