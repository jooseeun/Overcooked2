#include "PreCompile.h"
#include "GameSoundPlayer.h"

std::shared_ptr<GameSoundPlayer> GameSoundPlayer::BgmPlayer_ = std::make_shared<GameSoundPlayer>();
std::shared_ptr<GameSoundPlayer> GameSoundPlayer::EffectPlayer_ = std::make_shared<GameSoundPlayer>();


GameSoundPlayer::GameSoundPlayer() 
	: Volume_(1.f)

{
}

GameSoundPlayer::~GameSoundPlayer() 
{
}

void GameSoundPlayer::ChangeBgm(std::string _BgmName, unsigned int _LoopCount)
{
	if (Volume_ == 1.f)
	{
		Volume_ = 1.f;
	}

	BgmName_ = _BgmName;
	SoundPlayer_Bgm_.Stop();
	SoundPlayer_Bgm_ = GameEngineSound::SoundPlayControl(_BgmName, _LoopCount);
	SetBgmVolume(Volume_);
}

void GameSoundPlayer::ChangeEffect(std::string _BgmName, unsigned int _LoopCount)
{
	if (Volume_ == 1.f)
	{
		Volume_ = 1.f;
	}

	BgmName_ = _BgmName;
	SoundPlayer_Effect_.Stop();
	SoundPlayer_Effect_ = GameEngineSound::SoundPlayControl(_BgmName, _LoopCount);
	SetEffectVolume(Volume_);
}
