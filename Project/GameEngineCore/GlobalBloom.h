#pragma once
#include "GameEngineRenderTarget.h"

class BloomOption
{
public:
	float4 BloomFilter[5] = { float4(0.2126f, 0.7152f, 0.0722f), float4::ZERO, float4::ZERO, float4::ZERO, float4::ZERO };
	float BloomValue = 10;
	float BrightMin = 0.8f;
	float BrightMax = 1.0f;
};

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
	BloomOption& GetOption()
	{
		return Option_;
	}

protected:
	std::shared_ptr<GameEngineRenderTarget> CopyTarget;
	GameEngineRenderUnit EffectSet;

private:
	BloomOption Option_;
};

