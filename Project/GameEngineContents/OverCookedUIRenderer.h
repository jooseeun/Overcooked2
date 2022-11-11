#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct UIData
{
	int UIMode; // 0: �⺻ 1: ����ũ 2: Transition
	float4 DownDelta;//{0 : ����������� 1.f : �����,���� DeltaTime,,,}

	UIData()
		: UIMode(0)
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

	void StartDown(float _Speed);

	void SetSamplerWrap();

	void SetSamplerPointClamp();

	void StartFadeOut(float _StartRatio); //����! CameraOrder : AboveUICAMERA�� �ؾ���

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

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

	//Pump����
	float4 PrevScale_ = {};
	float Pump_IterTime_ = 0.f;
	float PumpingSpeed_ = 1.f;
	float PumpRatio_ = 0.f;
	bool IsPumping_ = false;
	bool IsPumping();

	//Down����
	bool IsDown_ = false;
	float DownIter_ = 0.f;
	float DownSpeed_ = 0.f;

	//Transition ����
	float TransitionRatio_;
	float AccTime_;
};
