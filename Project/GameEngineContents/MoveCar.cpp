#include "PreCompile.h"
#include "MoveCar.h"
#include "TrafficLightBloom.h"

std::list<MoveCar*> MoveCar::InstList_;

MoveCar::MoveCar()
	: State_(MOVECARSTATE::WAIT)
	, TimeInterval_(0.f)
	, StartPos_(float4::ZERO)
	, EndPos_(float4::ZERO)
	, IsMove_(false)
	, StartTime_(0.f)
	, StackTime_(0.f)
	, IsSound_(false)
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

void MoveCar::SetServerCookingGage(std::shared_ptr<ObjectCookingGagePacket> _Packet)
{
	TrafficLightBloom::SetColor(static_cast<LIGHTCOLOR>(_Packet->int_Index));
}

void MoveCar::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	if (ServerInitManager::Net== nullptr || ServerInitManager::Net->GetIsHost())
	{
		if (true == IsMove_)
		{
			switch (State_)
			{
			case MOVECARSTATE::WAIT:
				State_ = MOVECARSTATE::DRIVE;
				IsSound_ = true;
				break;
			case MOVECARSTATE::DRIVE:
				{
					if (true == IsSound_)
					{
						IsSound_ = false;
						GameEngineSound::SoundPlayOneShot("FE_Traffic_Passby_01.wav");
					}
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


					{

						std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
						Packet->ObjectID = GetNetID();
						Packet->Type = ServerObjectType::Object;
						Packet->State = ServerObjectBaseState::Base;
						Packet->Pos = GetTransform().GetWorldPosition();
						Packet->Rot = GetTransform().GetWorldRotation();
						Packet->Scale = GetTransform().GetWorldScale();

						ServerInitManager::Net->SendPacket(Packet);
					}
				}
				break;
			case MOVECARSTATE::ARRIVAL:
				GetTransform().SetWorldPosition(StartPos_);
				State_ = MOVECARSTATE::WAIT;
				IsMove_ = false;
				break;
			}
		}
		
	}
}

MoveCar* MoveCar::SelectCar()
{
	std::vector<MoveCar*> Can_Car;
	for (auto* Car : InstList_)
	{
		if (Car->IsMove_ == false)
		{
			Can_Car.push_back(Car);
		}
	}

	if (Can_Car.empty())
	{
		return nullptr;
	}
	else
	{
		int Random = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Can_Car.size()) - 1);
		return Can_Car[Random];
	}
}

bool MoveCar::IsWattingCar()
{
	for (auto* Car : InstList_)
	{
		if (Car->IsMove_ == false)
		{
			return true;
		}
	}
	return false;
}

bool MoveCar::IsMovingCar()
{
	for (auto* Car : InstList_)
	{
		if (Car->IsMove_ == true)
		{
			return true;
		}
	}
	return false;
}

void MoveCar::LevelStartEvent()
{
	MoveCar::InstList_.push_back(this);
}
void MoveCar::LevelEndEvent()
{
	MoveCar::InstList_.clear();
}