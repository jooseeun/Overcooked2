#include "PreCompile.h"
#include "Player.h"
#include "GamePlayStaticObject.h"
#include "CounterTop.h"
#include "Cannon.h"
#include "Button.h"
#include "Lift.h"
#include <math.h>


//player key
//이동 - 방향키
//다지기/던지기 - 왼쪽 CTRL
//잡기/놓기 - SPACEBAR
//대쉬 - 왼쪽 ALT
//감정표현 - E

Player::Player()
	:Speed_(650.0f)
	, CurAngle_(180.0f)
	, CurDir_(PlayerDir::Back)
	, CurHoldType_(PlayerHoldType::CanThrow)
	, CurStateType_(PlayerCurStateType::Max)
	, PlayerFloorCollision_(nullptr)
	, PlayerForwardCollision_(nullptr)
	, PlayerForwardLeftCollision_(nullptr)
	, PlayerForwardRightCollision_(nullptr)
	, PlayerRightCollision_(nullptr)
	, PlayerLeftCollision_(nullptr)
	, PlayerBackCollision_(nullptr)
	, PlayerCollision_(nullptr)
	, PlayerCameraCollision_(nullptr)
	, PlayerCustomNum(5)
	, PlayerIdleRenderer_()
	, PlayerWalkRenderer_()
	, PlayerChopRenderer_()
	, PlayerWashRenderer_()
	, StateManager()
	, CurrentHoldingObject_(nullptr)
	, FireOff_(false)
	, PlayerName_()
	, PlayerPNum(1)
	, IsSlice_(false)
	, DashTime_(0.0f)
	, IsSingleMode(false)
	, PNumString("")
	, CameraUpTime_(1.0f)
	, IsCameraMove_(true)
	, ThrowVec_()
	, IsThrow_(false)
	, IsPotal_(false)
	, DeathTime_(0.0f)
	, ResponePos_(float4{ -1400, 200, 200 })
	, IsSink_(false)
	, IsHolding_("Idle")
	, FlyTime_(0.0f)
	, CannonFlyPos_()
	, IsCannon_(false)
	, IsCannonFly_(false)
{

}

Player::~Player()
{
}

void Player::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });



	{
		PlayerName_[0] = "AlienGreen";
		PlayerName_[1] = "Buck";
		PlayerName_[2] = "Crocodile";
		PlayerName_[3] = "Dora";
		PlayerName_[4] = "Eagle";
		PlayerName_[5] = "Panda";

	}

	for (int i = 0; i < 6; i++)
	{
		PlayerIdleRenderer_[i] = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerIdleRenderer_[i]->SetFBXMesh(PlayerName_[i] + "_Idle.FBX", "TextureAnimation");

		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Idle",
			GameEngineRenderingEvent(PlayerName_[i] + "_Idle.FBX", 0.035f, true));

		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Idle2",
			GameEngineRenderingEvent(PlayerName_[i] + "_Idle2.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "WalkHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_WalkHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CarDeath",
			GameEngineRenderingEvent(PlayerName_[i] + "_CarDeath.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Death",
			GameEngineRenderingEvent(PlayerName_[i] + "_Death.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Drowning",
			GameEngineRenderingEvent(PlayerName_[i] + "_Drowning.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Fall",
			GameEngineRenderingEvent(PlayerName_[i] + "_Fall.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "IdleHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_IdleHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Slip",
			GameEngineRenderingEvent(PlayerName_[i] + "_Slip.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Stand",
			GameEngineRenderingEvent(PlayerName_[i] + "_Stand.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Throw",
			GameEngineRenderingEvent(PlayerName_[i] + "_Throw.FBX", 0.035f, true));

		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonEnterHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonEnterHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonEnterIdle",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonEnterIdle.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonFireHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonFireHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonFireIdle",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonFireIdle.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonFlyingHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonFlyingHolding.FBX", 0.035f, false));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonFlyingIdle",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonFlyingIdle.FBX", 0.035f, false));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonIdleIdle",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonIdleIdle.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonIdleHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonIdleHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonLandingHolding",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonLandingHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "CannonLandingIdle",
			GameEngineRenderingEvent(PlayerName_[i] + "_CannonLandingIdle.FBX", 0.035f, true));


		PlayerIdleRenderer_[i]->ChangeAnimation(PlayerName_[i] + "Idle");
		PlayerIdleRenderer_[i]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[i]->GetTransform().SetLocalScale({ 100,100,100 });

		PlayerWalkRenderer_[i] = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerWalkRenderer_[i]->SetFBXMesh(PlayerName_[i] + "_Walk.FBX", "TextureAnimation");
		PlayerWalkRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Walk",
			GameEngineRenderingEvent(PlayerName_[i] + "_Walk.FBX", 0.035f, true)); // Idle 호환 x
		PlayerWalkRenderer_[i]->ChangeAnimation(PlayerName_[i] + "Walk");
		PlayerWalkRenderer_[i]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerWalkRenderer_[i]->GetTransform().SetLocalScale({ 100,100,100 });


		PlayerWashRenderer_[i] = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerWashRenderer_[i]->SetFBXMesh(PlayerName_[i] + "_Wash.FBX", "TextureAnimation");
		PlayerWashRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Wash",
			GameEngineRenderingEvent(PlayerName_[i] + "_Wash.FBX", 0.035f, true)); // Idle 호환 x
		PlayerWashRenderer_[i]->ChangeAnimation(PlayerName_[i] + "Wash");
		PlayerWashRenderer_[i]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerWashRenderer_[i]->GetTransform().SetLocalScale({ 100,100,100 });
		PlayerWashRenderer_[i]->Off();

		PlayerChopRenderer_[i] = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerChopRenderer_[i]->SetFBXMesh(PlayerName_[i] + "_Chop.FBX", "TextureAnimation");
		PlayerChopRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Chop",
			GameEngineRenderingEvent(PlayerName_[i] + "_Chop.FBX", 0.02f, true)); // Idle 호환 x
		PlayerChopRenderer_[i]->ChangeAnimation(PlayerName_[i] + "Chop");
		PlayerChopRenderer_[i]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerChopRenderer_[i]->GetTransform().SetLocalScale({ 100,100,100 });

		PlayerIdleRenderer_[i]->Off();
		PlayerWalkRenderer_[i]->Off();
		PlayerWashRenderer_[i]->Off();
		PlayerChopRenderer_[i]->Off();






	}

	{
		PlayerCollision_ = CreateComponent<GameEngineCollision>();
		PlayerCollision_->GetTransform().SetLocalScale({ 100,100,100 });
		PlayerCollision_->GetTransform().SetLocalPosition({ 0,-20,0 });
		PlayerCollision_->ChangeOrder(CollisionOrder::Object_Character);
		SetCollision(PlayerCollision_);

		PlayerFloorCollision_ = CreateComponent<GameEngineCollision>();
		PlayerFloorCollision_->GetTransform().SetLocalScale({ 100,15,100 });
		PlayerFloorCollision_->GetTransform().SetLocalPosition({ 0,-20,0 });
		PlayerFloorCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		SetGravityCollision(PlayerFloorCollision_);
	}
	{
		PlayerForwardCollision_ = CreateComponent<GameEngineCollision>();
		PlayerForwardCollision_->GetTransform().SetLocalScale({ 55,100,10 });
		PlayerForwardCollision_->GetTransform().SetLocalPosition({ 0,0,-50 });
		PlayerForwardCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		PlayerForwardCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}
	{
		PlayerForwardLeftCollision_ = CreateComponent<GameEngineCollision>();
		PlayerForwardLeftCollision_->GetTransform().SetLocalScale({ 20,100,10 });
		PlayerForwardLeftCollision_->GetTransform().SetLocalPosition({ 70,0,-50 });
		PlayerForwardLeftCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		PlayerForwardLeftCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}
	{
		PlayerForwardRightCollision_ = CreateComponent<GameEngineCollision>();
		PlayerForwardRightCollision_->GetTransform().SetLocalScale({ 20,100,10 });
		PlayerForwardRightCollision_->GetTransform().SetLocalPosition({ -70,0,-50 });
		PlayerForwardRightCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		PlayerForwardRightCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}

	{
		PlayerRightCollision_ = CreateComponent<GameEngineCollision>();
		PlayerRightCollision_->GetTransform().SetLocalScale({ 10,100,100 });
		PlayerRightCollision_->GetTransform().SetLocalPosition({ -60,0,0 });
		PlayerRightCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		PlayerRightCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });

		PlayerLeftCollision_ = CreateComponent<GameEngineCollision>();
		PlayerLeftCollision_->GetTransform().SetLocalScale({ 10,100,100 });
		PlayerLeftCollision_->GetTransform().SetLocalPosition({ 60,0,0 });
		PlayerLeftCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		PlayerLeftCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });

		PlayerBackCollision_ = CreateComponent<GameEngineCollision>();
		PlayerBackCollision_->GetTransform().SetLocalScale({ 55,100,10 });
		PlayerBackCollision_->GetTransform().SetLocalPosition({ 0,0,60 });
		PlayerBackCollision_->ChangeOrder(CollisionOrder::Object_CharacterColCheck);
		PlayerBackCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}

	SetLeftCollision(PlayerLeftCollision_);
	SetRightCollision(PlayerRightCollision_);
	SetForwardCollision(PlayerForwardCollision_);
	SetBackCollision(PlayerBackCollision_);

	Collision_Interact_ = CreateComponent<GameEngineCollision>("PlayerCollision");
	Collision_Interact_->ChangeOrder(CollisionOrder::Object_Character_Interact);
	Collision_Interact_->GetTransform().SetLocalScale({ 50,100,200});
	Collision_Interact_->GetTransform().SetLocalPosition({ 0,0,-60 });

	PlayerCameraCollision_ = CreateComponent<GameEngineCollision>();
	PlayerCameraCollision_->ChangeOrder(CollisionOrder::Max);
	PlayerCameraCollision_->GetTransform().SetLocalScale({ 200,200,200 });
	PlayerCameraCollision_->GetTransform().SetLocalPosition({ 0,0,0 });

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
	StateManager.CreateStateMember("HoldUp"
		, std::bind(&Player::HoldUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::HoldUpStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("HoldDown"
		, std::bind(&Player::HoldDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::HoldDownStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Slice"
		, std::bind(&Player::SliceUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SliceStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("DishWash"
		, std::bind(&Player::DishWashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DishWashStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("FireOff"
		, std::bind(&Player::FireOffUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::FireOffStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("CannonInter"
		, std::bind(&Player::CannonInterUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::CannonInterStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("CannonFly"
		, std::bind(&Player::CannonFlyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::CannonFlyStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Drowning"
		, std::bind(&Player::DrowningUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DrowningStart, this, std::placeholders::_1)
	);
	StateManager.ChangeState("Idle");
	ChangePlayerColor();



}
void Player::IdleRendererON()
{
	PlayerIdleRenderer_[PlayerCustomNum]->On();
	PlayerWalkRenderer_[PlayerCustomNum]->Off();
	PlayerChopRenderer_[PlayerCustomNum]->Off();
	PlayerWashRenderer_[PlayerCustomNum]->Off();
}
void Player::WalkRendererON()
{
	PlayerIdleRenderer_[PlayerCustomNum]->Off();
	PlayerWalkRenderer_[PlayerCustomNum]->On();
	PlayerChopRenderer_[PlayerCustomNum]->Off();
	PlayerWashRenderer_[PlayerCustomNum]->Off();
}
void Player::ChopRendererON()
{
	PlayerIdleRenderer_[PlayerCustomNum]->Off();
	PlayerWalkRenderer_[PlayerCustomNum]->Off();
	PlayerChopRenderer_[PlayerCustomNum]->On();
	PlayerWashRenderer_[PlayerCustomNum]->Off();
}
void Player::WashRendererON()
{
	PlayerIdleRenderer_[PlayerCustomNum]->Off();
	PlayerWalkRenderer_[PlayerCustomNum]->Off();
	PlayerChopRenderer_[PlayerCustomNum]->Off();
	PlayerWashRenderer_[PlayerCustomNum]->On();
}
void Player::ChangePlayer()
{
	PlayerIdleRenderer_[PlayerCustomNum]->Off();
	PlayerWalkRenderer_[PlayerCustomNum]->Off();
	PlayerChopRenderer_[PlayerCustomNum]->Off();
	PlayerWashRenderer_[PlayerCustomNum]->Off();

	PlayerCustomNum += 1;
	if (PlayerCustomNum == 6)
	{
		PlayerCustomNum = 0;
	}

	PlayerIdleRenderer_[PlayerCustomNum]->On();
	PlayerWalkRenderer_[PlayerCustomNum]->Off();
	PlayerChopRenderer_[PlayerCustomNum]->Off();
	PlayerWashRenderer_[PlayerCustomNum]->Off();

	ChangePlayerColor();

}
void Player::ChangePlayerColor() // 플레이어 팀 색 바꾸는 함수
{
	PixelData& IdleRender = PlayerIdleRenderer_[PlayerCustomNum]->GetPixelDatas(0);
	IdleRender.AlphaFlag = 1;
	IdleRender.AlphaColor.a = 1.0f;

	PixelData& WalkRender = PlayerWalkRenderer_[PlayerCustomNum]->GetPixelDatas(0);
	WalkRender.AlphaFlag = 1;
	WalkRender.AlphaColor.a = 1.0f;

	PixelData& ChopRender = PlayerChopRenderer_[PlayerCustomNum]->GetPixelDatas(0);
	ChopRender.AlphaFlag = 1;
	ChopRender.AlphaColor.a = 1.0f;

	PixelData& WashRender = PlayerWashRenderer_[PlayerCustomNum]->GetPixelDatas(0);
	WashRender.AlphaFlag = 1;
	WashRender.AlphaColor.a = 1.0f;

	if (PlayerPNum == 1)
	{
		IdleRender.AlphaColor.r = 1.0f;
		IdleRender.AlphaColor.g = 0.0f;
		IdleRender.AlphaColor.b = 0.0f;

		WalkRender.AlphaColor.r = 1.0f;
		WalkRender.AlphaColor.g = 0.0f;
		WalkRender.AlphaColor.b = 0.0f;

		ChopRender.AlphaColor.r = 1.0f;
		ChopRender.AlphaColor.g = 0.0f;
		ChopRender.AlphaColor.b = 0.0f;

		WashRender.AlphaColor.r = 1.0f;
		WashRender.AlphaColor.g = 0.0f;
		WashRender.AlphaColor.b = 0.0f;

	}


	else if (PlayerPNum == 2)
	{
		IdleRender.AlphaColor.r = 0.0f;
		IdleRender.AlphaColor.g = 0.0f;
		IdleRender.AlphaColor.b = 1.0f;

		WalkRender.AlphaColor.r = 0.0f;
		WalkRender.AlphaColor.g = 0.0f;
		WalkRender.AlphaColor.b = 1.0f;

		ChopRender.AlphaColor.r = 0.0f;
		ChopRender.AlphaColor.g = 0.0f;
		ChopRender.AlphaColor.b = 1.0f;

		WashRender.AlphaColor.r = 0.0f;
		WashRender.AlphaColor.g = 0.0f;
		WashRender.AlphaColor.b = 1.0f;

	}

	else if (PlayerPNum == 3)
	{
		IdleRender.AlphaColor.r = 0.0f;
		IdleRender.AlphaColor.g = 1.0f;
		IdleRender.AlphaColor.b = 0.0f;

		WalkRender.AlphaColor.r = 0.0f;
		WalkRender.AlphaColor.g = 1.0f;
		WalkRender.AlphaColor.b = 0.0f;

		ChopRender.AlphaColor.r = 0.0f;
		ChopRender.AlphaColor.g = 1.0f;
		ChopRender.AlphaColor.b = 0.0f;

		WashRender.AlphaColor.r = 0.0f;
		WashRender.AlphaColor.g = 1.0f;
		WashRender.AlphaColor.b = 0.0f;

	}

	else if (PlayerPNum == 4)
	{
		IdleRender.AlphaColor.r = 1.0f;
		IdleRender.AlphaColor.g = 1.0f;
		IdleRender.AlphaColor.b = 0.0f;

		WalkRender.AlphaColor.r = 1.0f;
		WalkRender.AlphaColor.g = 1.0f;
		WalkRender.AlphaColor.b = 0.0f;

		ChopRender.AlphaColor.r = 1.0f;
		ChopRender.AlphaColor.g = 1.0f;
		ChopRender.AlphaColor.b = 0.0f;

		WashRender.AlphaColor.r = 1.0f;
		WashRender.AlphaColor.g = 1.0f;
		WashRender.AlphaColor.b = 0.0f;

	}
}


void Player::CustomKeyCheck()
{
	if (true == GameEngineInput::GetInst()->IsDownKey("ChangePlayerCustom" + PNumString))
	{
		ChangePlayer();
	}
	if (true == GameEngineInput::GetInst()->IsDownKey("ChangePlayerNum" + PNumString))
	{
		PlayerPNum += 1;
		if (PlayerPNum == 5)
		{
			PlayerPNum = 1;
		}
		ChangePlayerColor();
	}
}

void  Player::LevelStartEvent()
{
	for (int i = 0; i < 6; i++)
	{
		if (PlayerIdleRenderer_[i] != nullptr)
		{
			PlayerIdleRenderer_[i]->ChangeLoadMaterial();

		}
	}
	}


void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("IsSingleMode"))
	{
		IsSingleMode = true;
	}
	

	if (PlayerCameraCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::DeadZone, CollisionType::CT_OBB) == true)
	{
		if (StateManager.GetCurStateStateName() != "Drowning")
		{
			StateManager.ChangeState("Drowning");
		}
	}
	if (IsSingleMode == true)
	{
		std::shared_ptr<Player> MainPlayer2 = GetLevel()->CreateActor<Player>();
		MainPlayer2->GetTransform().SetWorldPosition({ -900.00, 90.0, -1111.00 });
		MainPlayer2->PlayerPNum = 2;

		IsSingleMode = false;
	}


	StateManager.Update(_DeltaTime);
	PNumSgtringUpdate();
	CustomKeyCheck();
	LiftFloorCheck();

	if (IsPotal_ != true)
	{
		DashCheck(_DeltaTime);
		
		if (IsLift() == false)
		{
			Gravity();
		}
		else if (IsLift() == true)
		{
			GetTransform().SetLocalPosition(
				float4
				{
					GetTransform().GetWorldPosition().x,
					GetCurLift()->GetTransform().GetWorldPosition().y+10,
					GetTransform().GetWorldPosition().z,
				}
			);
		}
	}

	CameraMove(_DeltaTime);
}

void Player::CameraMove(float _DeltaTime)
{
	if (PlayerCameraCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
	{
		if (IsCameraMove_ == false)
		{
			if (CameraUpTime_ <= 0.0f && CameraDownTime_ <= 0.0f)
			{
				CameraUpTime_ = 1.0f;
				IsCameraMove_ = true;
			}
		}
		
	}
	else
	{
		if (IsCameraMove_ == true)
		{
			if (CameraDownTime_ <= 0.0f && CameraUpTime_ <= 0.0f)
			{
				CameraDownTime_ = 1.0f;
				IsCameraMove_ = false;
			}
		}
	}

	if (CameraDownTime_ > 0.0f)
	{
		CameraDownTime_ -= 1.0f * _DeltaTime;
		GetLevel()->GetMainCameraActorTransform().SetWorldMove(float4{ 0,-20.0f* _DeltaTime,0 });
	}

	else if (CameraUpTime_ > 0.0f)
	{
		CameraUpTime_ -= 1.0f * _DeltaTime;
		GetLevel()->GetMainCameraActorTransform().SetWorldMove(float4{ 0,20.0f * _DeltaTime,0 });
	}

}

void Player::PNumSgtringUpdate()
{
	if (PlayerPNum == 1)
	{
		PNumString = "";
	}
	else if (PlayerPNum == 2)
	{
		PNumString = "2";
	}
	else if (PlayerPNum == 3)
	{
		PNumString = "3";
	}
	else if (PlayerPNum == 4)
	{
		PNumString = "4";
	}
}


bool Player::MoveAngle()
{

	if (CurAngle_ > 360)
	{
		CurAngle_ = 0;
	}
	if (CurAngle_ < 0)
	{
		CurAngle_ = 359;
	}

	if (CurDir_ == PlayerDir::Front)
	{
		if (CurAngle_ > 0 && CurAngle_ < 180)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 0)
			{
				CurAngle_ = 0;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 180)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ >= 360)
			{
				CurAngle_ = 0;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 0;
			return true;
		}

	}

	if (CurDir_ == PlayerDir::Right)
	{
		if (CurAngle_ > 90 && CurAngle_ < 270)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 90)
			{
				CurAngle_ = 90;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 270 || CurAngle_ < 90)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ <270 &&CurAngle_ > 90)
			{
				CurAngle_ = 90;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 90;
			return true;
		}
	}
	if (CurDir_ == PlayerDir::Left)
	{
		if (CurAngle_ > 270 || CurAngle_ < 90)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 90 &&CurAngle_ < 270)
			{
				CurAngle_ = 270;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 90 && CurAngle_ < 270)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 270)
			{
				CurAngle_ = 270;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 270;
			return true;
		}
	}
	if (CurDir_ == PlayerDir::Back)
	{
		if (CurAngle_ > 180 && CurAngle_ <= 360)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 180)
			{
				CurAngle_ = 180;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 0 && CurAngle_ < 180)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 180)
			{
				CurAngle_ = 180;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 180;
			return true;
		}

	}

	if (CurDir_ == PlayerDir::FrontRight)
	{
		if (CurAngle_ < 45 || CurAngle_ >= 225)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 225 && CurAngle_ > 45)
			{
				CurAngle_ = 45;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 225 && CurAngle_ > 45)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 45)
			{
				CurAngle_ = 45;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 45;
			return true;
		}
	}

	if (CurDir_ == PlayerDir::FrontLeft)
	{
		if (CurAngle_ < 315 && CurAngle_ >= 135)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 315)
			{
				CurAngle_ = 315;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 135 || CurAngle_ > 315)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 135 && CurAngle_ < 315)
			{
				CurAngle_ = 315;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 315;
			return true;
		}
	}
	if (CurDir_ == PlayerDir::BackRight)
	{
		if (CurAngle_ < 135 || CurAngle_ >= 315)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 0 && CurAngle_ > 135)
			{
				CurAngle_ = 135;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 315 && CurAngle_ > 135)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 135)
			{
				CurAngle_ = 135;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 135;
			return true;
		}
	}
	if (CurDir_ == PlayerDir::BackLeft)
	{
		if (CurAngle_ < 225 && CurAngle_ >= 45)
		{
			CurAngle_ += 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 0 && CurAngle_ > 225)
			{
				CurAngle_ = 225;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 45 || CurAngle_ > 225)
		{
			CurAngle_ -= 1200.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 225)
			{
				CurAngle_ = 225;
				return true;
			}
			return false;
		}
		else
		{
			CurAngle_ = 225;
			return true;
		}
	}
}
bool Player::PlayerMoveCollisionCheck(std::shared_ptr<GameEngineCollision> _Col)
{
	if (_Col->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
		_Col->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Cannon, CollisionType::CT_OBB) == false &&
		_Col->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Sink, CollisionType::CT_OBB) == false &&
		_Col->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Button, CollisionType::CT_OBB) == false &&
		_Col->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false)
	{
		return true;
	}
	else
	{
		false;
	}
}

void Player::DashCheck(float _DeltaTime)
{
	if (StateManager.GetCurStateStateName() == "CannonIdle")
	{
		return;
	}
	DashTime_ -= 1.0f * _DeltaTime;
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerDash" + PNumString))
	{
		if (DashTime_ < 0.0f)
		{
			DashTime_ = 0.3f;
			Speed_ = 1200.0;
		}
	}

	if (DashTime_ > 0.0f)
	{
		if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString) &&
			false == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString) &&
			false == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString) &&
			false == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
		{
			if (PlayerMoveCollisionCheck(PlayerForwardCollision_)==true)
			{
				if (StateManager.GetCurStateStateName() == "HoldUp")
				{
					PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "WalkHolding");
					PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
					PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
				}
				if (StateManager.GetCurStateStateName() == "Idle")
				{
					WalkRendererON();
				}
				GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
			}
		}
	}
	else
	{
		if (StateManager.GetCurStateStateName() == "Idle")
		{
			IdleRendererON();
			PlayerIdleRenderer_[PlayerCustomNum]->ChangeAnimation(PlayerName_[PlayerCustomNum] + "Idle");
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalRotation({ 90,180,0 });
			PlayerIdleRenderer_[PlayerCustomNum]->GetTransform().SetLocalScale({ 100,100,100 });
		}
		Speed_ = 650.0f;
	}

}

void Player::PlayerDirCheck() // 플레이어 방향 체크하고 회전시키는 함수
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString))
	{
		CurDir_ = PlayerDir::Front;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString))
		{
			CurDir_ = PlayerDir::FrontLeft;

		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString))
		{
			CurDir_ = PlayerDir::FrontRight;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
	{
		CurDir_ = PlayerDir::Back;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString))
		{
			CurDir_ = PlayerDir::BackLeft;
		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString))
		{
			CurDir_ = PlayerDir::BackRight;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft" + PNumString))
	{
		CurDir_ = PlayerDir::Left;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString))
		{
			CurDir_ = PlayerDir::FrontLeft;
		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
		{
			CurDir_ = PlayerDir::BackLeft;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight" + PNumString))
	{

		CurDir_ = PlayerDir::Right;
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront" + PNumString))
		{
			CurDir_ = PlayerDir::FrontRight;
		}
		if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack" + PNumString))
		{
			CurDir_ = PlayerDir::BackRight;
		}

	}

	GetTransform().SetLocalRotation({ 0,CurAngle_, 0 });
}


void Player::MoveCollisionSideCheck(float _DeltaTime)
{
	if (CurDir_ == PlayerDir::FrontRight)
	{
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{

			if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ -Speed_ * 0.8f * _DeltaTime ,0,0 });
			}
			else if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ 0,0,-Speed_ * 0.8f * _DeltaTime });
			}
			return;
		}





	}

	else if (CurDir_ == PlayerDir::FrontLeft)
	{
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ Speed_ * 0.8f * _DeltaTime ,0,0 });
			}
			else if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ 0,0,-Speed_ * 0.8f * _DeltaTime });
			}

			return;
		}
		\


	}

	else if (CurDir_ == PlayerDir::BackLeft)
	{
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{

			if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ Speed_ * 0.8f * _DeltaTime ,0,0 });
			}
			else if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ 0,0,Speed_ * 0.8f * _DeltaTime });
			}
			return;
		}



	}

	else if (CurDir_ == PlayerDir::BackRight)
	{
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ -Speed_ * 0.8f * _DeltaTime ,0,0 });
			}

			else if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB)== true)
				{
					return;
				}
				GetTransform().SetLocalMove({ 0,0,Speed_ * 0.8f * _DeltaTime });
			}

			return;
		}

	}
}

void Player::DetachPlayerHoldingToGround() // 플레이어 손에든 함수 바닥에 떨어뜨리는 함수
{
	if (CurrentHoldingObject_ != nullptr)
	{
		CurrentHoldingObject_->CastThis<GamePlayObject>()->SetPlayerState(std::dynamic_pointer_cast<Player>(shared_from_this()), CurStateType_);
		CurrentHoldingObject_->CastThis<GamePlayObject>()->GetCollisionObject()->On();
		CurrentHoldingObject_->GetTransform().SetLocalPosition(float4{ 0,0,0 });
		CurrentHoldingObject_->GetTransform().SetWorldPosition(GetTransform().GetLocalPosition() + GetTransform().GetBackVector() * 60.0f);
		CurrentHoldingObject_->DetachObject();
		CurrentHoldingObject_ = nullptr;
	}

}
//////////////////////충돌 함수




CollisionReturn Player::TableHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//테이블에게 알려주기
	if (CurrentHoldingObject_ != nullptr)
	{
		return CollisionReturn::ContinueCheck;
	}

	IdleRendererON();

	if (SetPlayerState_Return::Nothing ==
		_Other->GetParent()->CastThis<GamePlayStaticObject>()->SetPlayerState(std::dynamic_pointer_cast<Player>(shared_from_this()), CurStateType_))
	{
		StateManager.ChangeState("Idle");
	}

	return CollisionReturn::ContinueCheck;
}
CollisionReturn Player::GroundHoldUpCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{ //바닥에 있는 오브젝트 집기
	if (CurrentHoldingObject_ != nullptr)
	{
		return CollisionReturn::ContinueCheck;
	}

	SetPlayerHolding(_Other->GetActor());
	IdleRendererON();

	return CollisionReturn::ContinueCheck;
}

CollisionReturn Player::TableHoldDownCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{ // 테이블에게 내려놓는다고 알려주기
	if (CurrentHoldingObject_ == nullptr)
	{
		return CollisionReturn::ContinueCheck;
	}
	if (SetPlayerState_Return::Nothing ==
		_Other->GetParent()->CastThis<GamePlayStaticObject>()->SetPlayerState(std::dynamic_pointer_cast<Player>(shared_from_this()), CurStateType_))
	{  //테이블에 물체가 있어 못내려놓으면 그냥 아무일도 일어나지 않게 하기

		StateManager.ChangeState("HoldUp");
	}
	else
	{
		if (CurrentHoldingObject_ == nullptr)
		{
			return CollisionReturn::ContinueCheck;
		}
		CurrentHoldingObject_->CastThis<GamePlayObject>()->SetPlayerState(std::dynamic_pointer_cast<Player>(shared_from_this()), CurStateType_);
	}
	return CollisionReturn::ContinueCheck;
}


CollisionReturn Player::TableSliceCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//테이블에게 자를거라고 알려주기, 손에 아무것도 없는 Idle상태에서만 진입할 수 있음

	CurStateType_ = PlayerCurStateType::Slice;
	if (SetPlayerState_Return::Using ==
		_Other->GetParent()->CastThis<GamePlayStaticObject>()->SetPlayerState(std::dynamic_pointer_cast<Player>(shared_from_this()), CurStateType_))
	{  
		//자를수 있으면 자르는 상태로 변경
		TableCollision_ = _Other;
		StateManager.ChangeState("Slice");
	}
	return CollisionReturn::ContinueCheck;
}

CollisionReturn Player::TableSinkCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	CurStateType_ = PlayerCurStateType::DishWash;
	if (SetPlayerState_Return::Using ==
		_Other->GetParent()->CastThis<GamePlayStaticObject>()->SetPlayerState(std::dynamic_pointer_cast<Player>(shared_from_this()), CurStateType_))
	{
		TableCollision_ = _Other;
		StateManager.ChangeState("DishWash");
	}

	return CollisionReturn::ContinueCheck;
}

CollisionReturn Player::InteractTableCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (_Other != TableCollision_)
	{
		IsSlice_ = false;
		StateManager.ChangeState("Idle");
	}

	return CollisionReturn::ContinueCheck;
}



CollisionReturn Player::EnterCannon(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//SetParent(_Other->GetParent());
	_Other->GetParent()->CastThis<Cannon>()->SetPlayer(shared_from_this()->CastThis<Player>());
	IsCannon_ = true;
	GetTransform().SetWorldPosition({ -636.00, 90.0, -1111.00 });
	GetTransform().SetWorldRotation({270, 0, 90 });
	IsPotal_ = true;
	return CollisionReturn::ContinueCheck;
}

CollisionReturn Player::PushButton(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	_Other->GetParent()->CastThis<Button>()->SetButtonPressed();
	return CollisionReturn::ContinueCheck;
}