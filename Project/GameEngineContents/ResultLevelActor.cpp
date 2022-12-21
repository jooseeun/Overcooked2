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
	//GlobalGameData::SetCurStage("1-1");
	//GlobalGameData::AddScore(920, 10);
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
		//별 백그라운드 & 점수폰트
		{
			std::vector<int> Score = { 300,600,900 };
			for (int i = 0; i < 3; i++)
			{
				std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_ResultsScreen_EmptyStar_01.png");
				Renderer.lock()->ResistDebug();
				Renderer.lock()->GetTransform().SetLocalPosition({ (i - 1) * 110.f,185.f,0 });

				{
					std::weak_ptr<GameEngineFontRenderer> ScoreFont_ = CreateComponent<GameEngineFontRenderer>();
					ScoreFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
					ScoreFont_.lock()->SetText(std::to_string(Score[i]), "Naughty Squirrel");
					ScoreFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::LEFT);
					ScoreFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
					ScoreFont_.lock()->SetSize(19.f);
					ScoreFont_.lock()->SetAffectTransform(true);
					ScoreFont_.lock()->GetTransform().SetLocalPosition({ (i - 1) * 110.f-20.f,145.f,0 });
				}
			}
		}

		//찐별
		{
			for (int i = 0; i < 3; i++)
			{
				std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_LoadingScreen_Star_01.png");
				//Renderer.lock()->ResistDebug();
				Renderer.lock()->GetTransform().SetLocalPosition({ (i - 1) * 110.f,185.f,0 });
				Renderer.lock()->StartPump(1.6f,7.f);
				Renderer.lock()->Off();
				FrontStarRenderer_.push_back(Renderer);
			}
		}

		//결과 폰트들
		{
			//배달된 주문
			{
				DeliveredFoodCountFont_ = CreateComponent<GameEngineFontRenderer>();
				DeliveredFoodCountFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				DeliveredFoodCountFont_.lock()->SetText("배달된 주문 x "+std::to_string(GlobalGameData::DeliveredCount_), "Naughty Squirrel");
				DeliveredFoodCountFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::LEFT);
				DeliveredFoodCountFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				DeliveredFoodCountFont_.lock()->SetSize(23.f);
				DeliveredFoodCountFont_.lock()->SetAffectTransform(true);
				DeliveredFoodCountFont_.lock()->GetTransform().SetLocalPosition({ -215,110,-10 });
				DeliveredFoodCountFont_.lock()->Off();

				//ResistDebug("DeliveredFoodCountFont_", DeliveredFoodCountFont_.lock()->GetTransform());
			}

			//배달된 주문 스코어
			{
				DeliveredFoodScoreFont_ = CreateComponent<GameEngineFontRenderer>();
				DeliveredFoodScoreFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				DeliveredFoodScoreFont_.lock()->SetText(std::to_string(GlobalGameData::DeliveredScore_), "Naughty Squirrel");
				DeliveredFoodScoreFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
				DeliveredFoodScoreFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				DeliveredFoodScoreFont_.lock()->SetSize(23.f);
				DeliveredFoodScoreFont_.lock()->SetAffectTransform(true);
				DeliveredFoodScoreFont_.lock()->GetTransform().SetLocalPosition({ 200,110,-10 });
				DeliveredFoodScoreFont_.lock()->Off();

				//ResistDebug("DeliveredFoodCountFont_", DeliveredFoodScoreFont_.lock()->GetTransform());
			}

			//팁
			{
				TipFont_ = CreateComponent<GameEngineFontRenderer>();
				TipFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				TipFont_.lock()->SetText("팁", "Naughty Squirrel");
				TipFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::LEFT);
				TipFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				TipFont_.lock()->SetSize(23.f);
				TipFont_.lock()->SetAffectTransform(true);
				TipFont_.lock()->GetTransform().SetLocalPosition({ -215,75,-10 });
				TipFont_.lock()->Off();
				//ResistDebug("TipFont_", TipFont_.lock()->GetTransform());
			}

			//팁 스코어
			{
				TipScoreFont_ = CreateComponent<GameEngineFontRenderer>();
				TipScoreFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				TipScoreFont_.lock()->SetText(std::to_string(GlobalGameData::Tips_), "Naughty Squirrel");
				TipScoreFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
				TipScoreFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				TipScoreFont_.lock()->SetSize(23.f);
				TipScoreFont_.lock()->SetAffectTransform(true);
				TipScoreFont_.lock()->GetTransform().SetLocalPosition({ 200,75,-10 });
				TipScoreFont_.lock()->Off();
			}

			//실패한주문
			{
				FailFoodCountFont_ = CreateComponent<GameEngineFontRenderer>();
				FailFoodCountFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				FailFoodCountFont_.lock()->SetText("실패한 주문 x " + std::to_string(GlobalGameData::FailCount_), "Naughty Squirrel");
				FailFoodCountFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::LEFT);
				FailFoodCountFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				FailFoodCountFont_.lock()->SetSize(23.f);
				FailFoodCountFont_.lock()->SetAffectTransform(true);
				FailFoodCountFont_.lock()->GetTransform().SetLocalPosition({ -215,40,-10 });
				FailFoodCountFont_.lock()->Off();
				//ResistDebug("TipFont_", TipFont_.lock()->GetTransform());
			}

			//실패한 주문 스코어
			{
				FailFoodScoreFont_ = CreateComponent<GameEngineFontRenderer>();
				FailFoodScoreFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				FailFoodScoreFont_.lock()->SetText(std::to_string(GlobalGameData::FailScore_), "Naughty Squirrel");
				FailFoodScoreFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
				FailFoodScoreFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				FailFoodScoreFont_.lock()->SetSize(23.f);
				FailFoodScoreFont_.lock()->SetAffectTransform(true);
				FailFoodScoreFont_.lock()->GetTransform().SetLocalPosition({ 200,40,-10 });
				FailFoodScoreFont_.lock()->Off();
			}

			//합계 글
			{
				TotalFont_ = CreateComponent<GameEngineFontRenderer>();
				TotalFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				TotalFont_.lock()->SetText("합계:", "Naughty Squirrel");
				TotalFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::LEFT);
				TotalFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				TotalFont_.lock()->SetSize(30.f);
				TotalFont_.lock()->SetAffectTransform(true);
				TotalFont_.lock()->GetTransform().SetLocalPosition({ -215,-10,-10 });
				TotalFont_.lock()->Off();
				ResistDebug("TipFont_", TotalFont_.lock()->GetTransform());
			}

			//합계 스코어
			{
				TotalScoreFont_ = CreateComponent<GameEngineFontRenderer>();
				TotalScoreFont_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
				TotalScoreFont_.lock()->SetText(std::to_string(GlobalGameData::Score_), "Naughty Squirrel");
				TotalScoreFont_.lock()->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
				TotalScoreFont_.lock()->SetColor({ 0.5f,0.5f,0.5f,1 });
				TotalScoreFont_.lock()->SetSize(30.f);
				TotalScoreFont_.lock()->SetAffectTransform(true);
				TotalScoreFont_.lock()->GetTransform().SetLocalPosition({ 200,-10,-10 });
				TotalScoreFont_.lock()->Off();
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

			OnionKing_.lock()->CreateFBXAnimation("PhaseFail_0",
				GameEngineRenderingEvent("m_onion_king_01.fbx", 0.035f, true), 4);
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

			OnionKing_.lock()->ChangeAnimation("Phase1_1");
			OnionKing_.lock()->GetTransform().SetLocalScale({ 200,200,200 });
			OnionKing_.lock()->GetTransform().SetLocalPosition({ 380.f,-68.f,0.f });
			OnionKing_.lock()->GetTransform().SetLocalRotation({ 0,180,0 });

			//ResistDebug("OnionKing", OnionKing_.lock()->GetTransform());
		}

		//어니언킹 애니메이션 바인딩 GlobalGameData::DebugValue1_.x
		{

			OnionKing_.lock()->AnimationBindTime("PhaseFail_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 2.7f)
					{
						OnionKing_.lock()->ChangeAnimation("PhaseFail_0");
						OnionKing_.lock()->GetCurAnim()->bOnceEnd = false;
						OnionKing_.lock()->GetCurAnim()->Reset();
					}
				});
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
				Kevin_.lock()->CreateFBXAnimation("kPhaseFail_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 3);
				Kevin_.lock()->CreateFBXAnimation("kPhase0_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 5);
				Kevin_.lock()->CreateFBXAnimation("kPhase1_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 4);
				Kevin_.lock()->CreateFBXAnimation("kPhase1_1", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 4);
				Kevin_.lock()->CreateFBXAnimation("kPhase2_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 2);
				Kevin_.lock()->CreateFBXAnimation("kPhase2_1", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 6);
				Kevin_.lock()->ChangeAnimation("kPhase1_1");
				Kevin_.lock()->GetTransform().SetLocalScale({ 80,80,80 });
				Kevin_.lock()->GetTransform().SetLocalPosition({ -370.f,-48.f,50.f });
				Kevin_.lock()->GetTransform().SetLocalRotation({ 0,140,0 });

				ResistDebug("Kevin", Kevin_.lock()->GetTransform());
			}
		}

		//케빈 애니메이션 바인딩 GlobalGameData::DebugValue1_.x
		{
			Kevin_.lock()->AnimationBindTime("kPhaseFail_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 1.4f)
					{
						Kevin_.lock()->ChangeAnimation("kPhaseFail_0");
						Kevin_.lock()->GetCurAnim()->bOnceEnd = false;
						Kevin_.lock()->GetCurAnim()->Reset();
					}
				});

			Kevin_.lock()->AnimationBindTime("kPhase0_0", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 2.7f)
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

			Kevin_.lock()->AnimationBindTime("kPhase1_1", [&](const GameEngineRenderingEvent& _Info, float _Time)
				{
					if (_Info.PlayTime >= 1.6)
					{
						Kevin_.lock()->ChangeAnimation("kPhase1_1");
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


		//스코어 기준 애니메이션 점수 판단
		{
			int Score = GlobalGameData::Score_;
			if (Score < 300)
			{
				OnionKing_.lock()->ChangeAnimation("PhaseFail_0");
				Kevin_.lock()->ChangeAnimation("kPhaseFail_0");
			}
			else if (Score >= 300 && Score < 600)
			{
				//int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);
				OnionKing_.lock()->ChangeAnimation("Phase0_0");
				Kevin_.lock()->ChangeAnimation("kPhase0_0");
			}
			else if (Score >= 600 && Score < 900)
			{
				int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);
				OnionKing_.lock()->ChangeAnimation("Phase1_"+std::to_string(Num));
				Kevin_.lock()->ChangeAnimation("kPhase1_"+std::to_string(Num));
			}
			else if (Score >= 900)
			{
				int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);
				OnionKing_.lock()->ChangeAnimation("Phase2_" + std::to_string(Num));
				Kevin_.lock()->ChangeAnimation("kPhase2_" + std::to_string(Num));
			}
		}
	}
}

void ResultLevelActor::UIUpdate(float _DeltaTime)
{
	if (TransitionIcon_->IsFinishFadeOut_ == true)
	{
		std::vector<GameEngineLevel*> AllLevel = GameEngineCore::GetAllLevelVector();
		GEngine::ChangeLevel("SelectStage");
	}
	//UpdateScore
	{
		IterTime_ += _DeltaTime;
		if (IterTime_ > 0.5f)
		{
			DeliveredFoodCountFont_.lock()->On();
		}
		if (IterTime_ > 1.0f)
		{
			DeliveredFoodScoreFont_.lock()->On();
			if (GlobalGameData::Score_ >= 300)
			{
				FrontStarRenderer_[0].lock()->On();

			}
		}
		if (IterTime_ > 1.5f)
		{
			TipFont_.lock()->On();
		}
		if (IterTime_ > 2.f)
		{
			TipScoreFont_.lock()->On();
			if (GlobalGameData::Score_ >= 600)
			{
				FrontStarRenderer_[1].lock()->On();
			}

		}
		if (IterTime_ > 2.5f)
		{
			FailFoodCountFont_.lock()->On();
		}
		if (IterTime_ > 3.f)
		{
			FailFoodScoreFont_.lock()->On();
			if (GlobalGameData::Score_ >= 900)
			{
				FrontStarRenderer_[2].lock()->On();
			}


		}
		if (IterTime_ > 3.5f)
		{
			TotalFont_.lock()->On();
		}
		if (IterTime_ > 4.f)
		{
			TotalScoreFont_.lock()->On();
			if (GameEngineInput::GetInst()->IsDownKey("PlayerHold") == true)
			{
				StartFadeOut();
			}
		}
	}
	UpdatePlayerIcon(_DeltaTime);
}

void ResultLevelActor::UIEnd()
{
}