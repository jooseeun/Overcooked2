#include "PreCompile.h"
#include "GamePlayStaticObject.h"

GamePlayStaticObject::GamePlayStaticObject() 
	: ToolPos_(float4::ZERO)
{
}

GamePlayStaticObject::~GamePlayStaticObject() 
{
}

void GamePlayStaticObject::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::StaticObject);
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_StaticObject);
} 
