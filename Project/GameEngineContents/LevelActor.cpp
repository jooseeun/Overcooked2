#include "PreCompile.h"
#include "LevelActor.h"

LevelActor::LevelActor() 
{
}

LevelActor::~LevelActor() 
{
}

void LevelActor::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
}

void LevelActor::Update(float _Update)
{
}

void LevelActor::End()
{	
}
