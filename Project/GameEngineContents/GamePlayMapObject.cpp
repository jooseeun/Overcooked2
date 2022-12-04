#include "PreCompile.h"
#include "GamePlayMapObject.h"

GamePlayMapObject::GamePlayMapObject()
	: ObjType_(MapObjType::Max)
{
}

GamePlayMapObject::~GamePlayMapObject() 
{
}

void GamePlayMapObject::Start()
{
	GamePlayObject::Start();

	GetTransform().SetLocalScale({ 1.f, 1.f, 1.f });
	GetCollisionObject()->ChangeOrder(CollisionOrder::Map_Object);
	GetCollisionObject()->SetDebugSetting(CollisionType::CT_AABB, { 0, 0, 0.8f, 0.5f });	// 일반 벽, 갈 수 없는 지역, NPC => 파랑
	GetCollisionObject()->GetTransform().SetWorldScale({ 50.f, 50.f, 50.f });				// 원래 크기는 0.01
}

void GamePlayMapObject::Update(float _DeltaTime)
{

}

void GamePlayMapObject::SetMapObjectMesh(const std::string& _Name, MapObjType _ObjType)
{
	ObjType_ = _ObjType;
	switch (ObjType_)
	{
	case MapObjType::StaticNoCollision:
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
		GetCollisionObject()->Off();
	}
		break;
	case MapObjType::Pigeon_Grounded:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 150.f, 150.f, 150.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation", 1);	// Grounded
		GetAnimationFBXMesh()->CreateFBXAnimation("Idle", GameEngineRenderingEvent(_Name + ".fbx", 0.04f, true));
		GetAnimationFBXMesh()->ChangeAnimation("Idle");
		GetCollisionObject()->Off();
	}
		break;
	case MapObjType::Animation:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation", 0, 0);
		GetAnimationFBXMesh()->CreateFBXAnimation("Idle", GameEngineRenderingEvent(_Name + ".fbx", 0.04f, true));
		GetAnimationFBXMesh()->ChangeAnimation("Idle");
	}
		break;
	case MapObjType::Npc:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation");
		GetAnimationFBXMesh()->CreateFBXAnimation("Idle", GameEngineRenderingEvent(_Name + ".fbx", 0.04f, true));

		GetAnimationFBXMesh()->ChangeAnimation("Idle");
		GetAnimationFBXMesh()->ChangeAnimationFrame(GameEngineRandom::MainRandom.RandomInt(0, (int)GetAnimationFBXMesh()->GetAnimationFrameCount()));
	}
		break;
	case MapObjType::Car:
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
	}
		break;
	case MapObjType::TrafficLight:
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
	}
	case MapObjType::Candle:
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
		GetCollisionObject()->Off();
	}
		break;
	case MapObjType::Lift:
	{
		GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
	}
	break;
	default:
		break;
	}
}

