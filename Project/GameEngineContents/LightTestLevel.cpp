#include "PreCompile.h"
#include "LightTestLevel.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngineStatusWindow.h"
#include <GameEngineCore/GameEngineLight.h>

#include <GameEngineCore/GameEngineBlur.h>
#include "GamePacket.h"

LightTestLevel::LightTestLevel()
{
}

LightTestLevel::~LightTestLevel()
{
}

void LightTestLevel::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	GameEngineStatusWindow::AddDebugRenderTarget("GBuffer", GetMainCamera()->GetCameraDeferredLightRenderTarget());

	{
		LightObject = CreateActor<GameEngineLight>();
		LightObject->GetTransform().SetWorldRotation({ 0.0f, 45.0f, 0.0f });
		GetMainCamera()->PushLight(LightObject);
		LightObject->GetLightData().DifLightPower = 0.5f;
	}

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	if (false == GameEngineInput::GetInst()->IsKey("LightYRot"))
	{
		GameEngineInput::GetInst()->CreateKey("LightYRot", 'F');
		GameEngineInput::GetInst()->CreateKey("LightPowUp", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("LightPowDown", VK_NUMPAD2);
	}
}

void LightTestLevel::LevelStartEvent()
{
}

void LightTestLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (GameEngineInput::GetInst()->IsPressKey("LightYRot"))
	{
		LightObject->GetTransform().SetAddWorldRotation(float4(0.0f, 1.0f, 0.0f));
	}

	if (GameEngineInput::GetInst()->IsPressKey("LightPowUp"))
	{
		LightObject->GetLightData().SpcPow += _DeltaTime * 10.0f;
	}

	if (GameEngineInput::GetInst()->IsPressKey("LightPowDown"))
	{
		LightObject->GetLightData().SpcPow -= _DeltaTime * 10.0f;
	}
}
