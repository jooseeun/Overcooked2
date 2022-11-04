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
}

void SelectStageUIActor::Update(float _DeltaTime)
{
}

void SelectStageUIActor::End()
{
}