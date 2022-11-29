#include "PreCompile.h"
#include "ServerTestLevel.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngineStatusWindow.h"


GameEngineNet* ServerTestLevel::Net;
GameEngineNetServer ServerTestLevel::Server;
GameEngineNetClient ServerTestLevel::Client;

ServerTestLevel::ServerTestLevel()
{
}

ServerTestLevel::~ServerTestLevel()
{
}

void ServerTestLevel::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}
}

void ServerTestLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void ServerTestLevel::End()
{
}

void ServerTestLevel::LevelStartEvent()
{
	if (true == GameEngineStatusWindow::IsHost)
	{
		Server.Accept(30001);
		Net = &Server;
	}
	else
	{
		Client.Connect("127.0.0.1", 30001);
		Net = &Client;
	}
}

void ServerTestLevel::LevelEndEvent()
{
}
