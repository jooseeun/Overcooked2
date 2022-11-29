#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class GameEngineGUIWindow;
class GamePlayLevel;
class GlobalOverlay;
class GlobalVignette;
class GlobalBloom;

// Ό³Έν :
class GraphicWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	GraphicWindow();
	~GraphicWindow();

	// delete Function
	GraphicWindow(const GraphicWindow& _Other) = delete;
	GraphicWindow(GraphicWindow&& _Other) noexcept = delete;
	GraphicWindow& operator=(const GraphicWindow& _Other) = delete;
	GraphicWindow& operator=(GraphicWindow&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
	static std::shared_ptr<GlobalOverlay> GlobalOverlay_;
	static std::shared_ptr<GlobalVignette> GlobalVignette_;
	static std::shared_ptr<GlobalBloom> GlobalBloom_;


	static ImVec4 OverlayColor_;
	static bool OverlayOnOff_;
	static bool VignetteOnOff_;
	static bool BloomOnOff_;


public:
	static void SetOverlay(std::shared_ptr<GlobalOverlay> _PostEffect)
	{
		GlobalOverlay_ = _PostEffect;
	}

	static void SetVignette(std::shared_ptr<GlobalVignette> _PostEffect)
	{
		GlobalVignette_ = _PostEffect;
	}

	static void SetBloom(std::shared_ptr<GlobalBloom> _PostEffect)
	{
		GlobalBloom_ = _PostEffect;
	}

private:

	static void ConvertToImvec(float4 _float4Value, ImVec4& _ImVec4Value)
	{
		_ImVec4Value.x = _float4Value.x;
		_ImVec4Value.y = _float4Value.y;
		_ImVec4Value.z = _float4Value.z;
		_ImVec4Value.w = _float4Value.w;
	}


	static void ConvertToFloat4(float4& _float4Value, ImVec4 _ImVec4Value)
	{
		_float4Value.x = _ImVec4Value.x;
		_float4Value.y = _ImVec4Value.y;
		_float4Value.z = _ImVec4Value.z;
		_float4Value.w = _ImVec4Value.w;
	}

	static float BloomFilter1_[3];
	static float BloomFilter2_[3];
	static float BloomFilter3_[3];
	static float BloomFilter4_[3];
	static float BloomFilter5_[3];
	static float BloomValue_;
	static float BrightMin_;
	static float BrightMax_;
	static void BloomSetting();

public:
	static std::shared_ptr<GraphicWindow> Main_;

};
