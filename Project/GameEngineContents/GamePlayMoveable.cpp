#include "PreCompile.h"
#include "GamePlayMoveable.h"

GamePlayMoveable::GamePlayMoveable()
	: CookingGage_(0)
	, CookedStat_Current_(CookedStat::Nomal)
{
}

GamePlayMoveable::~GamePlayMoveable()
{
}

void GamePlayMoveable::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Moveable);

}

CookedStat GamePlayMoveable::Cook_Update(float _Delta)
{
	if (CookingGage_ <= 0)
	{
		if (Cook_Start_Child() == CookedStat::Nomal)
		{
			return CookedStat::Nomal;
		}
	}
	Cook_Update_Child(_Delta);

	return(Cook_Check_Child());
}