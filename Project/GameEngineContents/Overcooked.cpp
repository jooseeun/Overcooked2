#include "PreCompile.h"
#include "Overcooked.h"
#include "GameEngineStatusWindow.h"

#include "LoadingData.h"

#include "SelectStageLevel.h"
#include "LoadingLevel.h"
#include "ResultLevel.h"
#include "MapToolLevel.h"

#include "TitleLevel.h"

#include "Stage_1_1.h"
#include "Stage_1_2.h"
#include "Stage_1_3.h"
#include "Stage_1_4.h"
#include "Stage_2_1.h"

#include "MeshToolLevel.h"
#include "ServerTestLevel.h"

#include <GameEngineCore/GameEngineBlend.h>
#include "ServerInitManager.h"

Overcooked::Overcooked()
{
}

Overcooked::~Overcooked()
{
}

void Overcooked::Start()
{
	TextureLoad();
	MeshLoad();
	InputMake();
	LoadMaterial();
	SoundLoad();

	LoadingData::AddFunc("FirstLoad", std::bind(&Overcooked::LoadCommonResource, this));
	//1-1 1-3
	LoadingData::AddFunc("1-1", std::bind(&Overcooked::LoadStage, this, "1_1"));
	LoadingData::AddFunc("1-2", std::bind(&Overcooked::LoadStage, this, "1_2"));
	LoadingData::AddFunc("1-3", std::bind(&Overcooked::LoadStage, this, "1_3"));
	LoadingData::AddFunc("1-4", std::bind(&Overcooked::LoadStage, this, "1_4"));
	LoadingData::AddFunc("2-1", std::bind(&Overcooked::LoadStage, this, "2_1"));

	//GameEngineTime::SetLimitFrame(60);

	//{
	//	D3D11_BLEND_DESC Desc = { 0 };

	//	Desc.AlphaToCoverageEnable = FALSE;
	//	Desc.IndependentBlendEnable = FALSE;
	//	Desc.RenderTarget[0].BlendEnable = TRUE;
	//	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	//	Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
	//	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

	//	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	//	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	//	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

	//	GameEngineBlend::Create("AddBlend", Desc);
	//}

	//LoadingData::AddFunc("1-2", std::bind(&Overcooked::dfsdf, this, ));

	//LoadingInfo::AddFunc("Stage1_1", std::bind(&Overcooked::InitResourceStage1_1, this));
	//LoadingInfo::AddFunc("Stage1_2", std::bind(&Overcooked::InitResourceStage1_2, this));

	//or ;

	//LoadingInfo::AddFunc("Stage1_1", std::bind(&Overcooked::InitResource, this, "Stage1_1"));
	//LoadingInfo::AddFunc("Stage1_1", std::bind(&Overcooked::InitResource, this, "Stage1_2"));
	//InitResource(std::string _Name)
	//{
	//	LoadLevelMesh(_Name);
	//}

	CreateLevel<SelectStageLevel>("SelectStage");
	CreateLevel<LoadingLevel>("LoadingLevel");

	CreateLevel<Stage_1_1>("1-1");
	CreateLevel<Stage_1_2>("1-2");
	CreateLevel<Stage_1_3>("1-3");
	CreateLevel<Stage_1_4>("1-4");
	CreateLevel<Stage_2_1>("2-1");
	CreateLevel<MapToolLevel>("MapToolLevel");
	CreateLevel<MeshToolLevel>("MeshToolLevel");
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<ResultLevel>("ResultLevel");

	CreateLevel<ServerTestLevel>("ServerTestLevel");

	ChangeLevel("TitleLevel");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

	GameEngineInput::GetInst()->CreateKey("SubTest", 'K');
}

void Overcooked::LoadMaterial()
{
	//컨텐츠 Hlsl 파일 로드
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("ContentsShader");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
		}
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("UI");
		NewPipe->SetVertexShader("UI.hlsl");
		NewPipe->SetPixelShader("UI.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("LightObject");
		NewPipe->SetVertexShader("Light.hlsl");
		NewPipe->SetPixelShader("Light.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("ObjectHighlight");
		NewPipe->SetVertexShader("ObjectHighlight.hlsl");
		NewPipe->SetPixelShader("ObjectHighlight.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Vignette");
		NewPipe->SetVertexShader("Vignette.hlsl");
		NewPipe->SetPixelShader("Vignette.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Overlay");
		NewPipe->SetVertexShader("Overlay.hlsl");
		NewPipe->SetPixelShader("Overlay.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Water");
		NewPipe->SetVertexShader("Water.hlsl");
		NewPipe->SetPixelShader("Water.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Swirl");
		NewPipe->SetVertexShader("Swirl.hlsl");
		NewPipe->SetPixelShader("Swirl.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Bloom");
		NewPipe->SetVertexShader("Bloom.hlsl");
		NewPipe->SetPixelShader("Bloom.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Glass");
		NewPipe->SetVertexShader("Glass.hlsl");
		NewPipe->SetPixelShader("Glass.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("Portal");
		NewPipe->SetOutputMergerBlend("AddBlend");
		NewPipe->SetVertexShader("Portal.hlsl");
		NewPipe->SetPixelShader("Portal.hlsl");
		NewPipe->OutputMergerBlendSetting();
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("AddBlendAlpha");
		NewPipe->SetOutputMergerBlend("AddBlend");
		NewPipe->SetVertexShader("AddBlendAlpha.hlsl");
		NewPipe->SetPixelShader("AddBlendAlpha.hlsl");
		NewPipe->OutputMergerBlendSetting();
	}

	{
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("TextureSkybox");
		NewPipe->SetVertexShader("TextureSkybox.hlsl");
		NewPipe->SetPixelShader("TextureSkybox.hlsl");
	}
}

void Overcooked::Update(float _DeltaTime)
{
	ServerInitManager::Update(_DeltaTime);
}

void Overcooked::End()
{
	GameBgmPlayer::BgmPlayer_->Destroy();
}

void Overcooked::MeshLoad()
{
	//std::vector<std::string_view> TmpMeshs;
	//TmpMeshs.push_back("Object\\StaticObject\\CounterTop\\m_sk_countertop_01.FBX");
	//TmpMeshs.push_back("Object\\StaticObject\\CounterTop_Corner\\m_lorry_countertop_corner_01.FBX");
	//GameEngineFBXMesh::LoadAll(TmpMeshs);

	//std::vector<std::weak_ptr<GameEngineFBXMesh>> Test = GameEngineFBXMesh::LoadLevel("Level");
	LoadCommonResource();

	GameEngineFBXMesh::LoadLevel("Level\\Title");

	// 맵툴 오브젝트
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Chef");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Chef.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Chef1");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Chef1.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	//여기까지
}

void Overcooked::TextureLoad()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("Player");

		std::vector<GameEngineFile> Textures = Dir.GetAllFile();

		for (size_t i = 0; i < Textures.size(); i++)
		{
			GameEngineTexture::Load(Textures[i].GetFullPath());
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("UI");

		std::vector<GameEngineFile> Textures = Dir.GetAllFile();

		for (size_t i = 0; i < Textures.size(); i++)
		{
			GameEngineTexture::Load(Textures[i].GetFullPath());
		}

		GameEngineTexture::Cut("t_sk_crate_lid_images.png", 5, 5);
		GameEngineTexture::Cut("t_sk_crate_lid_images_dlc02.png", 3, 3);
		GameEngineTexture::Cut("t_sk_crate_lid_images_dlc03.png", 3, 3);
		GameEngineTexture::Cut("t_sk_crate_lid_images_dlc08.png", 4, 4);
	}

	{
		//Select UI
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

		//InGame UI
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("Texture");
			Dir.Move("UI");
			Dir.Move("InGame");

			std::vector<GameEngineFile> Textures = Dir.GetAllFile();

			for (size_t i = 0; i < Textures.size(); i++)
			{
				GameEngineTexture::Load(Textures[i].GetFullPath());
			}
		}

		//Thumbnail UI
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("Texture");
			Dir.Move("UI");
			Dir.Move("Thumbnail");

			std::vector<GameEngineFile> Textures = Dir.GetAllFile();

			for (size_t i = 0; i < Textures.size(); i++)
			{
				GameEngineTexture::Load(Textures[i].GetFullPath());
			}
		}

		//Coin FolderTexutre
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("Texture");
			Dir.Move("UI");
			Dir.Move("Coin");

			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}

		//Fire FolderTexutre
		GameEngineTexture::Cut("UI_FlameHUD_01.png", 8, 8);
		GameEngineFont::Load("Naughty Squirrel");
	}
}

void Overcooked::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

	for (auto& TmpDir : Folder)
	{
		std::vector<GameEngineFile> File = TmpDir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::LoadRessource(File[i].GetFullPath());
		}
	}
}

void Overcooked::InputMake()
{
	if (false == GameEngineInput::GetInst()->IsKey("LeftMouse"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("RightMouse", VK_RBUTTON);
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
		GameEngineInput::GetInst()->CreateKey("Test0", VK_NUMPAD0);
		GameEngineInput::GetInst()->CreateKey("Test1", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Test2", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Test3", VK_NUMPAD3);
	}
	//플레이어부분 Key
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("ChangePlayerCustom", 'M');
		GameEngineInput::GetInst()->CreateKey("ChangePlayerNum", 'N');
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerFront", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PlayerDash", 'X');
		GameEngineInput::GetInst()->CreateKey("PlayerHold", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("PlayerInteract", VK_CONTROL);
		GameEngineInput::GetInst()->CreateKey("PlayerDeath", VK_NUMPAD0);

	}


	GameEngineInput::GetInst()->CreateKey("Contents_Debug", 'B');
	GameEngineInput::GetInst()->CreateKey("MapObjectTest", VK_NUMPAD9);
}

void Overcooked::LoadStage(std::string_view _StageName)
{
	std::string StageName = _StageName.data();
	GameEngineFBXMesh::LoadLevel("Level\\" + StageName);
}

void Overcooked::LoadCommonResource()
{

	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Chef");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("uuu.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("uuu.FBX"));
	//}
	//
	//
	//Player Resource Animation 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("AlienGreen");

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CarDeath.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CarDeath.FBX"));
		}

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Chop.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Chop.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Death.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Death.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Drowning.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Drowning.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Fall.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Fall.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Idle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Idle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Idle2.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Idle2.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_IdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_IdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Slip.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Slip.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Stand.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Stand.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Throw.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Throw.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Walk.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Walk.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_WalkHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_WalkHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Wash.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Wash.FBX"));
		}

		//

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonEnterHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonEnterHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonEnterIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonEnterIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonFireHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonFireHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonFireIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonFireIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonFlyingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonFlyingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonFlyingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonFlyingIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonIdleIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonIdleIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonIdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonIdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonLandingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonLandingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CannonLandingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CannonLandingIdle.FBX"));
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("Buck");

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CarDeath.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CarDeath.FBX"));
		}

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Chop.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Chop.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Death.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Death.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Drowning.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Drowning.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Fall.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Fall.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Idle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Idle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Idle2.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Idle2.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_IdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_IdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Slip.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Slip.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Stand.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Stand.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Throw.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Throw.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Walk.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Walk.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_WalkHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_WalkHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_Wash.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_Wash.FBX"));
		}

		//
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonEnterHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonEnterHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonEnterIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonEnterIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonFireHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonFireHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonFireIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonFireIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonFlyingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonFlyingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonFlyingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonFlyingIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonIdleIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonIdleIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonIdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonIdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonLandingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonLandingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Buck_CannonLandingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Buck_CannonLandingIdle.FBX"));
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("Crocodile");

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CarDeath.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CarDeath.FBX"));
		}

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Chop.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Chop.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Death.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Death.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Drowning.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Drowning.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Fall.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Fall.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Idle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Idle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Idle2.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Idle2.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_IdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_IdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Slip.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Slip.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Stand.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Stand.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Throw.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Throw.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Walk.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Walk.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_WalkHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_WalkHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_Wash.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_Wash.FBX"));
		}
		//
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonEnterHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonEnterHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonEnterIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonEnterIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonFireHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonFireHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonFireIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonFireIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonFlyingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonFlyingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonFlyingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonFlyingIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonIdleIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonIdleIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonIdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonIdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonLandingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonLandingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Crocodile_CannonLandingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Crocodile_CannonLandingIdle.FBX"));
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("Dora");

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CarDeath.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CarDeath.FBX"));
		}

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Chop.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Chop.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Death.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Death.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Drowning.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Drowning.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Fall.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Fall.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Idle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Idle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Idle2.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Idle2.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_IdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_IdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Slip.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Slip.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Stand.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Stand.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Throw.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Throw.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Walk.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Walk.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_WalkHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_WalkHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_Wash.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_Wash.FBX"));
		}
		//
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonEnterHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonEnterHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonEnterIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonEnterIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonFireHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonFireHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonFireIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonFireIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonFlyingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonFlyingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonFlyingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonFlyingIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonIdleIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonIdleIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonIdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonIdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonLandingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonLandingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Dora_CannonLandingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Dora_CannonLandingIdle.FBX"));
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("Eagle");

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CarDeath.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CarDeath.FBX"));
		}

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Chop.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Chop.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Death.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Death.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Drowning.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Drowning.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Fall.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Fall.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Idle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Idle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Idle2.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Idle2.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_IdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_IdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Slip.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Slip.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Stand.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Stand.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Throw.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Throw.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Walk.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Walk.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_WalkHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_WalkHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_Wash.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_Wash.FBX"));
		}
		//
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonEnterHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonEnterHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonEnterIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonEnterIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonFireHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonFireHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonFireIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonFireIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonFlyingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonFlyingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonFlyingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonFlyingIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonIdleIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonIdleIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonIdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonIdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonLandingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonLandingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Eagle_CannonLandingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Eagle_CannonLandingIdle.FBX"));
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("Panda");

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CarDeath.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CarDeath.FBX"));
		}

		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Chop.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Chop.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Death.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Death.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Drowning.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Drowning.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Fall.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Fall.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Idle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Idle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Idle2.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Idle2.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_IdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_IdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Slip.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Slip.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Stand.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Stand.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Throw.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Throw.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Walk.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Walk.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_WalkHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_WalkHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_Wash.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_Wash.FBX"));
		}
		//
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonEnterHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonEnterHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonEnterIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonEnterIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonFireHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonFireHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonFireIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonFireIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonFlyingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonFlyingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonFlyingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonFlyingIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonIdleHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonIdleHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonIdleIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonIdleIdle.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonLandingHolding.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonLandingHolding.FBX"));
		}
		{
			GameEngineDirectory MeshDir = Dir;
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Panda_CannonLandingIdle.FBX"));
			std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Panda_CannonLandingIdle.FBX"));
		}
	}
}