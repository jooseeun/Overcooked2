#include "PreCompile.h"
#include "Candle.h"

Candle::Candle() 
	: CandleType_(CandleType::Max)
	, CandleTypeIndex_(0)
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

void Candle::SetCandleTypeIndex(int _TypeIndex)
{
	CandleTypeIndex_ = _TypeIndex;
	if (CandleTypeIndex_ == 0)
	{
		CandleType_ = CandleType::Middle;
	}
	else if (CandleTypeIndex_ == 1)
	{
		CandleType_ = CandleType::Left;
	}
	else if (CandleTypeIndex_ == 2)
	{
		CandleType_ = CandleType::Right;
	}
}
