#include "PreCompile.h"
#include "GameBgmPlayer.h"

std::shared_ptr<GameBgmPlayer> GameBgmPlayer::BgmPlayer_ = std::make_shared<GameBgmPlayer>();
std::shared_ptr<GameBgmPlayer> GameBgmPlayer::EffectBgmPlayer_ = std::make_shared<GameBgmPlayer>();


GameBgmPlayer::GameBgmPlayer() 
{
}

GameBgmPlayer::~GameBgmPlayer() 
{
}

