#include "PreCompile.h"
#include "ResultLevelActor.h"

#include "GlobalGameData.h"
#include "OverCookedUIRenderer.h"
#include "GamePlayLevel.h"

ResultLevelActor::ResultLevelActor()
{
}

ResultLevelActor::~ResultLevelActor()
{
}

void ResultLevelActor::UIStart()
{
	CreateUIRenderer("EndBackground.png");

	CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	//좌측 하단 조작키 알려주는 배너
	std::weak_ptr<OverCookedUIRenderer> ControlBg = CreateUIRenderer("control_bg.png");
	ControlBg.lock()->GetTransform().SetLocalPosition({-318,-308,-1});

	std::weak_ptr<OverCookedUIRenderer> Header = CreateUIRenderer("t_ui_dialog_header_01_non.png");
	Header.lock()->GetTransform().SetLocalPosition({-260,290,-1});

	//마스크 렌더러
	{
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("screen_bg_overlay_01.png");
		NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
		NewRenderer->SetSamplerWrap();
		NewRenderer->StartDown(0.2f);
	}
	{
		std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("screen_bg_overlay_02.png");
		NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
		NewRenderer->SetSamplerWrap();
		NewRenderer->StartDown(0.1f);
	}


	//스테이지 정보 Get
	GlobalGameData::SetCurStage("1-1");
	StageData NewData = GlobalGameData::GetCurStage();
	std::string StageName = NewData.StageName;

	//헤더쪽 폰트
	{
		//최고점수
		std::weak_ptr<GameEngineFontRenderer> HeaderFont = CreateComponent<GameEngineFontRenderer>("CowntDownFont");
		HeaderFont.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
		HeaderFont.lock()->SetText(StageName, "Naughty Squirrel");
		//HeaderFont.lock()->SetLeftAndRightSort(LeftAndRightSort::LEFT);
		HeaderFont.lock()->SetColor({1.f,1.f,1.f,1 });
		HeaderFont.lock()->SetSize(50.f);
		HeaderFont.lock()->SetAffectTransform(true);
		HeaderFont.lock()->GetTransform().SetLocalPosition({ -300,330,-10 });
		//ResistDebug("Font", HeaderFont.lock()->GetTransform());
	}
}

void ResultLevelActor::UIUpdate(float _DeltaTime)
{
}

void ResultLevelActor::UIEnd()
{
}
