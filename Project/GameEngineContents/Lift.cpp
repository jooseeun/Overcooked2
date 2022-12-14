#include "PreCompile.h"
#include "Lift.h"

Lift::Lift()
	: MoveTime_(0.f)
	, WaitingTime_(0.f)
	, Speed_(85.f)
	, LiftState_(LIFTSTATE::UP)
{
}

Lift::~Lift() 
{
}

void Lift::Start()
{
	GamePlayFloor::Start();

	GetCollisionObject()->GetTransform().SetLocalPosition({ GetTransform().GetWorldPosition()});
}

void Lift::Update(float _DeltaTime)
{
	switch (LiftState_)
	{
	case LIFTSTATE::UP:
		MoveTime_ += _DeltaTime;

		if (5.f <= MoveTime_)
		{
			GetTransform().SetWorldMove(float4::UP * Speed_ * _DeltaTime);

			if (0.f <= GetTransform().GetWorldPosition().y)
			{
				MoveTime_ -= 5.f;
				LiftState_ = LIFTSTATE::WAIT;
			}
		}
		break;
	case LIFTSTATE::WAIT:
		WaitingTime_ += _DeltaTime;

		if (2.f <= WaitingTime_)
		{
			WaitingTime_ -= 2.f;
			LiftState_ = LIFTSTATE::DOWN;
		}
		break;
	case LIFTSTATE::DOWN:
		GetTransform().SetWorldMove(float4::DOWN * Speed_ * _DeltaTime);

		if (-217.f >= GetTransform().GetWorldPosition().y)
		{
			LiftState_ = LIFTSTATE::UP;
		}
		break;
	}
}

