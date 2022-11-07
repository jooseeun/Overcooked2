#include "PreCompile.h"
#include "Player.h"

Player::Player()
	:Speed_(400.0f)
	, CurAngle_(0)
	, CurDir_(PlayerDir::Back)
	, PlayerCollision_(nullptr)
	, PlayerRenderer_(nullptr)
{

}

Player::~Player()
{
}

void Player::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerFront", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PlayerDash", 'X');
		GameEngineInput::GetInst()->CreateKey("PlayerHold", 'Z');
		GameEngineInput::GetInst()->CreateKey("PlayerThrow", VK_SPACE);

	}
	//GameEngineFBXMesh* TestMesh = GameEngineFBXMesh::Find("Chef.FBX");

	//std::string NewPath = "C:Users\\MOA\\Overcooked2\\Project\\ContentsResources\\Mesh\\Chef1\\t_chef_head_alien_green_d.png";
	//size_t idx = NewPath.rfind("\\");

	//std::string TestStr = NewPath.substr(0, idx);

	//TestMesh->GetFbxRenderUnit()[0].MaterialData[0].DifTexturePath = NewPath;
	//TestMesh->GetFbxRenderUnit()[0].MaterialData[0].DifTextureName = "t_chef_head_alien_green_d.png";






	PlayerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PlayerRenderer_->SetFBXMesh("Chef1.FBX", "Texture");

	//PlayerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	//PlayerRenderer_->SetFBXMesh("AlienGreen_CarDeath.FBX", "Texture");

	PlayerCollision_ = CreateComponent<GameEngineCollision>();
	PlayerCollision_->GetTransform().SetLocalScale({ 100,100,100 });
	PlayerCollision_->ChangeOrder(CollisionOrder::Default);



	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::MoveStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Throw"
		, std::bind(&Player::ThrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ThrowStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Hold"
		, std::bind(&Player::HoldUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::HoldStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Slice"
		, std::bind(&Player::SliceUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SliceStart, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");




}
void Player::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);
	DashCheck();
}

void Player::IdleStart(const StateInfo& _Info)
{

}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Move");
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold"))
	{
		StateManager.ChangeState("Hold");
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerThrow"))
	{
		StateManager.ChangeState("Throw");
	}
}

void Player::MoveStart(const StateInfo& _Info)
{

}
void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{

		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront"))
	{
		CurDir_ = PlayerDir::Front;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft"))
		{
			CurDir_ = PlayerDir::FrontLeft;

		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight"))
		{
			CurDir_ = PlayerDir::FrontRight;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		CurDir_ = PlayerDir::Back;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft"))
		{
			CurDir_ = PlayerDir::BackLeft;
		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight"))
		{
			CurDir_ = PlayerDir::BackRight;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft"))
	{
		CurDir_ = PlayerDir::Left;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront"))
		{
			CurDir_ = PlayerDir::FrontLeft;
		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
		{
			CurDir_ = PlayerDir::BackLeft;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight"))
	{

		CurDir_ = PlayerDir::Right;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront"))
		{
			CurDir_ = PlayerDir::FrontRight;
		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
		{
			CurDir_ = PlayerDir::BackRight;
		}

	}


	GetTransform().SetLocalRotation({ 0, (float)CurAngle_, 0 });
	if (MoveAngle() == true)
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
	}
	else
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * 0.1 * _DeltaTime);
		return;
	}

}
void Player::ThrowStart(const StateInfo& _Info)
{

}
void Player::ThrowUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerThrow"))
	{
		StateManager.ChangeState("Idle");
	}
}

void Player::HoldStart(const StateInfo& _Info)
{

}
void Player::HoldUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerHold"))
	{
		StateManager.ChangeState("Idle");
	}
}

void Player::SliceStart(const StateInfo& _Info)
{

}
void Player::SliceUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


///////////////////////////// 그외 함수들
bool Player::MoveAngle()
{
	int AngleCheck = (int)CurAngle_;

	if (AngleCheck >= 360)
	{
		CurAngle_ = 0;
		AngleCheck = (int)CurAngle_;
	}
	if (AngleCheck <= -1)
	{
		CurAngle_ = 359;
		AngleCheck = (int)CurAngle_;
	}

	if (CurDir_ == PlayerDir::Front)
	{
		if (AngleCheck > 0 && AngleCheck < 180)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 0)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck >= 0)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 0)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 0)
		{
			return true;
		}
	}

	if (CurDir_ == PlayerDir::Right)
	{
		if (AngleCheck > 90 && AngleCheck < 270)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 90)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck >= 270 || AngleCheck < 90)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 90)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 90)
		{
			return true;
		}
	}
	if (CurDir_ == PlayerDir::Left)
	{
		if (AngleCheck > 270 || AngleCheck < 90)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 270)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck >= 90 && AngleCheck < 270)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 270)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 270)
		{
			return true;
		}
	}
	if (CurDir_ == PlayerDir::Back)
	{
		if (AngleCheck > 180 && AngleCheck < 360)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 180)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck >= 0 && AngleCheck < 180)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 180)
			{
				return true;
			}
			return false;
		}

		if (AngleCheck == 180)
		{
			return true;
		}
	}

	if (CurDir_ == PlayerDir::FrontRight)
	{
		if (AngleCheck < 45 || AngleCheck >= 225)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 45)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck < 225 && AngleCheck > 45)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 45)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 45)
		{
			return true;
		}
	}

	if (CurDir_ == PlayerDir::FrontLeft)
	{
		if (AngleCheck < 315 && AngleCheck >= 135)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 315)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck < 135 || AngleCheck > 315)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 315)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 315)
		{
			return true;
		}
	}
	if (CurDir_ == PlayerDir::BackRight)
	{
		if (AngleCheck < 135 || AngleCheck >= 315)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 135)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck < 315 && AngleCheck > 135)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 135)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 135)
		{
			return true;
		}
	}
	if (CurDir_ == PlayerDir::BackLeft)
	{
		if (AngleCheck < 225 && AngleCheck >= 45)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 225)
			{
				return true;
			}
			return false;
		}
		else if (AngleCheck < 45 || AngleCheck > 225)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 225)
			{
				return true;
			}
			return false;
		}
		if (AngleCheck == 225)
		{
			return true;
		}
	}
}


void Player::DashCheck()
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerDash"))
	{
		if (Speed_ < 500.0f)
		{
			Speed_ = 1000.0f;
		}
	}
	if (Speed_ > 400.0f)
	{
		Speed_ -= 200.0f * GameEngineTime::GetDeltaTime();
	}
	else
	{
		Speed_ = 400.0f;
	}
}