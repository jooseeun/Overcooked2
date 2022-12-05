#include "PreCompile.h"
#include "ServerTestPlayer.h"
#include "ServerTestLevel.h"
#include "GamePacket.h"

bool ServerTestPlayer::OnePlayerInit = false;

ServerTestPlayer* ServerTestPlayer::MainPlayer = nullptr;

ServerTestPlayer::ServerTestPlayer()
	: Speed(50.0f)
	, Renderer_(nullptr)
	, IsPlayerble(false)
{
	MainPlayer = this;
}

ServerTestPlayer::~ServerTestPlayer()
{
}

void ServerTestPlayer::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	if (false == OnePlayerInit)
	{
		IsPlayerble = true;

		StateManager.CreateStateMember("Idle"
			, std::bind(&ServerTestPlayer::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&ServerTestPlayer::IdleStart, this, std::placeholders::_1)
		);

		StateManager.CreateStateMember("Move"
			, std::bind(&ServerTestPlayer::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, [/*&*/=](const StateInfo& _Info)
		{
		});

		StateManager.ChangeState("Idle");

		OnePlayerInit = true;
	}

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetWorldScale({100, 100, 100});
	Renderer_->GetTransform().SetWorldPosition({0, 0, 0});
}

void ServerTestPlayer::IdleStart(const StateInfo& _Info)
{
}

void ServerTestPlayer::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerFront") ||
		true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		StateManager.ChangeState("Move");
	}
}

void ServerTestPlayer::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressKey("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerFront") &&
		false == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}
}

CollisionReturn ServerTestPlayer::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn::Break;
}

void ServerTestPlayer::Update(float _DeltaTime)
{
	if (false == GetIsNetInit())
	{
		return;
	}

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	if (true == IsPlayerble)
	{

		StateManager.Update(_DeltaTime);

		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::Player;
		Packet->State = ServerObjectBaseState::Base;
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Rot = GetTransform().GetWorldRotation();
		ServerTestLevel::Net->SendPacket(Packet);
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
			GetTransform().SetWorldRotation(ObjectUpdate->Rot);
			break;
		}
		case ContentsPacketType::ClinetInit:
		default:
			MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
			break;
		}
	}
}