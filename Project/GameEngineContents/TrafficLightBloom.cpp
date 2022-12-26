#include "PreCompile.h"
#include "TrafficLightBloom.h"

TrafficLightBloom::TrafficLightBloom()
	: Color_(LIGHTCOLOR::RED)
	, ChangeTime_(0.f)
	, IsFirst_(true)
{
}

TrafficLightBloom::~TrafficLightBloom()
{
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

}

void TrafficLightBloom::Update(float _DeltaTime)
{
	switch (Color_)
	{
	case LIGHTCOLOR::GREEN:
		ChangeTime_ += _DeltaTime;

		if (2.f <= ChangeTime_)
		{
			Green_->Off();
			Red_->On();

			Green_Ground->Off();
			Red_Ground->On();

			Color_ = LIGHTCOLOR::RED;
			ChangeTime_ = 0.f;
		}
		break;
	case LIGHTCOLOR::YELLOW:
		ChangeTime_ += _DeltaTime;

		if (0.5f <= ChangeTime_)
		{
			Yellow_->Off();
			Green_->On();

			Yellow_Ground->Off();
			Green_Ground->On();

			Color_ = LIGHTCOLOR::GREEN;
			ChangeTime_ = 0.f;
		}
		break;
	case LIGHTCOLOR::RED:
		ChangeTime_ += _DeltaTime;

		if (20.f <= ChangeTime_ && true == IsFirst_)
		{
			IsFirst_ = false;

			Red_->Off();
			Yellow_->On();

			Red_Ground->Off();
			Yellow_Ground->On();

			Color_ = LIGHTCOLOR::YELLOW;
			ChangeTime_ = 0.f;
		}

		else if (2.f <= ChangeTime_ && false == IsFirst_)
		{
			Red_->Off();
			Yellow_->On();

			Red_Ground->Off();
			Yellow_Ground->On();

			Color_ = LIGHTCOLOR::YELLOW;
			ChangeTime_ = 0.f;
		}
		break;
	}
}

