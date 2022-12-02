#include "PreCompile.h"
#include "GameEngineCameraActor.h"
#include <GameEngineBase/GameEngineInput.h>

GameEngineCameraActor::GameEngineCameraActor()
	: CameraComponent(nullptr)
	, RotSpeed(180.0f)
	, Speed(500.0f)
	, FreeCameraMode(false)
{
}

GameEngineCameraActor::~GameEngineCameraActor() 
{
}

void GameEngineCameraActor::Start() 
{
	CameraComponent = CreateComponent<GameEngineCamera>();

	if (false == GameEngineInput::GetInst()->IsKey("CamMoveForward"))
	{
		GameEngineInput::GetInst()->CreateKey("CamMoveForward", 'W');
		GameEngineInput::GetInst()->CreateKey("CamMoveBack", 'S');
		GameEngineInput::GetInst()->CreateKey("CamMoveUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("CamMoveDown", 'E');
		GameEngineInput::GetInst()->CreateKey("CamMoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("CamMoveRight", 'D');

		GameEngineInput::GetInst()->CreateKey("CamMoveBoost", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("CamRot", VK_RBUTTON);
	}
}

void GameEngineCameraActor::Update(float _DeltaTime)
{
	if (false == FreeCameraMode)
	{
		return;
	}

	float MoveSpeed = Speed;

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveBoost"))
	{
		MoveSpeed *= 3.0f;
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveForward"))
	{
		GetTransform().SetWorldForwardMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveBack"))
	{
		GetTransform().SetWorldBackMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveUp"))
	{
		GetTransform().SetWorldUpMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveDown"))
	{
		GetTransform().SetWorldDownMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveLeft"))
	{
		GetTransform().SetWorldLeftMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamMoveRight"))
	{
		GetTransform().SetWorldRightMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPressKey("CamRot"))
	{
		float4 MouseDir = CameraComponent->GetMouseWorldDir();
		float4 RotMouseDir;
		RotMouseDir.x = -MouseDir.y;
		RotMouseDir.y = MouseDir.x;

		GetTransform().SetAddWorldRotation(RotMouseDir * RotSpeed);
	}
}

void GameEngineCameraActor::End() 
{

}


void GameEngineCameraActor::FreeCameraModeOnOff()
{
	FreeCameraMode = !FreeCameraMode;

	if (true == FreeCameraMode)
	{
		PrevMode = CameraComponent->GetProjectionMode();
		CameraComponent->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		OriginTrans.Copy(GetTransform());
	}
	else 
	{
		CameraComponent->SetProjectionMode(PrevMode);
		GetTransform().Copy(OriginTrans);
	}
}