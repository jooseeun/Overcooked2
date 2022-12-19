#include "PreCompile.h"
#include "Equipment_Steamer.h"

Equipment_Steamer::Equipment_Steamer() 
	: Angle_(0.f)
	, IsInteraction_(false)
	, SteamerState_(SteamerState::Idle)
	, OpenPos_(0, 30, -20)
	, CurPos_(0.f)
	, IsMoveDone_(false)
	, ToolPos_(0.f)
	, IsRotateDone_(false)
{
}

Equipment_Steamer::~Equipment_Steamer() 
{
}

void Equipment_Steamer::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Steamer);

	Lid_ = GetLevel()->CreateActor<GameEngineActor>();
	Lid_->SetParent(shared_from_this());

	LidRenderer_ = Lid_->CreateComponent<GameEngineFBXStaticRenderer>();
	LidRenderer_->SetFBXMesh("Steamer3.fbx", "Texture", 0);
	LidRenderer_->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	LidRenderer_->GetTransform().SetLocalRotation({ -45, 0, 0 });
	LidRenderer_->GetTransform().SetLocalMove({ OpenPos_ });

	GetFBXMesh()->SetFBXMesh("Steamer3.FBX", "Texture", 1);
	GetFBXMesh()->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	GetCollisionObject()->GetTransform().SetLocalScale({ 100 , 100, 100 });

	ToolPos_ = { 0.f, 85.f, 25.f };

	StateManager.CreateStateMember("Idle"
		, std::bind(&Equipment_Steamer::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Open"
		, std::bind(&Equipment_Steamer::OpenUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::OpenStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Cooking"
		, std::bind(&Equipment_Steamer::CookingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::CookingStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Close"
		, std::bind(&Equipment_Steamer::CloseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::CloseStart, this, std::placeholders::_1)
	); 

	StateManager.ChangeState("Idle");
}

void Equipment_Steamer::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst()->IsDownKey("SteamerTest"))
	{
		IsInteraction_ = true;
	}
}

void Equipment_Steamer::IdleStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Idle);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
	Angle_ = -45.f;
	CurPos_ = OpenPos_;
}

void Equipment_Steamer::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsInteraction_)
	{
		StateManager.ChangeState("Close");
	}
}

void Equipment_Steamer::OpenStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Open);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
}

void Equipment_Steamer::OpenUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsRotateDone_ && true == IsMoveDone_)
	{
		StateManager.ChangeState("Idle");
	}
	if (-45.f >= Angle_)
	{
		Angle_ = -45.f;
		IsRotateDone_ = true;
	}

	if (CurPos_.y >= OpenPos_.y && CurPos_.z <= OpenPos_.z)
	{
		IsMoveDone_ = true;
	}

	if (CurPos_.y >= OpenPos_.y)
	{
		CurPos_.y = OpenPos_.y;
	}
	if (CurPos_.z <= OpenPos_.z)
	{
		CurPos_.z = OpenPos_.z;
	}

	Angle_ -= _DeltaTime * 150.f;
	CurPos_.y += _DeltaTime * 110.f;
	CurPos_.z -= _DeltaTime * 130.f;

	if (false == IsRotateDone_)
	{
		LidRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
	}
	if (false == IsMoveDone_)
	{
		LidRenderer_->GetTransform().SetLocalPosition({ CurPos_ });
	}
}

void Equipment_Steamer::CookingStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Cooking);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
}

void Equipment_Steamer::CookingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsInteraction_)
	{
		StateManager.ChangeState("Open");
	}
}

void Equipment_Steamer::CloseStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Close);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
}

void Equipment_Steamer::CloseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsRotateDone_ && true == IsMoveDone_)
	{
		StateManager.ChangeState("Cooking");
	}
	if (0.f <= Angle_)
	{
		IsRotateDone_ = true;
		Angle_ = 0.f;
	}
	if (CurPos_.y <= 0.f && CurPos_.z >= 0.f)
	{
		IsMoveDone_ = true;
	}

	if (CurPos_.y <= 0.f)
	{
		CurPos_.y = 0.f;
	}
	if (CurPos_.z >= 0.f)
	{
		CurPos_.z = 0.f;
	}
	Angle_ += _DeltaTime * 140.f;
	CurPos_.y -= _DeltaTime * 110.f;
	CurPos_.z += _DeltaTime * 130.f;

	if (false == IsRotateDone_)
	{
		LidRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
	}
	if (false == IsMoveDone_)
	{
		LidRenderer_->GetTransform().SetLocalPosition({ CurPos_ });
	}
}
