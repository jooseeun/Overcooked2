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
	//�� �ڿ� ��׶���
	{
		std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("EndBackground.png");
		Renderer.lock()->GetTransform().SetLocalPosition({ 0,0,1000 });
	}

	//�߾� ���â ������
	{
		std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_ResultsTicketsStandard_01.png");
		Renderer.lock()->GetTransform().SetLocalPosition({ 0,80,0 });
	}

	CreateUIRenderer("UI_PauseScreen_Backdrop_01.png");

	//���� �ϴ� ����Ű �˷��ִ� ���
	std::weak_ptr<OverCookedUIRenderer> ControlBg = CreateUIRenderer("control_bg.png");
	ControlBg.lock()->GetTransform().SetLocalPosition({ -318,-308,-1 });

	std::weak_ptr<OverCookedUIRenderer> Header = CreateUIRenderer("t_ui_dialog_header_01_non.png");
	Header.lock()->GetTransform().SetLocalPosition({ -260,290,-1 });

	//����ũ ������
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

	//�������� ���� Get
	GlobalGameData::SetCurStage("1-1");
	StageData NewData = GlobalGameData::GetCurStage();
	std::string StageName = NewData.StageName;

	//����� ��Ʈ
	{
		//�ְ�����
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

	//���â ���ʿ� ǥ�õǴ� �͵�
	{
		//�� ��׶���
		{
			for (int i = 0; i < 3; i++)
			{
				std::weak_ptr<OverCookedUIRenderer> Renderer = CreateUIRenderer("UI_ResultsScreen_EmptyStar_01.png");
				Renderer.lock()->ResistDebug();
				Renderer.lock()->GetTransform().SetLocalPosition({ (i - 1) * 110.f,185.f,0 });
			}
		}
	}

	//��Ͼ�ŷ
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

	//��Ͼ�ŷ �ִϸ��̼� ���ε�
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

	//�ɺ�
	{
		{
			Kevin_ = CreateComponent<GameEngineFBXAnimationRenderer>();
			Kevin_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
			Kevin_.lock()->SetFBXMesh("m_kevin_01.fbx", "TextureAnimation");
			Kevin_.lock()->CreateFBXAnimation("kPhase0_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 5);
			Kevin_.lock()->CreateFBXAnimation("kPhase1_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 4);
			Kevin_.lock()->CreateFBXAnimation("kPhase2_0", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 2);
			Kevin_.lock()->CreateFBXAnimation("kPhase2_1", GameEngineRenderingEvent("m_kevin_01.fbx", 0.035f, true), 6);
			Kevin_.lock()->ChangeAnimation("kPhase2_1");
			Kevin_.lock()->GetTransform().SetLocalScale({ 80,80,80 });
			Kevin_.lock()->GetTransform().SetLocalPosition({ -370.f,-48.f,0.f });
			Kevin_.lock()->GetTransform().SetLocalRotation({ 0,180,0 });

			ResistDebug("Kevin", Kevin_.lock()->GetTransform());
		}
	}
}

void ResultLevelActor::UIUpdate(float _DeltaTime)
{
}

void ResultLevelActor::UIEnd()
{
}