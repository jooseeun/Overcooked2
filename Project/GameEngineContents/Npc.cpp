#include "PreCompile.h"
#include "Npc.h"
#include <GameEngineBase/GameEngineRandom.h>

Npc::Npc() 
	: RandomTime_(0)
{
}

Npc::~Npc() 
{
}

void Npc::Start()
{
	GamePlayMapObject::Start();

	RandomTime_ = GameEngineRandom::MainRandom.RandomInt(0, 25);
}

void Npc::Update(float _DeltaTime)
{
}

