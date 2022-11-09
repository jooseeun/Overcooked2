#include "PreCompile.h"
#include "GamePlayStuff.h"

GamePlayStuff::GamePlayStuff()
	: Enum_ObjectStuffType_(ObjectStuffType::None)
	, Enum_ToolInfo_(ToolInfo::None)

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


void GamePlayStuff::SetParentObject(GamePlayObject* _Object)
{
	SetParent(_Object);
}