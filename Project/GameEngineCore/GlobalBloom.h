#pragma once
#include "GameEngineRenderTarget.h"

// Ό³Έν :
class GlobalBloom : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	GlobalBloom();
	~GlobalBloom();

	// delete Function
	GlobalBloom(const GlobalBloom& _Other) = delete;
	GlobalBloom(GlobalBloom&& _Other) noexcept = delete;
	GlobalBloom& operator=(const GlobalBloom& _Other) = delete;
	GlobalBloom& operator=(GlobalBloom&& _Other) noexcept = delete;

	void EffectInit() override;
	void Effect(std::shared_ptr<GameEngineRenderTarget> _Target) override;

protected:
	std::shared_ptr<GameEngineRenderTarget> CopyTarget;
	GameEngineRenderUnit EffectSet;

private:

};

