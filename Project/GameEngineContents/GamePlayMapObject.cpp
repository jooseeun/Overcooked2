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

void GamePlayMapObject::SetMapObjectMesh(const std::string& _Name)
{
	GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
	//GetFBXMesh()->GetTransform().SetLocalScale({ 100.f, 100.f, 100.f });

	// ���� �ʿ�
	if (_Name == "Chef")
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 1.f, 1.f, 1.f });
	}
	else
	{
		GetFBXMesh()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
		//GetFBXMesh()->GetTransform().SetWorldMove({ -1891.f, 0.f, -3908.f});
	}
}

