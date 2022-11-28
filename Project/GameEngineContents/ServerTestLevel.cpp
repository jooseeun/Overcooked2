#include "PreCompile.h"
#include "ServerTestLevel.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngineStatusWindow.h"


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
		Server.Accept(30222);
	}
	else
	{
		// Client.Connect("127.0.0.1", 30222);
		Client.Connect("localHost", 30222);
	}
}

void ServerTestLevel::LevelEndEvent()
{
}
