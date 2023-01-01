#include "PreCompile.h"
#include "Equipment_Bowl.h"
#include "Equipment_Steamer.h"

Equipment_Bowl::Equipment_Bowl()
{
}

Equipment_Bowl::~Equipment_Bowl() 
{
}

void Equipment_Bowl::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Bowl);
	GamePlayBowl::SetObjectBowlType(ObjectBowlType::Bowl);

	GetFBXMesh()->SetFBXMesh("Bowl.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

//	GetCombinFood()->Start(2, shared_from_this());
}

//void Equipment_Bowl::Update(float _DeltaTime)
//{
//	//GetTransform().SetWorldRotation(float4::ZERO);
//
//	//GameEngineDebug::OutPutString(std::to_string(GetTransform().GetWorldRotation().x) + " + "  + std::to_string(GetTransform().GetWorldRotation().y) + " + " + std::to_string(GetTransform().GetWorldRotation().z));
//}

bool Equipment_Bowl::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Mixer)
	{
		if (!GetCombinFood()->IsClear())
		{
			if (Input_Auto(_DeltaTime, 12.f))
			{
				GetCombinFood()->SetCookType(ToolInfo::Mixer);
				return true;
			}
		}
	}
	else if (_Tool == ObjectToolType::Oven)
	{
		if (!GetCombinFood()->IsClear())
		{
			if (Input_Auto(_DeltaTime, 12.f))
			{
				GetCombinFood()->SetCookType(ToolInfo::OvenPot);
				return true;
			}
		}
	}
	return false;
}

void Equipment_Bowl::FinishTrimmingFirst()
{

}

HoldDownEnum Equipment_Bowl::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		return HoldDownEnum::HoldDown;
	}
	else
	{
		if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
		{
			std::shared_ptr<GamePlayFood> Food = (*_Moveable)->CastThis<GamePlayFood>();
			if (Food->GetTrim())
			{
				if (Food->GetCookingType() == CookingType::Mixer)
				{
					if (GetCombinFood()->PushFood(Food->GetObjectFoodClass()))
					{
						(*_Moveable)->Death();
						(*_Moveable)->Off();
						(*_Moveable) = nullptr;

						return HoldDownEnum::HoldUp;
					}
				}
			}
		}
		else if (!GetCombinFood()->IsClear())
		{
			std::shared_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
			if (Bowl != nullptr)
			{
				if (!ChangeSameBowl(Bowl))
				{
					if (Bowl->GetObjectBowlType() == ObjectBowlType::Steamer)
					{
						if (Bowl->GetCombinFood()->GetTrim())
						{
							(*_Moveable)->CastThis<Equipment_Steamer>()->BowltoSteamer(CastThis<Equipment_Bowl>());
						}
					}
				}
			}
		}

	}
	return HoldDownEnum::Nothing;
}
