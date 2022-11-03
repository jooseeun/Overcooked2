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
	GamePlayStaticObject::Start();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 100.f, 100.f, 100.f });
	Collision_->ChangeOrder(CollisionOrder::Default);
}

//void GamePlayMapObject::Update(float _DeltaTime)
//{
//}
//
//void GamePlayMapObject::End()
//{
//}
