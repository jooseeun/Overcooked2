#include "PreCompile.h"
#include "Player.h"
#include "GamePlayFood.h"
#include "GamePlayStaticObject.h"
#include <math.h>

Player::Player()
	:Speed_(400.0f)
	, CurAngle_(0)
	, CurDir_(PlayerDir::Front)
	, CurHoldType_(PlayerHoldType::CanThrow)
	, PlayerFloorCollision_(nullptr)
	, PlayerLeftCollision_(nullptr)
	, PlayerRightCollision_(nullptr)
	, PlayerForwardCollision_(nullptr)
	, PlayerBackCollision_(nullptr)
	, PlayerCustomNum(5)
	, PlayerIdleRenderer_()
	, PlayerWalkRenderer_()
	, PlayerChopRenderer_()
	, PlayerWashRenderer_()
	, StateManager()
	, CurrentHoldingObject_(nullptr)
	, Collision_Interact_(nullptr)
	, Interact_GroundObject_(nullptr)
	, Interact_TableObject_(nullptr)
	, CurKineticEnergy_(0)
	, FireOff_(false)
	, PlayerName_()
{

}

Player::~Player()
{
}

void Player::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });
	//palyer key
	//이동 - 방향키
	//다지기/던지기 - 왼쪽 CTRL
	//잡기/놓기 - SPACEBAR
	//대쉬 - 왼쪽 ALT
	//감정표현 - E

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


		PlayerIdleRenderer_[i]->ChangeAnimation(PlayerName_[i] + "Idle");
		PlayerIdleRenderer_[i]->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerIdleRenderer_[i]->GetTransform().SetLocalScale({ 100,100,100 });

		PlayerWalkRenderer_[i] = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerWalkRenderer_[i]->SetFBXMesh(PlayerName_[i] + "_Walk.FBX", "TextureAnimation");
		PlayerWalkRenderer_[i]->CreateFBXAnimation(PlayerName_[i] + "Walk",
			GameEngineRenderingEvent(PlayerName_[i] + "_Walk.FBX", 0.03f, true)); // Idle 호환 x
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


		PixelData&  Test = PlayerIdleRenderer_[i]->GetPixelDataList(0);
		Test.AlphaFlag = 1;

		Test.AlphaColor.r = 1.0f;

		Test.AlphaColor.g = 0.0f;
		Test.AlphaColor.b = 0.0f;
		Test.AlphaColor.a = 1.0f;
	}
	//AlienGreen
	{
		

	}

	{
		PlayerFloorCollision_ = CreateComponent<GameEngineCollision>();
		PlayerFloorCollision_->GetTransform().SetLocalScale({ 100,15,100 });
		PlayerFloorCollision_->GetTransform().SetLocalPosition({ 0,-20,0 });
		PlayerFloorCollision_->ChangeOrder(CollisionOrder::Object_Character);
	}
	{
		PlayerForwardCollision_ = CreateComponent<GameEngineCollision>();
		PlayerForwardCollision_->GetTransform().SetLocalScale({ 55,100,10 });
		PlayerForwardCollision_->GetTransform().SetLocalPosition({ 0,0,-50 });
		PlayerForwardCollision_->ChangeOrder(CollisionOrder::Object_Character);
		PlayerForwardCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}
	{
		PlayerForwardLeftCollision_ = CreateComponent<GameEngineCollision>();
		PlayerForwardLeftCollision_->GetTransform().SetLocalScale({ 20,100,10 });
		PlayerForwardLeftCollision_->GetTransform().SetLocalPosition({ 70,0,-50 });
		PlayerForwardLeftCollision_->ChangeOrder(CollisionOrder::Max);
		PlayerForwardLeftCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}
	{
		PlayerForwardRightCollision_ = CreateComponent<GameEngineCollision>();
		PlayerForwardRightCollision_->GetTransform().SetLocalScale({ 20,100,10 });
		PlayerForwardRightCollision_->GetTransform().SetLocalPosition({ -70,0,-50 });
		PlayerForwardRightCollision_->ChangeOrder(CollisionOrder::Max);
		PlayerForwardRightCollision_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
	}
	/*{
		PlayerLeftCollision_ = CreateComponent<GameEngineCollision>();
		PlayerLeftCollision_->GetTransform().SetLocalScale({ 10,100,90 });
		PlayerLeftCollision_->GetTransform().SetLocalPosition({ -50,0,0 });
		PlayerLeftCollision_->ChangeOrder(CollisionOrder::Object_Character);
	}
	{
		PlayerRightCollision_ = CreateComponent<GameEngineCollision>();
		PlayerRightCollision_->GetTransform().SetLocalScale({ 10,100,90 });
		PlayerRightCollision_->GetTransform().SetLocalPosition({ 50,0,0 });
		PlayerRightCollision_->ChangeOrder(CollisionOrder::Object_Character);
	}

	{
		PlayerBackCollision_ = CreateComponent<GameEngineCollision>();
		PlayerBackCollision_->GetTransform().SetLocalScale({ 90,100,10 });
		PlayerBackCollision_->GetTransform().SetLocalPosition({ 0,0,50 });
		PlayerBackCollision_->ChangeOrder(CollisionOrder::Object_Character);
	}*/


	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::Character);
	Collision_Interact_ = CreateComponent<GameEngineCollision>("PlayerCollision");
	Collision_Interact_->GetTransform().SetLocalScale({ 50,100,200});
	Collision_Interact_->GetTransform().SetLocalPosition({ 0,0,-60 });
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_Character);


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
	StateManager.CreateStateMember("DishWash"
		, std::bind(&Player::DishWashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DishWashStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("FireOff"
		, std::bind(&Player::FireOffUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::FireOffStart, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");




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

	StateManager.Update(_DeltaTime);
	Gravity();
	DashCheck();
	Collision_AroundObject();
	CalculateKineticEnergy();
}

///////////////////////////// 그외 함수들


void Player::Gravity()
{
	if(PlayerFloorCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB,
		std::bind(&Player::GravityColCheck, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{
		GetTransform().SetWorldDownMove(300.0f, GameEngineTime::GetDeltaTime());
	}

}

void Player::CalculateKineticEnergy()
{
	CurKineticEnergy_ = 0.5 * Speed_ * sqrt(pow((double)GetTransform().GetLocalScale().x, 2) + 
		pow((double)GetTransform().GetLocalScale().y, 2)+ pow((double)GetTransform().GetLocalScale().z, 2));
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
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 0)
			{
				CurAngle_ = 0;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 180)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 90)
			{
				CurAngle_ = 90;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 270 || CurAngle_ < 90)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 90 &&CurAngle_ < 270)
			{
				CurAngle_ = 270;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 90 && CurAngle_ < 270)
		{
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 180)
			{
				CurAngle_ = 180;
				return true;
			}
			return false;
		}
		else if (CurAngle_ >= 0 && CurAngle_ < 180)
		{
			CurAngle_ = CurAngle_ + 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ < 225 && CurAngle_ > 45)
			{
				CurAngle_ = 45;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 225 && CurAngle_ > 45)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 315)
			{
				CurAngle_ = 315;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 135 || CurAngle_ > 315)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 0 && CurAngle_ > 135)
			{
				CurAngle_ = 135;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 315 && CurAngle_ > 135)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
			CurAngle_ += 500.0f * GameEngineTime::GetDeltaTime();
			if (CurAngle_ > 0 && CurAngle_ > 225)
			{
				CurAngle_ = 225;
				return true;
			}
			return false;
		}
		else if (CurAngle_ < 45 || CurAngle_ > 225)
		{
			CurAngle_ -= 500.0f * GameEngineTime::GetDeltaTime();
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
		Speed_ -= 400.0f * GameEngineTime::GetDeltaTime();
	}
	else
	{
		Speed_ = 400.0f;
	}
}

void Player::PlayerDirCheck() // 플레이어 방향 체크하고 회전시키는 함수
{
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

	GetTransform().SetLocalRotation({ 0,CurAngle_, 0 });
}

void Player::Collision_AroundObject()
{
	if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
		std::bind(&Player::GetCrashGroundObject, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{
		if (Interact_GroundObject_ != nullptr)
		{
			Interact_GroundObject_->SetBloomEffectOff();
		}
		Interact_GroundObject_ = nullptr;
	}
	if (Collision_Interact_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
		std::bind(&Player::GetCrashTableObject, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{
		if (Interact_TableObject_ != nullptr)
		{
			Interact_TableObject_->SetBloomEffectOff();
		}
		Interact_TableObject_ = nullptr;
	}
;
}

void Player::MoveCollisionSideCheck(float _DeltaTime)
{
	if (CurDir_ == PlayerDir::FrontRight)
	{
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{

			if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ -Speed_ * 0.8f * _DeltaTime ,0,0 });
			}
			else if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{
			if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ Speed_ * 0.8f * _DeltaTime ,0,0 });
			}
			else if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{

			if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ Speed_ * 0.8f * _DeltaTime ,0,0 });
			}
			else if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
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
		if (PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
			std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
			PlayerForwardCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
		{
			if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ -Speed_ * 0.8f * _DeltaTime ,0,0 });
			}

			else if (PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
				std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
				PlayerForwardLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
			{
				if (PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB,
					std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true ||
					PlayerForwardRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
						std::bind(&Player::MoveColCheck, this, std::placeholders::_1, std::placeholders::_2)) == true)
				{
					return;
				}
				GetTransform().SetLocalMove({ 0,0,Speed_ * 0.8f * _DeltaTime });
			}

			return;
		}

	}
}

//////////////////////충돌 함수


CollisionReturn Player::GetCrashGroundObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (Interact_GroundObject_ != nullptr)
	{
		Interact_GroundObject_->SetBloomEffectOff();
		//Interact_Possible_StaticObject_ = nullptr;
	}

	Interact_GroundObject_ = _Other->GetActor<GamePlayMoveable>();
	if (Interact_GroundObject_ == nullptr) // 임시코드
	{
		return CollisionReturn::Break;
	}
	Interact_GroundObject_->SetBloomEffectOn();
	return CollisionReturn::Break;
}

CollisionReturn Player::GetCrashTableObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (Interact_TableObject_ != nullptr)
	{
		Interact_TableObject_->SetBloomEffectOff();
		//Interact_Possible_StaticObject_ = nullptr;
	}

	Interact_TableObject_ = _Other->GetActor<GamePlayStaticObject>();
	if (Interact_TableObject_ == nullptr) // 임시코드
	{
		return CollisionReturn::Break;
	}
	Interact_TableObject_->SetBloomEffectOn();
	return CollisionReturn::Break;
}


CollisionReturn Player::GravityColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	return CollisionReturn::ContinueCheck;
}

CollisionReturn Player::MoveColCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	return CollisionReturn::ContinueCheck;
}
// 집는거 안해도되고 앞에 상호작용테이블 검사

