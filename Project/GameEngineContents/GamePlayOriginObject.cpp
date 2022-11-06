#include "PreCompile.h"
#include "GamePlayOriginObject.h"

GamePlayOriginObject::GamePlayOriginObject() 
{
}

GamePlayOriginObject::~GamePlayOriginObject() 
{
}

void GamePlayOriginObject::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
}



