#include "PreCompile.h"
#include "SelectStageLevel.h"
#include "SelectStageUIActor.h"
SelectStageLevel::SelectStageLevel()
{
}

SelectStageLevel::~SelectStageLevel()
{
}

void SelectStageLevel::Start()
{
	SelectStageUIActor* NewActor = CreateActor< SelectStageUIActor>();
}

void SelectStageLevel::Update(float _DeltaTime)
{
}

void SelectStageLevel::End()
{
}