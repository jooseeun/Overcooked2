#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

// 설명 :

struct UIData
{
	int UsingMask;
	float4 DownDelta;//{0 : 사용하지않음 1.f : 사용함,누적 DeltaTime,,,}

	UIData()
		: UsingMask(0)
		, DownDelta(float4::ZERO)
	{
	}
};

class OverCookedUIRenderer : public GameEngineDefaultRenderer
{
	friend FrameAnimation;

public:
	// constrcuter destructer
	OverCookedUIRenderer();
	~OverCookedUIRenderer();

	// delete Function
	OverCookedUIRenderer(const OverCookedUIRenderer& _Other) = delete;
	OverCookedUIRenderer(OverCookedUIRenderer&& _Other) noexcept = delete;
	OverCookedUIRenderer& operator=(const OverCookedUIRenderer& _Other) = delete;
	OverCookedUIRenderer& operator=(OverCookedUIRenderer&& _Other) noexcept = delete;

	void SetSamplingModePoint();
	void SetSamplingModeLiner();

	void SetScaleModeImage()
	{
		ScaleMode = SCALEMODE::IMAGE;
	}

	void SetScaleRatio(float _Scale)
	{
		ScaleRatio = _Scale;
	}

	float GetScaleRatio()
	{
		return ScaleRatio;
	}

	void ResistDebug();

	void SetTexture(GameEngineTexture* _Texture);

	void SetTexture(const std::string& _Name);

	void SetMaskTexture(const std::string_view _Name);

	void SetFrame(UINT _Index);

	GameEngineTexture* GetCurTexture();

	void SetTexture(const std::string& _Name, UINT _Index);

	void SetPivot();

	void SetPivot(PIVOTMODE _Mode);

	void SetPivotToVector(const float4& _Value);

	void SetTexture(GameEngineTexture* _Texture, UINT _Index);

	void SetFolderTextureToIndex(const std::string& _Text, UINT _Index);

	void ScaleToTexture();

	void ScaleToCutTexture(int _Index);

	void StartPump(float _Ratio, float _Speed = 1.f);

	void StartDown(float _Speed);

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

	void StopPump();

private:
	PIVOTMODE PivotMode;
	SCALEMODE ScaleMode;
	float ScaleRatio;

	GameEngineTexture* CurTex;

	PixelData PixelDataInst;
	AtlasData AtlasDataInst;
	UIData UIDataInst;

	std::map<std::string, FrameAnimation> FrameAni;
	FrameAnimation* CurAni;

	//Pump관련
	float4 PrevScale_ = {};
	float Pump_IterTime_ = 0.f;
	float PumpingSpeed_ = 1.f;
	float PumpRatio_ = 0.f;
	bool IsPumping_ = false;
	bool IsPumping();

	//Down관련
	bool IsDown_ = false;
	float DownIter_ = 0.f;
	float DownSpeed_ = 0.f;
};
