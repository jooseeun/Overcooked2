#include "PreCompile.h"
#include "Equipment_Steamer.h"

Equipment_Steamer::Equipment_Steamer() 
	: Angle_(0.f)
	, IsInteraction_(false)
	, IsOpen_(false)
	, SteamerState_(SteamerState::Idle)
	, OpenPos_(0, 30, -20)
	, CurPos_(0.f)
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

	GetFBXMesh()->SetFBXMesh("Steamer3.FBX", "Texture", 1);
	GetFBXMesh()->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	GetCollisionObject()->GetTransform().SetLocalScale({ 100 , 100, 100 });

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
	Angle_ = -45.f;
}

void Equipment_Steamer::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsInteraction_)
	{
		StateManager.ChangeState("Close");
	}
	LidRenderer_->GetTransform().SetWorldRotation({ Angle_, 0, 0 });
	LidRenderer_->GetTransform().SetLocalPosition(OpenPos_);
}

void Equipment_Steamer::OpenStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Open);
	IsInteraction_ = false;
}

void Equipment_Steamer::OpenUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (-45.f >= Angle_)
	{
		Angle_ = -45.f;
		StateManager.ChangeState("Idle");
	}

	Angle_ -= _DeltaTime * 80.f;
	Lid_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
}

void Equipment_Steamer::CookingStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Cooking);
	IsInteraction_ = false;
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
}

void Equipment_Steamer::CloseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.f <= Angle_)
	{
		Angle_ = 0.f;
		StateManager.ChangeState("Cooking");
	}

	Angle_ += _DeltaTime * 80.f;
	Lid_->GetTransform().SetWorldRotation({ Angle_, 0.f, 0.f });
}
