#include "PreCompile.h"
#include "Lift.h"
#define Lift_MaxHigh 15
#define Lift_MinHigh -217
#define Lift_Time 3.f

Lift::Lift()
	: MoveTime_(-2.f)
	, WaitingTime_(0.f)
	, Speed_(150.f)
	, LiftState_(LIFTSTATE::UP)
	, LerpTime_(0)
{
}

Lift::~Lift() 
{
}

void Lift::Start()
{
	GamePlayFloor::Start();

	GetCollisionObject()->GetTransform().SetLocalMove({0, 0, 20});
	GetCollisionObject()->GetTransform().SetLocalScale({ 312, 195, 50 });
	GetCollisionObject()->ChangeOrder(CollisionOrder::Lift);

	
	std::shared_ptr<GameEngineCollision> PlusCol = CreateComponent<GameEngineCollision>();
	PlusCol->GetTransform().SetLocalScale({ 307.00,194.00,130.00 });
	PlusCol->GetTransform().SetLocalPosition( GetTransform().GetWorldPosition() - float4{0,0,-130 });
	PlusCol->ChangeOrder(CollisionOrder::Map_Object);
}

void Lift::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	if (ServerInitManager::Net == nullptr)
	{
		switch (LiftState_)
		{
		case LIFTSTATE::UP:
			MoveTime_ += _DeltaTime;

			if (5.f <= MoveTime_)
			{
				GetTransform().SetWorldMove(float4::UP * Speed_ * _DeltaTime);

				if (10.f <= GetTransform().GetWorldPosition().y)
				{
					GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, 10.f , GetTransform().GetWorldPosition().z });
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
				GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, -217.f , GetTransform().GetWorldPosition().z });
				LiftState_ = LIFTSTATE::UP;
			}
			break;
		}
	}
	else
	{
		if (ServerInitManager::Net->GetIsHost() != true)
		{
			_DeltaTime = 0;
		}

		const float4& WolrdPos = GetTransform().GetWorldPosition();
		switch (LiftState_)
		{
		case LIFTSTATE::UP:
			MoveTime_ += _DeltaTime;

			if (3.f <= MoveTime_)
			{
				LerpTime_ += _DeltaTime;
				float Lerp = (Lift_MinHigh * ((Lift_Time - LerpTime_) / 3.f)) + (Lift_MaxHigh * (LerpTime_ / Lift_Time)); // Lerp


				if (Lift_MaxHigh <= Lerp)
				{
					LerpTime_ = Lift_Time;
					Lerp = Lift_MaxHigh;
					MoveTime_ = 0.f;
					LiftState_ = LIFTSTATE::WAIT;
				}
				GetTransform().SetWorldPosition({ WolrdPos.x, Lerp ,WolrdPos.z });
			}
			break;
		case LIFTSTATE::WAIT:
			WaitingTime_ += _DeltaTime;

			if (2.f <= WaitingTime_)
			{
				WaitingTime_ = 0.f;
				LiftState_ = LIFTSTATE::DOWN;
				//LerpTime_ = 0;
			}
			break;
		case LIFTSTATE::DOWN:
			LerpTime_ -= _DeltaTime;
			float Lerp = (Lift_MinHigh * ((Lift_Time - LerpTime_) / 3.f)) + (Lift_MaxHigh * (LerpTime_ / Lift_Time)); // Lerp


			if (-217.f >= Lerp)
			{
				LerpTime_ = 0;
				Lerp = Lift_MinHigh;
				LiftState_ = LIFTSTATE::UP;
			}
			GetTransform().SetWorldPosition({ WolrdPos.x, Lerp ,WolrdPos.z });
			break;
		}

		if (ServerInitManager::Net->GetIsHost())
		{
			std::shared_ptr<ObjectCookingGagePacket> Packet = std::make_shared<ObjectCookingGagePacket>();
			Packet->ObjectID = GetNetID();
			Packet->CookingGage = LerpTime_;
			Packet->int_Index = static_cast<int>(LiftState_);
			Packet->float4_Index = { MoveTime_, WaitingTime_ , 0};
			//LiftState_ == LIFTSTATE::WAIT ? WaitingTime_ : MoveTime_;

			ServerInitManager::Net->SendPacket(Packet);
		}
	}

}



void Lift::SetServerCookingGage(std::shared_ptr<ObjectCookingGagePacket> _Packet)
{ 
	LerpTime_ = _Packet->CookingGage;
	LiftState_ = static_cast<LIFTSTATE>(_Packet->int_Index);
	MoveTime_ = _Packet->float4_Index.x;
	WaitingTime_ = _Packet->float4_Index.y;
}