#include "PreCompile.h"
#include "MoveCar.h"

MoveCar::MoveCar()
	: State_(MOVECARSTATE::WAIT)
	, TimeInterval_(0.f)
	, StartPos_(float4::ZERO)
	, EndPos_(float4::ZERO)
	, IsMove_(false)
	, StartTime_(0.f)
	, StackTime_(0.f)
{
}

MoveCar::~MoveCar()
{
}

void MoveCar::Start()
{
	GamePlayObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 170.f, 80.f, 300.f }); // 원래 크기는 0.01
	GetCollisionObject()->GetTransform().SetLocalMove({ 0.f, 80.f });
	GetCollisionObject()->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0.8f, 0.5f });
	GetCollisionObject()->ChangeOrder(CollisionOrder::MoveCar);
}

void MoveCar::Update(float _DeltaTime)
{
	if (false == IsMove_)
	{
		StackTime_ += _DeltaTime;

		if (StackTime_ >= StartTime_)
		{
			StartTime_ = 0.f;
			IsMove_ = true;
		}
	}

	if (true == IsMove_)
	{
		switch (State_)
		{
		case MOVECARSTATE::WAIT:
			TimeInterval_ += _DeltaTime;

			if (5.f <= TimeInterval_)
			{
				TimeInterval_ = 0.f;
				State_ = MOVECARSTATE::DRIVE;
			}
			break;
		case MOVECARSTATE::DRIVE:
			GetTransform().SetWorldMove(GetTransform().GetLocalBackVector() * 1300.f * _DeltaTime);

			if (0 >= EndPos_.z
				&& GetTransform().GetWorldPosition().z <= EndPos_.z)
			{
				State_ = MOVECARSTATE::ARRIVAL;
			}

			else if (0 <= EndPos_.z
				&& GetTransform().GetWorldPosition().z >= EndPos_.z)
			{
				State_ = MOVECARSTATE::ARRIVAL;
			}
			break;
		case MOVECARSTATE::ARRIVAL:
			GetTransform().SetWorldPosition(StartPos_);
			State_ = MOVECARSTATE::WAIT;
			break;
		}
	}
}

