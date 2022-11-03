#include "PreCompile.h"
#include "GamePlayMoveable.h"

GamePlayMoveable::GamePlayMoveable() 
{
}

GamePlayMoveable::~GamePlayMoveable() 
{
}

void GamePlayMoveable::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Moveable);

}