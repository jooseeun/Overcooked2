#include "PreCompile.h"
#include "Cannon.h"
#include "Button.h"
#include "Player.h"
#include "ServerInitManager.h"

Cannon::Cannon()
	: CurState_(CannonState::Max)
	, MaxAngle_(-40.f)
	, ReadyAngle_(-32.f)
	, CurAngle_(0.f)
	, IsCounterReaction_(false)
	, IsMoveDone_(false)
	, ReactCount_(0)
	, IsDownMove_(false)
	, CurPos_(0.f)
	, IsCounterReactionPos_(false)
	, IsSetting_(false)
{
}

Cannon::~Cannon()
{
}

void Cannon::FBXSetting()
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
	Button_->GetTransform().SetWorldMove({ 0.f, 0.f, 122.f });
	Button_->SetParent(shared_from_this());
}

void Cannon::Start()
{
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
	if (false == IsSetting_)
	{
		IsSetting_ = true;
		FBXSetting();
		return;
	}

	if (Player_ != nullptr)
	{
		Player_->CannonZAngle_ = CurAngle_;
	}

	StateManager.Update(_DeltaTime);

	DebugOn();

	ServerUpdate(_DeltaTime);
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

	GameEngineSound::SoundPlayOneShot("DLC_08_Cannon_Enter_01.wav");
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

		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::Cannon;
		Packet->State = ServerObjectBaseState::Base;
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Animation = "Shoot"; 

		if (Player_ == nullptr)
		{
			Packet->RendererState = -1;
		}
		else
		{
			Packet->RendererState = Player_->GetNetID();
		}
		Packet->PlayerMove = -1;
		Packet->PlayerDeath = -1;

		ServerInitManager::Net->SendPacket(Packet);
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

	GameEngineSound::SoundPlayOneShot("DLC_08_Cannon_Fire_01.wav");
	GameEngineSound::SoundPlayOneShot("DLC_08_Cannon_Crowd_03.wav");
}

void Cannon::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.f)
	{
		StateManager.ChangeState("Down");
	}

	if (_Info.StateTime < 0.6f)
	{
		if (false == IsCounterReactionPos_)
		{
			if (CurPos_ <= -20.f)
			{
				IsCounterReactionPos_ = true;
			}
			CurPos_ -= _DeltaTime * 250.f;
			Mesh_Object_->GetTransform().SetLocalPosition({ CurPos_, Mesh_Object_->GetTransform().GetLocalPosition().y, Mesh_Object_->GetTransform().GetLocalPosition().z });
		}
		else
		{
			if (CurPos_ >= 10.f)
			{
				CurPos_ = 20.f;
				IsCounterReactionPos_ = false;
			}
			CurPos_ += _DeltaTime * 250.f;
			Mesh_Object_->GetTransform().SetLocalPosition({ CurPos_, Mesh_Object_->GetTransform().GetLocalPosition().y, Mesh_Object_->GetTransform().GetLocalPosition().z });
		}

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
	IsCounterReactionPos_ = false;
	IsDownMove_ = true;
	ReactCount_ = 1;

	GameEngineSound::SoundPlayOneShot("DLC_08_Cannon_Rotate_Release.wav");
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

void Cannon::ServerUpdate(float _DeltaTime)
{
	if (false == GetIsNetInit() || nullptr == ServerInitManager::Net)
	{
		return;
	}

	if (nullptr != Player_ || ServerInitManager::Net->GetIsHost() == true)
	{
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::Cannon;
		Packet->State = ServerObjectBaseState::Base;
		Packet->Pos = GetTransform().GetWorldPosition();
		//Packet->Rot = GetTransform().GetWorldRotation();
		//Packet->Scale = GetTransform().GetWorldScale();
		Packet->Animation = StateManager.GetCurStateStateName(); // State 이름

		if (Player_ == nullptr)
		{
			Packet->RendererState = -1; // 플레이어 번호
		}
		else
		{
			Packet->RendererState = Player_->GetNetID(); // 플레이어 번호
		}
		Packet->PlayerMove = -1;
		Packet->PlayerDeath = -1;

		ServerInitManager::Net->SendPacket(Packet);
		return;
	}

	while (false == IsPacketEmpty())
	{
		std::shared_ptr<GameServerPacket> Packet = PopPacket();

		ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

		switch (PacketType)
		{
		case ContentsPacketType::ObjectUpdate:
		{
			std::shared_ptr<ObjectUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectUpdatePacket>(Packet);
			GetTransform().SetWorldPosition(ObjectUpdate->Pos);
			//GetTransform().SetWorldRotation(ObjectUpdate->Rot);
			//GetTransform().SetWorldScale(ObjectUpdate->Scale);

			if (StateManager.GetCurStateStateName() != ObjectUpdate->Animation)
			{
				StateManager.ChangeState(ObjectUpdate->Animation);
			}

			if (Player_ == nullptr)
			{
				Player* Object = static_cast<Player*>(GameServerObject::GetServerObject(ObjectUpdate->RendererState));
				if (Object != nullptr)
				{
					SetPlayer(std::dynamic_pointer_cast<Player>(Object->shared_from_this()));
				}
			}

			break;
		}
		}
	}
}