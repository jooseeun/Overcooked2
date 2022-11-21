#include "PreCompile.h"
#include "Candle.h"

Candle::Candle() 
	: CandleType_(CandleType::Max)
	, CandleTypeIndex_(0)
	, MoveDir_(0.f)
	, Speed_(0.f)
	, ChangeTime_(0.f)
	, CurDir_(CandleDir::Max)
	, UpDowmDir_(0.f)
	, MoveTime_(0.f)
	, StopTime_(0.f)
	, StateName_{}
{
}

Candle::~Candle() 
{
}

void Candle::Start()
{
	GamePlayMapObject::Start();

	StateManager.CreateStateMember("LeftMove"
		, std::bind(&Candle::LeftMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Candle::LeftMoveStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("RightMove"
		, std::bind(&Candle::RightMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Candle::RightMoveStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("UpMove"
		, std::bind(&Candle::UpMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Candle::UpMoveStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("DownMove"
		, std::bind(&Candle::DownMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Candle::DownMoveStart, this, std::placeholders::_1)
	);
}

void Candle::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);
	//UpDownMove(_DeltaTime);

	//MoveTime_ += _DeltaTime;
}

void Candle::LeftMoveStart(const StateInfo& _Info)
{
	MoveDir_ = float4::RIGHT;
}

void Candle::LeftMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > ChangeTime_)
	{
		switch (CandleType_)
		{
		case CandleType::Middle:
		{
			MoveDir_ = float4::ZERO;
			StateName_ = "RightMove";
		}
			break;
		case CandleType::Left:
		{
			StateName_ = "UpMove";
		}
			break;
		case CandleType::Right:
		{
			StateName_ = "DownMove";
		}
			break;
		default:
			break;
		}
	}

	if (_Info.StateTime > StopTime_)
	{
		StateManager.ChangeState(StateName_);
	}
	GetFBXMesh()->GetTransform().SetLocalMove(MoveDir_ * Speed_ * _DeltaTime);
}

void Candle::RightMoveStart(const StateInfo& _Info)
{
	MoveDir_ = float4::LEFT;
}

void Candle::RightMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > ChangeTime_)
	{
		switch (CandleType_)
		{
		case CandleType::Middle:
		{
			MoveDir_ = float4::ZERO;
			StateName_ = "LeftMove";
		}
		break;
		case CandleType::Left:
		{
			StateName_ = "DownMove";
		}
		break;
		case CandleType::Right:
		{
			StateName_ = "UpMove";
		}
		break;
		default:
			break;
		}
	}
	if (_Info.StateTime > StopTime_)
	{
		StateManager.ChangeState(StateName_);
	}
	GetFBXMesh()->GetTransform().SetLocalMove(MoveDir_ * Speed_ * _DeltaTime);
}

void Candle::UpMoveStart(const StateInfo& _Info)
{
	MoveDir_ = float4::BACK;
}

void Candle::UpMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > ChangeTime_)
	{
		switch (CandleType_)
		{
		case CandleType::Left:
		{
			StateName_ = "RightMove";
		}
		break;
		case CandleType::Right:
		{
			StateName_ = "LeftMove";
		}
		break;
		default:
			break;
		}
	}
	if (_Info.StateTime > StopTime_)
	{
		StateManager.ChangeState(StateName_);
	}
	GetFBXMesh()->GetTransform().SetLocalMove(MoveDir_ * Speed_ * _DeltaTime);
}

void Candle::DownMoveStart(const StateInfo& _Info)
{
	MoveDir_ = float4::FORWARD;
}

void Candle::DownMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > ChangeTime_)
	{
		switch (CandleType_)
		{
		case CandleType::Left:
		{
			StateName_ = "LeftMove";
		}
		break;
		case CandleType::Right:
		{
			StateName_ = "RightMove";
		}
		break;
		default:
			break;
		}
	}
	if (_Info.StateTime > StopTime_)
	{
		StateManager.ChangeState(StateName_);
	}
	GetFBXMesh()->GetTransform().SetLocalMove(MoveDir_ * Speed_ * _DeltaTime);
}

void Candle::UpDownMove(float _DeltaTime)
{
	/*MoveDir_.y = 10.f;

	if (0.8f < MoveTime_)
	{
		if (6.f == MoveDir_.y)
		{
			MoveDir_.y = -6.f;
		}
		else if (-6.f == MoveDir_.y)
		{
			MoveDir_.y = 6.f;
		}

		MoveTime_ = 0.f;
	}*/

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

	InfoSetting();
}

void Candle::InfoSetting()
{
	switch (CandleType_)
	{
	case CandleType::Middle:
	{
		StateManager.ChangeState("RightMove");
		Speed_ = 25.f;
		ChangeTime_ = 10.f;
		StopTime_ = ChangeTime_ + 4.f;
	}
		break;
	case CandleType::Left:
	{
		StateManager.ChangeState("DownMove");
		Speed_ = 50.f;
		ChangeTime_ = 12.f;
		StopTime_ = ChangeTime_ + 1.5f;
	}
		break;
	case CandleType::Right:
	{
		StateManager.ChangeState("UpMove");
		Speed_ = 50.f;
		ChangeTime_ = 12.f;
		StopTime_ = ChangeTime_ + 1.5f;
	}
		break;
	default:
		break;
	}
}
