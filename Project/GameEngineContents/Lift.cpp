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
	GetCollisionObject()->ChangeOrder(CollisionOrder::Lift);

	
	std::shared_ptr<GameEngineCollision> PlusCol = CreateComponent<GameEngineCollision>();
	PlusCol->GetTransform().SetLocalScale({ 307.00,194.00,100.00 });
	PlusCol->GetTransform().SetLocalPosition( GetTransform().GetWorldPosition() - float4{0,0,-100 });
	PlusCol->ChangeOrder(CollisionOrder::Map_Object);
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
				MoveTime_ = 0.f;
				LiftState_ = LIFTSTATE::WAIT;
			}
		}
		break;
	case LIFTSTATE::WAIT:
		WaitingTime_ += _DeltaTime;

		if (2.f <= WaitingTime_)
		{
			WaitingTime_ = 0.f;
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

