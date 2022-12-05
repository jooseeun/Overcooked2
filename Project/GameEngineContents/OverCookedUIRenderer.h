#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct UIData
{
	int UIMode; // 0: 기본 1: 마스크 2: Transition
	float4 DownDelta;//{0 : 사용하지않음 1.f : 사용함,누적 DeltaTime,,,}

	UIData()
		: UIMode(0)
		, DownDelta(float4::ZERO)
	{
	}
};

enum TransitionType
{
	Clover,
	Chicken,
	Onion
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
	PixelData& GetPixelData()
	{
		return PixelDataInst;
	}

	void ResistDebug();

	void ResistDebug(std::string_view _Name);

	void SetTexture(std::shared_ptr<GameEngineTexture> _Texture);

	void SetTexture(const std::string& _Name);

	void SetMaskTexture(const std::string_view _Name);

	void SetFrame(UINT _Index);

	std::shared_ptr<GameEngineTexture> GetCurTexture();

	void SetTexture(const std::string& _Name, UINT _Index);

	void SetPivot();

	void SetPivot(PIVOTMODE _Mode);

	void SetPivotToVector(const float4& _Value);

	void SetTexture(std::shared_ptr<GameEngineTexture> _Texture, UINT _Index);

	void SetFolderTextureToIndex(const std::string& _Text, UINT _Index);

	void ScaleToTexture();

	void ScaleToCutTexture(int _Index);

	void StartPump(float _Ratio, float _Speed = 1.f);

	void StartPumpHori(float _Ratio, float _Speed = 1.f);

	void StartPumpVerti(float _Ratio, float _Speed = 1.f);

	void StartVibrationHori(float _Scale, float _Speed);

	void StartDown(float _Speed);

	void SetSamplerWrap();

	void SetSamplerPointClamp();

	void StartFadeOut(float _StartRatio); //주의! CameraOrder : AboveUICAMERA로 해야함

	void StartFadeIn();

	void SetUIMode(int _Mode) // 3: LeftToRight Gauge
	{
		UIDataInst.UIMode = _Mode;
	}

	void UpdateLeftToRight(float _Percentage); // 0.0 : min , 1.0

	void UpdateLeftTime(float _Percentage);

	void UpdateColor(const float4& _PlusColor = { 0,0,0,0 }, const float4& _MulColor = { 1.f,1.f,1.f,1.f });

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

	void UpdateTransition(float _Delta);

	void StopPump();

private:
	PIVOTMODE PivotMode;
	SCALEMODE ScaleMode;
	float ScaleRatio;

	std::shared_ptr<GameEngineTexture> CurTex;

	PixelData PixelDataInst;
	AtlasData AtlasDataInst;
	UIData UIDataInst;

	std::map<std::string, FrameAnimation> FrameAni;
	std::shared_ptr<FrameAnimation> CurAni;

	//Vibration관련
	float4 PrevPos_ = {};
	float4 VibrationPos_ = {};
	float VibrationSpeed_ = 1.f;
	float Vibration_IterTime_ = 0.f;
	bool IsVibration_ = false;

	//Pump관련
	float4 PrevScale_ = {};
	float4 PumpScale_;
	float Pump_IterTime_ = 0.f;
	float PumpingSpeed_ = 1.f;
	float PumpRatio_ = 0.f;
	bool IsPumping_ = false;
	bool IsPumping();

	//Down관련
	bool IsDown_ = false;
	float DownIter_ = 0.f;
	float DownSpeed_ = 0.f;

	//Transition 관련
	bool IsFadeOut_; //true : FadeOut, false : FadeIn
public:
	bool IsFinishFadeIn_ = false;
	bool IsFinishFadeOut_ = false;

private:

	float TransitionRatio_;
	float AccTime_;
};
