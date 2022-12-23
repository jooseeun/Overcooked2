#include "PreCompile.h"
#include "Cannon.h"
#include "Button.h"
#include "Player.h"

Cannon::Cannon() 
	: CurState_(CannonState::Max)
	, MaxAngle_(-40.f)
	, ReadyAngle_(-32.f)
	, CurAngle_(0.f)
	, IsCounterReaction_(false)
	, IsMoveDone_(false)
	, ReactCount_(0)
	, IsDownMove_(false)
{
}

Cannon::~Cannon() 
{
}

void Cannon::Start()
{
	
	BaseRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
	BaseRenderer->SetFBXMesh("Cannon_Base.fbx", "Texture");
	BaseRenderer->GetTransform().SetWorldScale({ 100, 100, 100 });

	Mesh_Object_ = CreateComponent<GameEngineFBXStaticRenderer>("Mesh_Object");
	Mesh_Object_->SetFBXMesh("m_dlc08_cannon_02.fbx", "Texture");
	Mesh_Object_->GetTransform().SetWorldScale({ 100, 100, 100 });
	Mesh_Object_->GetTransform().SetWorldMove({ 0, 100, 0 });

	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->ChangeOrder(CollisionOrder::Map_Cannon);
	Collision_Object_->GetTransform().SetWorldScale({ 100, 100, 100 });

	Button_ = GetLevel()->CreateActor<Button>();
	Button_->GetTransform().SetWorldMove({0.f, 0.f, 122.f});
	Button_->SetParent(shared_from_this());

	StateManager.CreateStateMember("Idle"
		, std::bind(&Cannon::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::IdleStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Ready"
		, std::bind(&Cannon::ReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ReadyStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Shoot"
		, std::bind(&Cannon::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ShootStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Down"
		, std::bind(&Cannon::DownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::DownStart, this, std::placeholders::_1)
	);

	StateManager.ChangeState("Idle");
}

void Cannon::Update(float _DeltaTime)
{
	if (Player_ != nullptr)
	{
		Player_->CannonZAngle_ = CurAngle_; 
	}

	StateManager.Update(_DeltaTime);

	DebugOn();
}

void Cannon::IdleStart(const StateInfo& _Info)
{
	if (Player_ == nullptr)
	{
		return;
	}
	CurState_ = CannonState::Idle;
}

void Cannon::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (Player_ == nullptr)
	{
		return;
	}

	if (true == Player_->IsCannon_)
	{
		StateManager.ChangeState("Ready");
	}
}

void Cannon::ReadyStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Ready;
	Button_->IsReady_ = true;
	IsMoveDone_ = false;
	IsCounterReaction_ = false;
	CurAngle_ = 0.f;
}

void Cannon::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 플레이어가 내렸다
	if (false == Player_->IsCannon_)
	{
		ResetPlayer();
		StateManager.ChangeState("Down");
	}
	// 버튼이 눌렸다
	else if (true == Button_->CheckButtonPressedState() && true == Player_->IsCannon_)
	{
		StateManager.ChangeState("Shoot");
	}
	else if (true == GameEngineInput::GetInst()->IsDownKey("MapObjectTest") && true == Player_->IsCannon_)	/// 테스트 //
	{
		StateManager.ChangeState("Shoot");
	}

	if (true == IsMoveDone_)
	{
		return;
	}

	if (false == IsCounterReaction_)
	{
		if (MaxAngle_ >= CurAngle_)
		{
			CurAngle_ = MaxAngle_;
			IsCounterReaction_ = true;
		}

		CurAngle_ -= _DeltaTime * 250.f;
		Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
	}
	else
	{
		if (ReadyAngle_ <= CurAngle_)
		{
			IsCounterReaction_ = false;
			IsMoveDone_ = true;
		}

		CurAngle_ += _DeltaTime * 100.f;
		Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
	}
}

void Cannon::ShootStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Shoot;
	Player_->IsCannon_ = false;
	Player_->IsCannonFly_ = true;
	Button_->IsReady_ = false;
	Button_->SetButtonUnPressed();
	ReactCount_ = 2;
}

void Cannon::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.f)
	{
		StateManager.ChangeState("Down");
	}



	// 반동
	if (_Info.StateTime > 0.4f)
	{
		if (0 != ReactCount_)
		{
			if (false == IsCounterReaction_)
			{
				if (ReadyAngle_ + 7.f <= CurAngle_)
				{
					IsCounterReaction_ = true;
				}

				CurAngle_ += _DeltaTime * 100.f;
				Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
			}
			else
			{
				if (ReadyAngle_ >= CurAngle_)
				{
					ReactCount_ -= 1;
					IsCounterReaction_ = false;
				}

				CurAngle_ -= _DeltaTime * 100.f;
				Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
			}
		}
	}
}

void Cannon::DownStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Down;
	IsMoveDone_ = false;
	IsCounterReaction_ = false;
	IsDownMove_ = true;
	ReactCount_ = 1;
}

void Cannon::DownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (nullptr != Player_)
	{
		if (true == Player_->IsCannon_)
		{
			StateManager.ChangeState("Ready");
		}
	}

	if (true == IsMoveDone_)
	{
		StateManager.ChangeState("Idle");
		return;
	}
	
	if (true == IsDownMove_)
	{
		if (0.f <= CurAngle_)
		{
			IsDownMove_ = false;
		}

		CurAngle_ += _DeltaTime * 220.f;
		Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
	}
	else
	{
		if (0 == ReactCount_)
		{
			IsMoveDone_ = true;
		}

		if (false == IsCounterReaction_)
		{
			if (-7.f >= CurAngle_)
			{
				IsCounterReaction_ = true;
			}

			CurAngle_ -= _DeltaTime * 100.f;
			Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
		}
		else
		{
			if (0.f <= CurAngle_)
			{
				CurAngle_ = 0.f;
				ReactCount_ -= 1;
				IsCounterReaction_ = false;
			}

			CurAngle_ += _DeltaTime * 100.f;
			Mesh_Object_->GetTransform().SetLocalRotation({ 0.f, 0.f, CurAngle_ });
		}
	}

}