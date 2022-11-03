#include "PreCompile.h"
#include "GamePlayObject.h"

GamePlayObject::GamePlayObject() 
	: Mesh_Object_(nullptr)
	, Collision_Object_(nullptr)
	, Enum_ObjectType_(ObjectType::None)
{
}

GamePlayObject::~GamePlayObject() 
{
}



void GamePlayObject::Start()
{
	Mesh_Object_ = CreateComponent<GameEngineFBXRenderer>("Mesh_Object");
	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->SetDebugSetting(CollisionType::CT_SPHERE, {0, 0.8f, 0, 0.5f});

}