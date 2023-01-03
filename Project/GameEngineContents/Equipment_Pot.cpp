#include "PreCompile.h"
#include "Equipment_Pot.h"
#include "Equipment_Plate.h"

Equipment_Pot::Equipment_Pot() 
{
}

Equipment_Pot::~Equipment_Pot() 
{
}

void Equipment_Pot::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Pot);

	GetFBXMesh()->SetFBXMesh("m_sk_pot_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetCombinFood()->Start(1, shared_from_this());
}

void Equipment_Pot::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	if (MyMoveableState_ == MoveableState::Cooking)
	{
		if (GetParent() != nullptr && GetParent()->CastThis<Player>() != nullptr)
		{
			MyMoveableState_ = MoveableState::Idle;
			IsSound_ = false;
			ObjSoundPlayer_.Stop();
		}
	}
}

bool Equipment_Pot::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Cooker)
	{
		
		if (!GetCombinFood()->IsClear())
		{
			if (false == IsSound_)
			{
				MyMoveableState_ = MoveableState::Cooking;
				ObjSoundPlayer_ = GameEngineSound::SoundPlayControl("HotPotBubble.wav", -1);
				ObjSoundPlayer_.Volume(2.f);
				IsSound_ = true;
			}

			if (Input_Auto(_DeltaTime, 12.f))
			{
				return true;
			}
		}
	}
	return false;

}

HoldDownEnum Equipment_Pot::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
		{
			std::weak_ptr<GamePlayFood> Food = (*_Moveable)->CastThis<GamePlayFood>();
		
			if (Food.lock()->GetCookingType() == CookingType::Boil && Food.lock()->GetTrim())
			{
				if (GetCombinFood()->PushFood((*_Moveable)->CastThis<GamePlayFood>()->GetObjectFoodClass()))
				{
					(*_Moveable)->Death();
					(*_Moveable)->Off();
					(*_Moveable) = nullptr;
					return HoldDownEnum::HoldUp;
				}
			}

		}
		else if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Bowl)
		{
			std::weak_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
			if (!ChangeSameBowl(Bowl.lock()))
			{
				if (Bowl.lock()->GetCombinFood()->GetFoodType() != FoodType::None)
				{
					BowltoBowl(Bowl.lock());
				}
			}
		}
		else if ((*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Dish && GetCombinFood()->GetTrim())
		{
			std::weak_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
			Bowl.lock()->GetCombinFood()->AddFood(GetCombinFood());
		}
	}
	else
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		MyMoveableState_ = MoveableState::Idle;
		IsSound_ = false;
		ObjSoundPlayer_.Stop();
		return HoldDownEnum::HoldDown;
	}

	return HoldDownEnum::Nothing;
}