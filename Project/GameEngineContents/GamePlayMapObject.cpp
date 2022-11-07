#include "PreCompile.h"
#include "GamePlayMapObject.h"

GamePlayMapObject::GamePlayMapObject()
	: Collision_(nullptr)
{
}

GamePlayMapObject::~GamePlayMapObject() 
{
}

void GamePlayMapObject::Start()
{
	GamePlayObject::Start();

	GetTransform().SetLocalScale({ 1.f, 1.f, 1.f });
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_StaticObject);
	GetCollisionObject()->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });	// ���� ũ��� 0.01
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
	}
}
