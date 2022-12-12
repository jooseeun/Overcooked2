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

	//중앙 결과창 렌더러
	{
		std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_ResultsTicketsStandard_01.png");
		Renderer.lock()->GetTransform().SetLocalPosition({ 0,80,0 });
	}

	CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	//좌측 하단 조작키 알려주는 배너
	std::weak_ptr<OverCookedUIRenderer> ControlBg = CreateUIRenderer("control_bg.png");
	ControlBg.lock()->GetTransform().SetLocalPosition({ -318,-308,-1 });

	std::weak_ptr<OverCookedUIRenderer> Header = CreateUIRenderer("t_ui_dialog_header_01_non.png");
	Header.lock()->GetTransform().SetLocalPosition({ -260,290,-1 });

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
		HeaderFont.lock()->SetColor({ 1.f,1.f,1.f,1 });
		HeaderFont.lock()->SetSize(50.f);
		HeaderFont.lock()->SetAffectTransform(true);
		HeaderFont.lock()->GetTransform().SetLocalPosition({ -300,330,-10 });
		//ResistDebug("Font", HeaderFont.lock()->GetTransform());
	}

	//결과창 안쪽에 표시되는 것들
	{
		//별 백그라운드
		{
			for (int i = 0; i < 3; i++)
			{
				std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_ResultsScreen_EmptyStar_01.png");
				Renderer.lock()->ResistDebug();
				Renderer.lock()->GetTransform().SetLocalPosition({ (i - 1) * 110.f,185.f,0 });
			}
		}
	}

	//어니언킹
	{
		Mesh = CreateComponent<GameEngineFBXAnimationRenderer>();
		Mesh.lock()->ChangeCamera(CAMERAORDER::AboveUICAMERA);

		Mesh.lock()->SetFBXMeshExceptionMesh("m_onion_king_01.fbx", "TextureAnimation", 7);

		Mesh.lock()->CreateFBXAnimation("Phase0_0",
			GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 0);
		Mesh.lock()->CreateFBXAnimation("Phase1_0",
			GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 1);
		Mesh.lock()->CreateFBXAnimation("Phase1_1",
			GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 2);
		Mesh.lock()->CreateFBXAnimation("Phase2_0",
			GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 3);
		Mesh.lock()->CreateFBXAnimation("Phase2_1",
			GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, false), 5);

		Mesh.lock()->ChangeAnimation("Phase2_1");
		Mesh.lock()->GetTransform().SetLocalScale({ 200,200,200 });
		Mesh.lock()->GetTransform().SetLocalPosition({ 390.f,-68.f,0.f });
		Mesh.lock()->GetTransform().SetLocalRotation({ 0,180,0 });

		ResistDebug("OnionKing", Mesh.lock()->GetTransform());
	}

	Mesh.lock()->AnimationBindTime("Phase2_1", [&](const GameEngineRenderingEvent& _Info, float _Time)
		{
			if (_Info.PlayTime >= 0.8f)
			{
				Mesh.lock()->ChangeAnimation("Phase2_1");
				Mesh.lock()->GetTransform().SetLocalScale({ 200,200,200 });
				Mesh.lock()->GetTransform().SetLocalPosition({ 390.f,-68.f,0.f });
				Mesh.lock()->GetTransform().SetLocalRotation({ 0,180,0 });
				Mesh.lock()->GetCurAnim()->bOnceEnd = false;
				Mesh.lock()->GetCurAnim()->Reset();
			}
		});
}

void ResultLevelActor::UIUpdate(float _DeltaTime)
{
}

void ResultLevelActor::UIEnd()
{
}