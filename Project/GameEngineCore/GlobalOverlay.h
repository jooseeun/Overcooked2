#pragma once
#include "GameEngineRenderTarget.h"


struct OverlayColorData
{
	float4 OverlayColor = { 0.499f, 0.592f, 0.726f, 1.0f };

};

class GlobalOverlay : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	GlobalOverlay();
	~GlobalOverlay();

	// delete Function
	GlobalOverlay(const GlobalOverlay& _Other) = delete;
	GlobalOverlay(GlobalOverlay&& _Other) noexcept = delete;
	GlobalOverlay& operator=(const GlobalOverlay& _Other) = delete;
	GlobalOverlay& operator=(GlobalOverlay&& _Other) noexcept = delete;

	void EffectInit() override;
	void Effect(std::shared_ptr<GameEngineRenderTarget> _Target) override;


protected:
	std::shared_ptr<GameEngineRenderTarget> CopyTarget;
	std::shared_ptr<GameEngineRenderUnit> EffectSet;

	OverlayColorData OverlayColorData_;

private:

public:

	OverlayColorData& GetOverlayColorData()
	{
		return OverlayColorData_;
	}
};

