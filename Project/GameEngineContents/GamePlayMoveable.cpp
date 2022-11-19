#include "PreCompile.h"
#include "GamePlayMoveable.h"

GamePlayMoveable::GamePlayMoveable()
	: CookingGage_(0)
	//, CookedStat_Current_(CookedStat::Nomal)
{
}

GamePlayMoveable::~GamePlayMoveable()
{
}

void GamePlayMoveable::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Moveable);
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_Moveable);

}
void GamePlayMoveable::Update(float _DeltaTime)
{
	if (GetParent() == nullptr)
	{
		if (GetCollisionObject()->IsCollision(CollisionType::CT_AABB, CollisionOrder::Floor, CollisionType::CT_AABB) == false)
		{
			GetTransform().SetWorldDownMove(300.0f, GameEngineTime::GetDeltaTime());
		}
		
		if (GetCollisionObject()->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false)
		{

		}
	}

	if (true)
	{

	}
}


//CookedStat GamePlayMoveable::Cook_Update(float _Delta)
//{
//	if (CookingGage_ <= 0)
//	{
//		if (Cook_Start_Child() == CookedStat::Nomal)
//		{
//			return CookedStat::Nomal;
//		}
//	}
//	Cook_Update_Child(_Delta);
//
//	return(Cook_Check_Child());
//}