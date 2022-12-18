#include "PreCompile.h"
#include "Equipment_Bowl.h"

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

	GetFBXMesh()->SetFBXMesh("Bowl.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	CreateFoodThumbnail(1);
}

void Equipment_Bowl::Update(float _DeltaTime)
{

}

bool Equipment_Bowl::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Mixer)
	{
		if (FoodThumbnail_IngredientType[0] != IngredientType::None)
		{
			if (Input_Auto(_DeltaTime, 12.f))
			{
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
					if (FoodThumbnail_IngredientType.size() < 2)
					{
						if (PushFoodThumbnail(Food->GetObjectFoodClass()))
						{
							(*_Moveable)->Death();
							(*_Moveable)->Off();
							(*_Moveable) = nullptr;

							return HoldDownEnum::HoldUp;
						}
					}
					else
					{
						return HoldDownEnum::Nothing;
					}
				}
			}
		}
		else
		{
			//if ((*_Moveable)->CastThis<Equipment_FryingPan>() != nullptr)
			//{
			//	std::weak_ptr<GamePlayFood> Index = (*_Moveable)->CastThis<Equipment_FryingPan>()->FryFood_;
			//	(*_Moveable)->CastThis<Equipment_FryingPan>()->SetFryFood(FryFood_);
			//	SetFryFood(Index.lock());
			//}
		}
	}
	return HoldDownEnum::Nothing;
}
