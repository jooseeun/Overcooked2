#include "PreCompile.h"
#include "Candle.h"

Candle::Candle() 
{
}

Candle::~Candle() 
{
}

void Candle::Start()
{
	GamePlayMapObject::Start();
}

void Candle::Update(float _DeltaTime)
{
	switch (CandleType_)
	{
	case CandleType::Left:
	{

	}
		break;
	case CandleType::Right:
	{

	}
		break;
	case CandleType::Middle:
	{

	}
		break;
	default:
		break;
	}
}

void Candle::SetCandleTypeIndex(float4 TypeIndex)
{
	CandleTypeIndex_ = TypeIndex.x;
	if (TypeIndex.x == 0)
	{
		CandleType_ = CandleType::Middle;
	}
	else if (TypeIndex.x == 1)
	{
		CandleType_ = CandleType::Left;
	}
	else if (TypeIndex.x == 2)
	{
		CandleType_ = CandleType::Right;
	}
}
