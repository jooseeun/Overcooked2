#include "PreCompile.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight() 
	: Color_(LIGHTCOLOR::RED)
{
}

TrafficLight::~TrafficLight() 
{
}

void TrafficLight::Start()
{
	GamePlayMapObject::Start();
}

void TrafficLight::Update(float _DeltaTime)
{
	switch (Color_)
	{
	case LIGHTCOLOR::GREEN:
		if (3.f <= ChangeTime_)
		{
			Color_ = LIGHTCOLOR::GREEN;
			ChangeTime_ = 0.f;
		}
		break;
	case LIGHTCOLOR::YELLOW:
		ChangeTime_ += _DeltaTime;

		if (0.1f <= ChangeTime_)
		{
			Color_ = LIGHTCOLOR::GREEN;
			ChangeTime_ = 0.f;
		}
		break;
	case LIGHTCOLOR::RED:
		ChangeTime_ += _DeltaTime;

		if (19.f <= ChangeTime_)
		{
			Color_ = LIGHTCOLOR::YELLOW;
			ChangeTime_ = 0.f;
		}
		break;
	default:
		break;
	}
}

