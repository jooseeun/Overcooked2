#include "PreCompile.h"
#include "SoundControlWindow.h"

std::shared_ptr<SoundControlWindow> SoundControlWindow::Main_ = nullptr;

SoundControlWindow::SoundControlWindow() 
{
}

SoundControlWindow::~SoundControlWindow() 
{
}

void SoundControlWindow::Initialize(GameEngineLevel* _Level)
{
}

void SoundControlWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string Name = "Current Bgm : " + GameSoundPlayer::BgmPlayer_->GetBgmName();
	BgmVolume_ = GameSoundPlayer::BgmPlayer_->GetVolume();
	EffectVolume_ = GameSoundPlayer::EffectPlayer_->GetVolume();

	ImGui::Text(Name.c_str());

	ImGui::DragFloat("Volume : Bgm", &BgmVolume_, 0.5f, 0.f, 10.f);
	ImGui::DragFloat("Volume : Effect", &EffectVolume_, 0.5f, 0.f, 10.f);

	GameSoundPlayer::BgmPlayer_->SetBgmVolume(BgmVolume_);
	GameSoundPlayer::EffectPlayer_->SetEffectVolume(EffectVolume_);
}

