#include "PreCompile.h"
#include "Oven.h"

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

