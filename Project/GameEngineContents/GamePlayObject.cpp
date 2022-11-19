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
	Collision_Object_->SetDebugSetting(CollisionType::CT_AABB, {0, 0.8f, 0, 0.5f});
	Collision_Object_->ChangeOrder(CollisionOrder::Object_None);

	AnimationMesh_Obejct_ = CreateComponent<GameEngineFBXAnimationRenderer>("AnimationMesh_Obejct");
}



CollisionReturn GamePlayObject::CheckCollisionObjectByPhysics(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	CalculatorPhysic(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()), _Other->GetActor<GamePlayObject>());

	return CollisionReturn::ContinueCheck;
}

// Static
void GamePlayObject::CalculatorPhysic(std::weak_ptr<GamePlayObject> _ObjectA, std::weak_ptr<GamePlayObject> _ObjectB)
{
	_ObjectA.lock()->External_Vector_ += (_ObjectA.lock()->Vector_ - _ObjectB.lock()->Vector_);
	_ObjectB.lock()->External_Vector_ += (_ObjectB.lock()->Vector_ - _ObjectA.lock()->Vector_);

}