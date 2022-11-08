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
	GetCollisionObject()->SetDebugSetting(CollisionType::CT_AABB, { 0, 0, 0.8f, 0.5f });	// 일반 벽, 갈 수 없는 지역, NPC => 파랑
	GetCollisionObject()->GetTransform().SetWorldScale({ 50.f, 50.f, 50.f });				// 원래 크기는 0.01
}

void GamePlayMapObject::Update(float _DeltaTime)
{

}

void GamePlayMapObject::SetMapObjectMesh(const std::string& _Name)
{
	GetFBXMesh()->SetFBXMesh(_Name + ".fbx", "Texture");
	//GetFBXMesh()->GetTransform().SetLocalScale({ 100.f, 100.f, 100.f });

	// 수정 필요
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

