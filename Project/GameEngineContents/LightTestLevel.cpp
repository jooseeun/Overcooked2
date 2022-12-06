#include "PreCompile.h"
#include "LightTestLevel.h"

LightTestLevel::LightTestLevel()
{
}

LightTestLevel::~LightTestLevel()
{
}

void LightTestLevel::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	std::shared_ptr<GameEngineLight> LightObject = CreateActor<GameEngineLight>();
	GetMainCamera()->PushLight(LightObject);

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}
}

void LightTestLevel::LevelStartEvent()
{
	std::shared_ptr<Player> MainPlayer = CreateActor<Player>(OBJECTORDER::Player);
}
