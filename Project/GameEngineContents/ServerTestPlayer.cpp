#include "PreCompile.h"
#include "ServerTestPlayer.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include "ServerTestLevel.h"
#include "GamePacket.h"

#include <iostream>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineBase/GameEngineRandom.h>


bool ServerTestPlayer::OnePlayerInit = false;

ServerTestPlayer* ServerTestPlayer::MainPlayer = nullptr;

ServerTestPlayer::ServerTestPlayer()
	: Renderer(nullptr)
	, IsPlayerble(false)
{
	MainPlayer = this;
}

ServerTestPlayer::~ServerTestPlayer()
{
}


void ServerTestPlayer::Start()
{
	if (false == OnePlayerInit)
	{
		IsPlayerble = true;

		OnePlayerInit = true;
	}

	{
		std::shared_ptr <GameEngineDefaultRenderer> Renderer = CreateComponent<GameEngineDefaultRenderer>();

		Renderer->SetMesh("Box");
		Renderer->SetMaterial("Color");
		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });

		if (true == Renderer->GetRenderUnit()->ShaderResources.IsConstantBuffer("ResultColor"))
		{
			Renderer->GetRenderUnit()->ShaderResources.SetConstantBufferNew("ResultColor", float4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
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

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * -100 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * -100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerFront"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * -100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * -100 * _DeltaTime);
	}

	if (true == IsPlayerble)
	{
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