#include "PreCompile.h"
#include "Npc.h"

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
}

void Npc::Update(float _DeltaTime)
{
}

