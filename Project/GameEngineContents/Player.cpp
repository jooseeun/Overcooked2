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
	, PlayerIdleRenderer_(nullptr)
	, PlayerWalkRenderer_(nullptr)
	, PlayerChopRenderer_(nullptr)
	, PlayerWashRenderer_(nullptr)
	, StateManager()
	, CurrentHoldingObject_(nullptr)
	, Collision_Interact_(nullptr)
	, Interact_GroundObject_(nullptr)
	, Interact_TableObject_(nullptr)
	, CurKineticEnergy_(0)
	, FireOff_(false)
	, PlayerName_("AlienGreen")
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
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerFront", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PlayerDash", 'X');
		GameEngineInput::GetInst()->CreateKey("PlayerHold", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("PlayerInteract", VK_CONTROL);

		//GameEngineInput::GetInst()->CreateKey("PlayerSlice", VK_CONTROL);
	}


	//GameEngineFBXMesh* TestMesh = GameEngineFBXMesh::Find("Chef.FBX");

	//std::string NewPath = "C:Users\\MOA\\Overcooked2\\Project\\ContentsResources\\Mesh\\Chef1\\t_chef_head_alien_green_d.png";
	//size_t idx = NewPath.rfind("\\");

	//std::string TestStr = NewPath.substr(0, idx);

	//TestMesh->GetFbxRenderUnit()[0].MaterialData[0].DifTexturePath = NewPath;
	//TestMesh->GetFbxRenderUnit()[0].MaterialData[0].DifTextureName = "t_chef_head_alien_green_d.png";



	//임시 Player StaticRenderer
	//{
	//	PlayerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	//	PlayerRenderer_->SetFBXMesh("Chef1.FBX", "Texture");
	//	
	//}


	//AlienGreen
	{
		PlayerIdleRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerIdleRenderer_->SetFBXMesh("AlienGreen_Idle.FBX", "TextureAnimation");

		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenIdle", 
			GameEngineRenderingEvent("AlienGreen_Idle.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenIdle2", 
			GameEngineRenderingEvent("AlienGreen_Idle2.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenWalkHolding", 
			GameEngineRenderingEvent("AlienGreen_WalkHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenCarDeath", 
			GameEngineRenderingEvent("AlienGreen_CarDeath.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenDeath", 
			GameEngineRenderingEvent("AlienGreen_Death.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenDrowning", 
			GameEngineRenderingEvent("AlienGreen_Drowning.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenFall", 
			GameEngineRenderingEvent("AlienGreen_Fall.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenIdleHolding", 
			GameEngineRenderingEvent("AlienGreen_IdleHolding.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenSlip", 
			GameEngineRenderingEvent("AlienGreen_Slip.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenStand", 
			GameEngineRenderingEvent("AlienGreen_Stand.FBX", 0.035f, true));
		PlayerIdleRenderer_->CreateFBXAnimation("AlienGreenThrow", 
			GameEngineRenderingEvent("AlienGreen_Throw.FBX", 0.035f, true));


		PlayerIdleRenderer_->ChangeAnimation("AlienGreenIdle");
		PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 0,180,0 });
		PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100,100,100 });

		PlayerWalkRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerWalkRenderer_->SetFBXMesh("AlienGreen_Walk.FBX", "TextureAnimation");
		PlayerWalkRenderer_->CreateFBXAnimation("AlienGreenWalk", 
			GameEngineRenderingEvent("AlienGreen_Walk.FBX", 0.035f, true)); // Idle 호환 x
		PlayerWalkRenderer_->ChangeAnimation("AlienGreenWalk");
		PlayerWalkRenderer_->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerWalkRenderer_->GetTransform().SetLocalScale({ 100,100,100 });


		PlayerWashRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerWashRenderer_->SetFBXMesh("AlienGreen_Wash.FBX", "TextureAnimation");
		PlayerWashRenderer_->CreateFBXAnimation("AlienGreenWash", 
			GameEngineRenderingEvent("AlienGreen_Wash.FBX", 0.035f, true)); // Idle 호환 x
		PlayerWashRenderer_->ChangeAnimation("AlienGreenWash");
		PlayerWashRenderer_->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerWashRenderer_->GetTransform().SetLocalScale({ 100,100,100 });
		PlayerWashRenderer_->Off();

		PlayerChopRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerChopRenderer_->SetFBXMesh("AlienGreen_Chop.FBX", "TextureAnimation");
		PlayerChopRenderer_->CreateFBXAnimation("AlienGreenChop", 
			GameEngineRenderingEvent("AlienGreen_Chop.FBX",  0.04f, true)); // Idle 호환 x
		PlayerChopRenderer_->ChangeAnimation("AlienGreenChop");
		PlayerChopRenderer_->GetTransform().SetLocalRotation({ 90,180,0 });
		PlayerChopRenderer_->GetTransform().SetLocalScale({ 100,100,100 });

		PlayerIdleRenderer_->Off();
		PlayerWalkRenderer_->Off();
		PlayerWashRenderer_->Off();
		PlayerChopRenderer_->Off();

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
	PlayerIdleRenderer_->On();
	PlayerWalkRenderer_->Off();
	PlayerChopRenderer_->Off();
	PlayerWashRenderer_->Off();
}
void Player::WalkRendererON()
{
	PlayerIdleRenderer_->Off();
	PlayerWalkRenderer_->On();
	PlayerChopRenderer_->Off();
	PlayerWashRenderer_->Off();
}
void Player::ChopRendererON()
{
	PlayerIdleRenderer_->Off();
	PlayerWalkRenderer_->Off();
	PlayerChopRenderer_->On();
	PlayerWashRenderer_->Off();
}
void Player::WashRendererON()
{
	PlayerIdleRenderer_->Off();
	PlayerWalkRenderer_->Off();
	PlayerChopRenderer_->Off();
	PlayerWashRenderer_->On();
}

void  Player::LevelStartEvent()
{
	if (PlayerIdleRenderer_ != nullptr)
	{
		PlayerIdleRenderer_->ChangeLoadMaterial();

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

