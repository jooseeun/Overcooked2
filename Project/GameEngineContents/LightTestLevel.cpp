#include "PreCompile.h"
#include "LightTestLevel.h"
#include <GameEngineCore/GameEngineLight.h>
#include "GameEngineStatusWindow.h"

LightTestLevel::LightTestLevel()
{
}

LightTestLevel::~LightTestLevel()
{
}

void LightTestLevel::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	LightObject = CreateActor<GameEngineLight>();
	LightObject->GetTransform().SetWorldRotation({ 0.0f, 45.0f, 0.0f });
	GetMainCamera()->PushLight(LightObject);

	GameEngineStatusWindow::AddDebugRenderTarget("GBuffer", GetMainCamera()->GetCameraDeferredGBufferRenderTarget());

	{
		std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
		// Light->GetTransform().SetWorldRotation({0.0f, 90.0f, 0.0f});
		GetMainCamera()->PushLight(Light);
	}

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	if (false == GameEngineInput::GetInst()->IsKey("LightYRot"))
	{
		GameEngineInput::GetInst()->CreateKey("LightYRot", 'F');
	}
}

void LightTestLevel::Update(float _Delat)
{
	if (GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (GameEngineInput::GetInst()->IsPressKey("LightYRot"))
	{
		LightObject->GetTransform().SetAddWorldRotation(float4(0.0f, 1.0f, 0.0f));
	}
}

void LightTestLevel::LevelStartEvent()
{
	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>(OBJECTORDER::Player);
}
