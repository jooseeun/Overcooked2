#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// ���� :
class SoundControlGUI : public GameEngineGUI
{
public:
	// constrcuter destructer
	SoundControlGUI();
	~SoundControlGUI();

	// delete Function
	SoundControlGUI(const SoundControlGUI& _Other) = delete;
	SoundControlGUI(SoundControlGUI&& _Other) noexcept = delete;
	SoundControlGUI& operator=(const SoundControlGUI& _Other) = delete;
	SoundControlGUI& operator=(SoundControlGUI&& _Other) noexcept = delete;

protected:


};

