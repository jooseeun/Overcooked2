#include "PreCompile.h"
#include "GamePlayCharacter.h"

GamePlayCharacter::GamePlayCharacter() 
{
}

GamePlayCharacter::~GamePlayCharacter() 
{
}

void GamePlayCharacter::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::Character);

}