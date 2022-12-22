#include "PreCompile.h"
#include "Oven.h"
#include "Equipment_Bowl.h"

Oven::Oven()
	: Door_(nullptr)
	, DoorRenderer_(nullptr)
	//, IsPut_(true)
	//, IsTakeOut_(false)
	, IsCooking_(false)
	, Angle_(0.f)
	, IsInteraction_(false)
{
}

Oven::~Oven() 
{
}

void Oven::Start()
{
	GamePlayStaticObject::Start();

	// 오븐 문
	Door_ = GetLevel()->CreateActor<GameEngineActor>();
	Door_->SetParent(shared_from_this());

	DoorRenderer_ = Door_->CreateComponent<GameEngineFBXStaticRenderer>();
	DoorRenderer_->SetFBXMesh("OvenDoor.fbx", "Texture");
	DoorRenderer_->GetTransform().SetWorldScale({ 100, 100, 100 });
	DoorRenderer_->GetTransform().SetWorldMove({ 0, 52, 50 });
	DoorRenderer_->GetTransform().SetWorldRotation({180, 0, 0 });

	// 오븐
	GetFBXMesh()->SetFBXMesh("Oven.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetStuff(GetLevel()->CreateActor<Tool_Oven>());
}

void Oven::Update(float _DeltaTime)
{
	if (true == IsInteraction_)
	{
		// 요리중 X
		if (false == IsCooking_)
		{
			if (0.f >= Angle_)
			{
				IsCooking_ = true;
				IsInteraction_ = false;
			}

			Angle_ -= _DeltaTime * 250.f;
			DoorRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });

		}
		// 요리중
		if (true == IsCooking_)
		{
			if (170.f <= Angle_)
			{
				Angle_ = 170.f;
				IsCooking_ = false;
				IsInteraction_ = false;
			}

			Angle_ += _DeltaTime * 250.f;
			DoorRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
		}
	}

	//if (true == IsPut_)
	//{
	//	if (0.f >= Angle_)
	//	{
	//		IsPut_ = false;
	//		IsTakeOut_ = true;
	//	}

	//	Angle_ -= _DeltaTime * 230.f;
	//	DoorRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
	//}
	//else if (true == IsTakeOut_)
	//{
	//	if (170.f <= Angle_)
	//	{
	//		Angle_ = 170.f;
	//		IsTakeOut_ = false;
	//		IsPut_ = true;
	//	}

	//	Angle_ += _DeltaTime * 230.f;
	//	DoorRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
	//}
}


Tool_Oven::Tool_Oven()
{

}
Tool_Oven::~Tool_Oven()
{

}

void Tool_Oven::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Auto);
	GamePlayTool::SetToolInfoType(ToolInfo::OvenPot);
	GamePlayTool::SetObjectToolType(ObjectToolType::Oven);

	//SetMoveablePos();

}

void Tool_Oven::Update(float _DeltaTime)
{
	if (GetCurrentMoveable() != nullptr)
	{
		if (GetCurrentMoveable()->AutoTrim(_DeltaTime, GetObjectToolType()))
		{
			//불 붙히는 애니메이션
		}
	}
}

HoldDownEnum Tool_Oven::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		if (GetCurrentMoveable() != nullptr)
		{
			(*_Moveable) = GetCurrentMoveable()->CastThis<GamePlayMoveable>();
			ReSetCurrentMoveable();
			return HoldDownEnum::HoldDown;
		}
	}
	else
	{
		std::shared_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
		if (Bowl != nullptr)
		{
			if (GetCurrentMoveable() == nullptr)
			{
				if (Bowl->GetObjectBowlType() == ObjectBowlType::Bowl)
				{
					if (Bowl->GetCombinFood()->GetFoodType() != FoodType::None && (Bowl->GetCombinFood()->GetCookType() == ToolInfo::Mixer || Bowl->GetCombinFood()->GetCookType() == ToolInfo::OvenPot))
					{
						FoodData BowlFoodData = Bowl->GetCombinFood()->GetFoodData();
			
						for (size_t i = 0; i < BowlFoodData.CommonCookery.size(); i++)
						{
							if (BowlFoodData.CommonCookery[i] ==  ToolInfo::OvenPot)
							{
								if (Bowl->GetCombinFood()->GetCookType() == ToolInfo::Mixer)
								{
									Bowl->ReSetCookingGage();
								}
								SetMoveable((*_Moveable));
								(*_Moveable) = nullptr;
								return HoldDownEnum::HoldUp;
							}
						}
					}
				}
			}
			else
			{
				//std::shared_ptr<Equipment_Bowl> OvenBowl = GetCurrentMoveable()->CastThis<Equipment_Bowl>();
				//if (Bowl->GetObjectBowlType() == ObjectBowlType::Plate &&
				//	OvenBowl->GetCookingOven() == true &&
				//	OvenBowl->GetCookingGage() > 100.f)
				//{
				//	Bowl->GetCombinFood()->Move(OvenBowl->GetCombinFood());
				//}
			}
		}
	}
	return HoldDownEnum::Nothing;
}
