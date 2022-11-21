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

void GamePlayObject::Update(float _DeltaTime)
{
	if (GetParent() == nullptr)
	{
		switch (Enum_ObjectType_)
		{
		case ObjectType::StaticObject:
			return;
			break;
		case ObjectType::Stuff:
		case ObjectType::Character:
		{
			const float4& Pos = GetTransform().GetWorldPosition();
			if (GetCollisionObject()->IsCollision(CollisionType::CT_AABB, CollisionOrder::Floor, CollisionType::CT_AABB) == false)
			{
				GetTransform().SetWorldDownMove(100.0f, GameEngineTime::GetDeltaTime());
				if (Vector_.CompareInt3D(float4::ZERO) == false) 
				{ 
					Vector_ *= 0.95f;
				}

				GetTransform().SetWorldMove(Vector_ * _DeltaTime);

				Pos;
				int a = 0;
				a + 1;
			}



		

			//GetCollisionObject()->SetCollisionMode(CollisionMode::Ex);
			//if (GetCollisionObject()->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(CollisionOrder::Map_Object), CollisionType::CT_OBB,
			//	std::bind(&GamePlayObject::CheckCollisionObjectByPhysics_Enter, this, std::placeholders::_1, std::placeholders::_2)) == false)
			//{

			//}

			//GetCollisionObject()->SetCollisionMode(CollisionMode::Normal);
		}
			break;
		default:
			break;
		}



	}

	if (true)
	{

	}
	
}


CollisionReturn GamePlayObject::CheckCollisionObjectByPhysics_Enter(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//CalculatorPhysic(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()), _Other->GetActor<GamePlayObject>());

	return CollisionReturn::ContinueCheck;
}

CollisionReturn GamePlayObject::CheckCollisionMapObjectByPhysics_Enter(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//CalculatorPhysicByMapobject(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()), _Other->GetActor<GamePlayObject>());

	return CollisionReturn::ContinueCheck;
}

// Static
//void GamePlayObject::CalculatorPhysic(std::weak_ptr<GamePlayObject> _ObjectA, std::weak_ptr<GamePlayObject> _ObjectB)
//{   
//	_ObjectA.lock()->External_Vector_ += (_ObjectA.lock()->Vector_ - _ObjectB.lock()->Vector_);
//	_ObjectB.lock()->External_Vector_ += (_ObjectB.lock()->Vector_ - _ObjectA.lock()->Vector_);
//}
//
//void GamePlayObject::CalculatorPhysicByMapobject(std::weak_ptr<GamePlayObject> _Object, std::weak_ptr<GamePlayObject> _MapObject)
//{
//	_Object.lock()->GetCollisionObject();
//
//
//	_Object.lock()->External_Vector_ += (_MapObject.lock()->Vector_ - _Object.lock()->Vector_);
//}