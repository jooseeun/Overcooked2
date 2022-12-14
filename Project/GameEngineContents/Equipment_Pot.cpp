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

bool Equipment_Pot::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Cooker)
	{
		if (Rice_)
		{
			if (Rice_->Input_Auto(_DeltaTime, 12.f))
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
		if (Rice_ == nullptr)
		{
			std::shared_ptr<Food_Ingredients_Rice> Rice = (*_Moveable)->CastThis<Food_Ingredients_Rice>();
			if (Rice != nullptr
				&& !Rice->GetPlatting())
			{
				Rice_ = Rice;
				Rice_->SetParent(shared_from_this());
				Rice_->GetTransform().SetLocalPosition(float4::ZERO);
				Rice_->GetTransform().SetLocalRotation(float4::ZERO);
				Rice_->GetCollisionObject()->Off();
				Rice_->GetFBXMesh()->Off();

				(*_Moveable) = nullptr;
				return HoldDownEnum::HoldUp;
			}
		}
		else
		{
			std::shared_ptr<GamePlayMoveable> Moveable = Rice_;
			switch ((*_Moveable)->PickUp(&Moveable))
			{
			case HoldDownEnum::HoldUp:
				Rice_ = nullptr;
				return HoldDownEnum::Nothing;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (Rice_ != nullptr)
		{
			if ((*_Moveable) == nullptr)
			{
				Rice_->GetFBXMesh()->On();
				(*_Moveable) = CastThis<GamePlayMoveable>();
				return HoldDownEnum::HoldDown;
			}
		}
	}
	return HoldDownEnum::Nothing;
}