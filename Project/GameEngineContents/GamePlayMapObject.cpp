#include "PreCompile.h"
#include "GamePlayMapObject.h"

GamePlayMapObject::GamePlayMapObject()
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
	GetCollisionObject()->SetDebugSetting(CollisionType::CT_AABB, { 0, 0, 0.8f, 0.5f });	// �Ϲ� ��, �� �� ���� ����, NPC => �Ķ�
	GetCollisionObject()->GetTransform().SetWorldScale({ 50.f, 50.f, 50.f });				// ���� ũ��� 0.01
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
	case MapObjType::AnimationNoCollision:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation");
		GetAnimationFBXMesh()->CreateFBXAnimation("Test", _Name + ".fbx");
		GetAnimationFBXMesh()->ChangeAnimation("Test");
		GetCollisionObject()->Off();
	}
		break;
	case MapObjType::Animation:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation");
		GetAnimationFBXMesh()->CreateFBXAnimation("Test", _Name + ".fbx");
		GetAnimationFBXMesh()->ChangeAnimation("Test");
	}
		break;
	case MapObjType::Npc:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation");
		GetAnimationFBXMesh()->CreateFBXAnimation("Test", _Name + ".fbx");
		GetAnimationFBXMesh()->ChangeAnimation("Test");
	}
		break;
	case MapObjType::Car:
	{
		GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation");
		GetAnimationFBXMesh()->CreateFBXAnimation("Test", _Name + ".fbx");
		GetAnimationFBXMesh()->ChangeAnimation("Test");
	}
		break;
	case MapObjType::TrafficLight:
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
	}
		break;
	default:
		break;
	}


	//GetAnimationFBXMesh()->SetFBXMesh(_Name + ".fbx", "TextureAnimation");
	//GetAnimationFBXMesh()->CreateFBXAnimation("Test", _Name + ".fbx");
	//GetAnimationFBXMesh()->ChangeAnimation("Test");
	//// ���� �ʿ� => Chef �׽�Ʈ ������ ���� 
	//if (_Name == "Chef")
	//{
	//	GetFBXMesh()->GetTransform().SetWorldScale({ 1.f, 1.f, 1.f });
	//}
	//else
	//{
	//	GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
	//}
}

