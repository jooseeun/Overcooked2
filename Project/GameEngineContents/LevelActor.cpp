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
	Renderer_ = CreateComponent<GameEngineFBXRenderer>();
}

void LevelActor::Update(float _Update)
{
}

void LevelActor::End()
{	
}
