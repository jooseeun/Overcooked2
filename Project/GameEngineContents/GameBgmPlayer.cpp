#include "PreCompile.h"
#include "GameBgmPlayer.h"

std::shared_ptr<GameBgmPlayer> GameBgmPlayer::BgmPlayer_ = std::make_shared<GameBgmPlayer>();

GameBgmPlayer::GameBgmPlayer() 
{
}

GameBgmPlayer::~GameBgmPlayer() 
{
}

