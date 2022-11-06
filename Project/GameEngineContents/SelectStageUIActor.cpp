#include "PreCompile.h"
#include "SelectStageUIActor.h"
#include "OverCookedUIRenderer.h"
#include "UIDebugGUI.h"
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

SelectStageUIActor::SelectStageUIActor()
{
}

SelectStageUIActor::~SelectStageUIActor()
{
}

void SelectStageUIActor::Start()
{
	//필요한 리소스 로드
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

	GameEngineFont::Load("Naughty Squirrel");

	EndBackground_ = CreateComponent<OverCookedUIRenderer>("EndBackground");
	EndBackground_->SetTexture("EndBackground.png");
	EndBackground_->ScaleToTexture();

	Background_ = CreateComponent<OverCookedUIRenderer>("Background");
	Background_->SetTexture("UI_PauseScreen_Backdrop_01.png");
	Background_->ScaleToTexture();

	Header_ = CreateComponent<OverCookedUIRenderer>("Header");
	Header_->SetTexture("t_ui_dialog_header_01_d.png");
	Header_->ScaleToTexture();
	Header_->GetTransform().SetLocalPosition({ -260,290 });

	CountDownFont_ = CreateComponent<GameEngineFontRenderer>("CowntDownFont");
	CountDownFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	CountDownFont_->SetText("0sd4", "Naughty Squirrel");
	CountDownFont_->SetColor({ 120.f/256.f,178.f/256.f,218.f/256.f,1 });
	CountDownFont_->SetPositionMode(FontPositionMode::SCREEN);
}

void SelectStageUIActor::Update(float _DeltaTime)
{
}

void SelectStageUIActor::End()
{
}