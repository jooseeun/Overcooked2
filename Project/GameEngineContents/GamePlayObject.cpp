#include "PreCompile.h"
#include "GamePlayObject.h"

GamePlayObject::GamePlayObject()
	: Mesh_Object_(nullptr)
	, Collision_Object_(nullptr)
	, Enum_ObjectType_(ObjectType::None)
	, BloomEffect_(false)
{
}

GamePlayObject::~GamePlayObject()
{
}

void GamePlayObject::Start()
{
	Mesh_Object_ = CreateComponent<GameEngineFBXStaticRenderer>("Mesh_Object");
	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0, 0.5f });
	Collision_Object_->ChangeOrder(CollisionOrder::Object_None);

	AnimationMesh_Obejct_ = CreateComponent<GameEngineFBXAnimationRenderer>("AnimationMesh_Obejct");
	SetGravityCollision(Collision_Object_);
}

void GamePlayObject::Update(float _DeltaTime)
{
	if (GetParent() == nullptr)
	{
		Gravity();
	}
}
