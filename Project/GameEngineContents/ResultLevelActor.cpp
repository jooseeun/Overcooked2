#include "PreCompile.h"
#include "ResultLevelActor.h"

#include "GlobalGameData.h"
#include "OverCookedUIRenderer.h"
#include "GamePlayLevel.h"

//void GameEngineFBXAnimationRenderer::SetFBXMeshExceptionMesh(const std::string& _Name, std::string _Material, size_t MeshIndex)
//{
//	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);
//
//	if (GlobalIOManager::Load(IOType::Mesh, "_" + FindFBXMesh->GetNameCopy()))
//	{
//		MeshData Data = GlobalIOManager::GetMeshData();
//
//		for (size_t j = 0; j < Data.PreviewMeshInfo_.size(); j++)
//		{
//			FindFBXMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTexturePath = Data.PreviewMeshInfo_[j].DifTexturePath_;
//			FindFBXMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTextureName = Data.PreviewMeshInfo_[j].DifTextureName_;
//		}
//	}
//
//	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
//	{
//		if (UnitCount == MeshIndex)
//		{
//			continue;
//		}
//		for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(UnitCount); SubSetCount++)
//		{
//			SetFBXMesh(_Name, _Material, UnitCount, SubSetCount);
//		}
//	}
//}
ResultLevelActor::ResultLevelActor()
{
}

ResultLevelActor::~ResultLevelActor()
{
}

void ResultLevelActor::UIStart()
{
	//맨 뒤에 백그라운드
	{
		std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("EndBackground.png");
		Renderer.lock()->GetTransform().SetLocalPosition({ 0,0,1000 });
	}

	//중앙 결과창 렌더러
	{
		std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_ResultsTicketsStandard_01.png");
		Renderer.lock()->GetTransform().SetLocalPosition({ 0,80,950 });
	}

	{
		std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");
		Renderer.lock()->GetTransform().SetLocalPosition({ 0,0,900 });
	}

	//좌측 하단 조작키 알려주는 배너
	std::weak_ptr<OverCookedUIRenderer> ControlBg = CreateUIRenderer("control_bg.png");
	ControlBg.lock()->GetTransform().SetLocalPosition({ -318,-308,-1 });

	std::weak_ptr<OverCookedUIRenderer> Header = CreateUIRenderer("t_ui_dialog_header_01_non.png");
	Header.lock()->GetTransform().SetLocalPosition({ -260,290,-1 });

	//마스크 렌더러
	{
		{
			std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("screen_bg_overlay_01.png");
			NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
			NewRenderer->SetSamplerWrap();
			NewRenderer->StartDown(0.2f);
			NewRenderer->GetTransform().SetLocalPosition({ 0,0,500 });
		}
		{
			std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateUIRenderer("screen_bg_overlay_02.png");
			NewRenderer->SetMaskTexture("UI_PauseScreen_Backdrop_01.png");
			NewRenderer->SetSamplerWrap();
			NewRenderer->StartDown(0.1f);
			NewRenderer->GetTransform().SetLocalPosition({ 0,0,500 });
		}
	}

	//플레이어 아이콘
	{
		CreatePlayerIcon(0, "LoveSushi");
		CreatePlayerIcon(1, "AS40");
		CreatePlayerIcon(2, "NiceRice");
		CreatePlayerIcon(3, "HelpMe");
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

	//메쉬
	{
		//어니언킹
		{
			OnionKing_ = CreateComponent<GameEngineFBXAnimationRenderer>();
			OnionKing_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);

			OnionKing_.lock()->SetFBXMeshExceptionMesh("m_onion_king_01.fbx", "TextureAnimation", 7);

			OnionKing_.lock()->CreateFBXAnimation("Phase0_0",
				GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 0);
			OnionKing_.lock()->CreateFBXAnimation("Phase1_0",
				GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 1);
			OnionKing_.lock()->CreateFBXAnimation("Phase1_1",
				GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 2);
			OnionKing_.lock()->CreateFBXAnimation("Phase2_0",
				GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 3);
			OnionKing_.lock()->CreateFBXAnimation("Phase2_1",
				GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, false), 5);

			OnionKing_.lock()->ChangeAnimation("Phase2_1");
			OnionKing_.lock()->GetTransform().SetLocalScale({ 200,200,200 });
			OnionKing_.lock()->GetTransform().SetLocalPosition({ 380.f,-68.f,0.f });
			OnionKing_.lock()->GetTransform().SetLocalRotation({ 0,180,0 });

			//ResistDebug("OnionKing", OnionKing_.lock()->GetTransform());
		}

		//어니언킹 애니메이션 바인딩
		{
			OnionKing_.lock()->AnimationBindTime("Phase2_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 2.35f)
					{
						OnionKing_.lock()->ChangeAnimation("Phase2_0");
						OnionKing_.lock()->GetCurAnim()->bOnceEnd = false;
						OnionKing_.lock()->GetCurAnim()->Reset();
					}
				});

			OnionKing_.lock()->AnimationBindTime("Phase2_1", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 0.8f)
					{
						OnionKing_.lock()->ChangeAnimation("Phase2_1");
						OnionKing_.lock()->GetCurAnim()->bOnceEnd = false;
						OnionKing_.lock()->GetCurAnim()->Reset();
					}
				});
		}

		//케빈
		{
			{
				Kevin_ = CreateComponent<GameEngineFBXAnimationRenderer>();
				Kevin_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				Kevin_.lock()->SetFBXMesh("m_kevin_01.fbx", "TextureAnimation");
				Kevin_.lock()->CreateFBXAnimation("kPhase0_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 3);
				Kevin_.lock()->CreateFBXAnimation("kPhase1_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 4);
				Kevin_.lock()->CreateFBXAnimation("kPhase2_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 2);
				Kevin_.lock()->CreateFBXAnimation("kPhase2_1", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 6);
				Kevin_.lock()->ChangeAnimation("kPhase2_1");
				Kevin_.lock()->GetTransform().SetLocalScale({ 80,80,80 });
				Kevin_.lock()->GetTransform().SetLocalPosition({ -370.f,-48.f,50.f });
				Kevin_.lock()->GetTransform().SetLocalRotation({ 0,140,0 });

				ResistDebug("Kevin", Kevin_.lock()->GetTransform());
			}
		}

		//케빈 애니메이션 바인딩 GlobalGameData::DebugValue1_.x
		{
			Kevin_.lock()->AnimationBindTime("kPhase0_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 1.4f)
					{
						Kevin_.lock()->ChangeAnimation("kPhase0_0");
						Kevin_.lock()->GetCurAnim()->bOnceEnd = false;
						Kevin_.lock()->GetCurAnim()->Reset();
					}
				});

			Kevin_.lock()->AnimationBindTime("kPhase1_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 1.6)
					{
						Kevin_.lock()->ChangeAnimation("kPhase1_0");
						Kevin_.lock()->GetCurAnim()->bOnceEnd = false;
						Kevin_.lock()->GetCurAnim()->Reset();
					}
				});

			Kevin_.lock()->AnimationBindTime("kPhase2_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 0.95f)
					{
						Kevin_.lock()->ChangeAnimation("kPhase2_0");
						Kevin_.lock()->GetCurAnim()->bOnceEnd = false;
						Kevin_.lock()->GetCurAnim()->Reset();
					}
				});

			Kevin_.lock()->AnimationBindTime("kPhase2_1", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 0.8f)
					{
						Kevin_.lock()->ChangeAnimation("kPhase2_1");
						Kevin_.lock()->GetCurAnim()->bOnceEnd = false;
						Kevin_.lock()->GetCurAnim()->Reset();
					}
				});
		}
	}
}

void ResultLevelActor::UIUpdate(float _DeltaTime)
{
	UpdatePlayerIcon(_DeltaTime);
}

void ResultLevelActor::UIEnd()
{
}