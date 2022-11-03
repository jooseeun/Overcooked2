#include "PreCompile.h"
#include "Player.h"

Player::Player() 
	:Speed_(400.0f)
	, CurAngle_(0)
	, CurDir_(PlayerDir::Back)
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
		GameEngineInput::GetInst()->CreateKey("PlayerDash", VK_MENU); // Ã¢ÀÌ ²¨Áø´Ù..

	}
	GameEngineFBXRenderer* Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("Chef.FBX", "Texture");
	class GameEngineFBXMesh* Mesh = Renderer->GetFBXMesh();
	int a = 0;


	PlayerRenderer = CreateComponent<GameEngineFBXRenderer>();
	PlayerRenderer->SetFBXMesh("Chef.FBX", "Texture");
	
	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::MoveStart, this, std::placeholders::_1)
	);

	StateManager.ChangeState("Idle");

	GameEngineCollision* Test = CreateComponent<GameEngineCollision>();
	Test->GetTransform().SetWorldScale({ 100, 100, 100 });
	Test->ChangeOrder(CollisionOrder::Default);

	
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


	GetTransform().SetLocalRotation({ 0, (float)CurAngle_, 0});
	if (MoveAngle() == true)
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
	}
	else
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ *0.5* _DeltaTime);
		return;
	}

}
bool Player::MoveAngle()
{
	int AngleCheck = (int)CurAngle_;
	if (AngleCheck == 360)
	{
		CurAngle_ = 0;
	}
	if (AngleCheck == -1)
	{
		CurAngle_ = 359;
	}

	if (CurDir_ == PlayerDir::Front)
	{
		if (AngleCheck > 0 && AngleCheck < 180)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			return false;
		}
		else if (AngleCheck >= 180)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck >= 270 || AngleCheck < 90)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck >= 90 && AngleCheck < 270)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck >= 0 && AngleCheck < 180)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck < 225 && AngleCheck > 45)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck < 135 || AngleCheck > 315)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck < 315 && AngleCheck > 135)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
			return false;
		}
		else if (AngleCheck < 45 || AngleCheck > 225)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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