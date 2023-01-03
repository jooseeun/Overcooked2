#include "PreCompile.h"
#include "TrafficLightBloom.h"
#include "MoveCar.h"
#include "GlobalGameData.h"

float TrafficLightBloom::ChangeTime_ = 0;
float TrafficLightBloom::WattingTime_ = 0;
LIGHTCOLOR TrafficLightBloom::Color_ = LIGHTCOLOR::RED;
LIGHTCOLOR TrafficLightBloom::BeforeColor_ = LIGHTCOLOR::RED;
TrafficLightBloom* TrafficLightBloom::Inst_ = nullptr;


TrafficLightBloom::TrafficLightBloom()
	: IsFirst_(true)
{
}

TrafficLightBloom::~TrafficLightBloom()
{
	if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
	{
		if (TrafficLightBloom::Inst_ == this)
		{
			ChangeTime_ = 0;
			Color_ = LIGHTCOLOR::RED;
			BeforeColor_ = LIGHTCOLOR::RED;
			TrafficLightBloom::Inst_ = nullptr;
		}
	}
}

void TrafficLightBloom::SetBloomActor()
{
	{
		Green_ = GetLevel()->CreateActor<GlobalBloomActor>();
		Green_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Green_->GetTransform().SetWorldMove({ 0.f, -50.f });
		Green_->GetTransform().SetWorldScale({ 350, 350 });
		Green_->SetColor({ 0.f, 1.f, 0.f, 1.f });
		Green_->Off();
	}

	{
		Yellow_ = GetLevel()->CreateActor<GlobalBloomActor>();
		Yellow_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Yellow_->GetTransform().SetWorldScale({ 350, 350 });
		Yellow_->SetColor({ 1.0f, 0.6f, 0.1f, 1.f });
		Yellow_->Off();
	}

	{
		Red_ = GetLevel()->CreateActor<GlobalBloomActor>();
		Red_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Red_->GetTransform().SetWorldScale({ 350, 350 });
		Red_->GetTransform().SetWorldMove({ 0.f, 50.f });
		Red_->SetColor({ 1.0f, 0.f, 0.0f, 1.f });
	}

	{
		Green_Ground = GetLevel()->CreateActor<GlobalBloomActor>();
		Green_Ground->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Green_Ground->GetTransform().SetWorldScale({ 500, 500 });
		Green_Ground->GetTransform().SetLocalRotation({ 90.f, 0.f });
		Green_Ground->GetTransform().SetWorldMove({ 0.f, -250.f, 100.f });
		Green_Ground->SetColor({ 0.f, 1.f, 0.f, 1.f });
		Green_Ground->Off();
	}

	{
		Yellow_Ground = GetLevel()->CreateActor<GlobalBloomActor>();
		Yellow_Ground->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Yellow_Ground->GetTransform().SetWorldScale({ 500, 500 });
		Yellow_Ground->GetTransform().SetLocalRotation({ 90.f, 0.f });
		Yellow_Ground->GetTransform().SetWorldMove({ 0.f, -250.f, 125.f });
		Yellow_Ground->SetColor({ 1.0f, 0.6f, 0.1f, 1.f });
		Yellow_Ground->Off();
	}

	{
		Red_Ground = GetLevel()->CreateActor<GlobalBloomActor>();
		Red_Ground->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Red_Ground->GetTransform().SetWorldScale({ 500, 500 });
		Red_Ground->GetTransform().SetLocalRotation({ 90.f, 0.f });
		Red_Ground->GetTransform().SetWorldMove({ 0.f, -250.f, 150.f });
		Red_Ground->SetColor({ 1.0f, 0.f, 0.0f, 1.f });
	}
}

void TrafficLightBloom::Start()
{
	if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
	{
		TrafficLightBloom::Inst_ = this;
	}
}

void TrafficLightBloom::Update(float _DeltaTime)
{
	if (GlobalGameData::IsGameStart() == false)
	{
		_DeltaTime = 0;
	}

	if ((ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost()) && TrafficLightBloom::Inst_ == this)
	{
		TrafficLightBloom::TrafficLightUpdate(_DeltaTime);

		if (ServerInitManager::Net->GetIsHost())
		{
			std::shared_ptr<ObjectCookingGagePacket> Packet = std::make_shared<ObjectCookingGagePacket>();
			Packet->ObjectID = MoveCar::InstList_.front()->GetNetID();
			Packet->int_Index = static_cast<int>(TrafficLightBloom::Color_);
			ServerInitManager::Net->SendPacket(Packet);
		}
	}

	switch (TrafficLightBloom::Color_)
	{
	case LIGHTCOLOR::GREEN:
		{
			Green_->On();
			Yellow_->Off();
			Red_->Off();

			Green_Ground->On();
			Yellow_Ground->Off();
			Red_Ground->Off();
		}
		break;
	case LIGHTCOLOR::YELLOW:
		{
			Green_->Off();
			Yellow_->On();
			Red_->Off();

			Green_Ground->Off();
			Yellow_Ground->On();
			Red_Ground->Off();
		}
		break;
	case LIGHTCOLOR::RED:
		{
			Green_->Off();
			Yellow_->Off();
			Red_->On();

			Green_Ground->Off();
			Yellow_Ground->Off();
			Red_Ground->On();
		}
		break;
	}
}

void TrafficLightBloom::TrafficLightUpdate(float _Delta)
{
	switch (TrafficLightBloom::Color_)
		{
		case LIGHTCOLOR::GREEN:
			if (!MoveCar::IsMovingCar())
			{
				TrafficLightBloom::Color_ = LIGHTCOLOR::YELLOW;
				TrafficLightBloom::BeforeColor_ = LIGHTCOLOR::GREEN;
				ChangeTime_ = 0.3f;
			}
			break;
		case LIGHTCOLOR::YELLOW:
		{
			ChangeTime_ -= _Delta;
			if (ChangeTime_ < 0)
			{
				if (TrafficLightBloom::BeforeColor_ == LIGHTCOLOR::GREEN)
				{
					TrafficLightBloom::Color_ = LIGHTCOLOR::RED;
					TrafficLightBloom::BeforeColor_ = LIGHTCOLOR::YELLOW;

					TrafficLightBloom::WattingTime_ = GameEngineRandom::MainRandom.RandomFloat(1.5f, 5.f);
				}
				else // RED
				{
					MoveCar* Car = MoveCar::SelectCar();
					if (Car != nullptr)
					{
						Car->IsMove_ = true;
						TrafficLightBloom::Color_ = LIGHTCOLOR::GREEN;
						TrafficLightBloom::BeforeColor_ = LIGHTCOLOR::YELLOW;
					}
				}
			}
		}
			break;
		case LIGHTCOLOR::RED:
		{
			WattingTime_ -= _Delta;
			if (WattingTime_ < 0 && MoveCar::IsWattingCar())
			{
				TrafficLightBloom::Color_ = LIGHTCOLOR::YELLOW;
				TrafficLightBloom::BeforeColor_ = LIGHTCOLOR::RED;
				ChangeTime_ = 0.3f;
			}
		}
		break;
			//ChangeTime_ += _DeltaTime;

			//if (20.f <= ChangeTime_ && true == IsFirst_)
			//{
			//	IsFirst_ = false;

			//	Red_->Off();
			//	Yellow_->On();

			//	Red_Ground->Off();
			//	Yellow_Ground->On();

			//	Color_ = LIGHTCOLOR::YELLOW;
			//	ChangeTime_ = 0.f;
			//}

			//else if (2.f <= ChangeTime_ && false == IsFirst_)
			//{
			//	Red_->Off();
			//	Yellow_->On();

			//	Red_Ground->Off();
			//	Yellow_Ground->On();

			//	Color_ = LIGHTCOLOR::YELLOW;
			//	ChangeTime_ = 0.f;
			//}
			break;
		}

}

void TrafficLightBloom::LevelStartEvent()
{
	if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
	{
		TrafficLightBloom::Inst_ = this;
		TrafficLightBloom::WattingTime_ = 10.f;
	}
}
void TrafficLightBloom::LevelEndEvent()
{
	if ((ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost()) && TrafficLightBloom::Inst_ == this)
	{
		ChangeTime_ = 0;
		Color_ = LIGHTCOLOR::RED;
		BeforeColor_ = LIGHTCOLOR::RED;
		TrafficLightBloom::Inst_ = nullptr;
	}
}