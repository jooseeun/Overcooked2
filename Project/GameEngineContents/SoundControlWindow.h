#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class SoundControlWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	SoundControlWindow();
	~SoundControlWindow();

	// delete Function
	SoundControlWindow(const SoundControlWindow& _Other) = delete;
	SoundControlWindow(SoundControlWindow&& _Other) noexcept = delete;
	SoundControlWindow& operator=(const SoundControlWindow& _Other) = delete;
	SoundControlWindow& operator=(SoundControlWindow&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	static std::shared_ptr<SoundControlWindow> Main_;

private:
	float Volume_;
	float BgmVolume_;
	float EffectVolume_;
	float ObjVolume_;
};

