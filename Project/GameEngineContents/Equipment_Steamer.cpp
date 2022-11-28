#include "PreCompile.h"
#include "Equipment_Steamer.h"

Equipment_Steamer::Equipment_Steamer() 
{
}

Equipment_Steamer::~Equipment_Steamer() 
{
}

void Equipment_Steamer::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetToolInfoType(ToolInfo::Steamer);

	Lid_ = GetLevel()->CreateActor<GameEngineActor>();
	Lid_->SetParent(shared_from_this());

	std::shared_ptr<GameEngineFBXStaticRenderer> LidRenderer = Lid_->CreateComponent<GameEngineFBXStaticRenderer>();
	LidRenderer->SetFBXMesh("Steamer2.fbx", "Texture", 0);
	LidRenderer->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	LidRenderer->GetTransform().SetWorldRotation({ 90, 0, 0 });

	GetFBXMesh()->SetFBXMesh("Steamer2.FBX", "Texture", 1);
	GetFBXMesh()->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	GetFBXMesh()->GetTransform().SetWorldRotation({90, 0, 0});
	GetCollisionObject()->GetTransform().SetLocalScale({ 100 , 100, 100 });


	//StateManager.CreateStateMember("Idle"
	//	, std::bind(&Equipment_Steamer::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
	//	, std::bind(&Equipment_Steamer::IdleStart, this, std::placeholders::_1)
	//);

	//StateManager.ChangeState("Idle");
}

void Equipment_Steamer::Update(float _DeltaTime)
{
}

void Equipment_Steamer::IdleStart(const StateInfo& _Info)
{
}

void Equipment_Steamer::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Equipment_Steamer::CookStartStart(const StateInfo& _Info)
{
}

void Equipment_Steamer::CookStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Equipment_Steamer::CookingStart(const StateInfo& _Info)
{
}

void Equipment_Steamer::CookingUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Equipment_Steamer::CookDoneStart(const StateInfo& _Info)
{
}

void Equipment_Steamer::CookDoneUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
