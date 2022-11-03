#include "PreCompile.h"
#include "GamePlayStuff.h"

GamePlayStuff::GamePlayStuff() 
	: Enum_ObjectStuffType_(ObjectStuffType::None)
{
}

GamePlayStuff::~GamePlayStuff() 
{
}

void GamePlayStuff::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::Stuff);


}