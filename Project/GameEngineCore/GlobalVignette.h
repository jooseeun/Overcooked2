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
	void Effect(std::shared_ptr<GameEngineRenderTarget> _Target) override;

protected:
	std::shared_ptr<GameEngineRenderTarget> CopyTarget;
	std::shared_ptr<GameEngineRenderUnit> EffectSet;

private:

};

