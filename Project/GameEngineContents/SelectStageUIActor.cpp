#include "PreCompile.h"
#include "SelectStageUIActor.h"
#include "OverCookedUIRenderer.h"

SelectStageUIActor::SelectStageUIActor()
{
}

SelectStageUIActor::~SelectStageUIActor()
{
}

void SelectStageUIActor::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("SelectStage");

		std::vector<GameEngineFile> Textures = Dir.GetAllFile();

		for (size_t i = 0; i < Textures.size(); i++)
		{
			GameEngineTexture::Load(Textures[i].GetFullPath());
		}
	}

	OverCookedUIRenderer* Test = CreateComponent<OverCookedUIRenderer>();
	Test->SetTexture("UI_PauseScreen_Backdrop_01.png");
	Test->ScaleToTexture();
}

void SelectStageUIActor::Update(float _DeltaTime)
{
}

void SelectStageUIActor::End()
{
}