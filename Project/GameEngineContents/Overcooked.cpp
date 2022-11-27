#include "PreCompile.h"
#include "Overcooked.h"

#include "LoadingData.h"

#include "SelectStageLevel.h"
#include "LoadingLevel.h"
#include "MapToolLevel.h"

#include "TitleLevel.h"

#include "Stage_1_1.h"
#include "Stage_1_2.h"
#include "Stage_1_3.h"
#include "Stage_1_4.h"

#include "MeshToolLevel.h"

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

	LoadingData::AddFunc("FirstLoad", std::bind(&Overcooked::LoadCommonResource, this));
	//1-1 1-3
	LoadingData::AddFunc("1-1", std::bind(&Overcooked::LoadStage, this, "1_1"));
	LoadingData::AddFunc("1-2", std::bind(&Overcooked::LoadStage, this, "1_2"));
	LoadingData::AddFunc("1-3", std::bind(&Overcooked::LoadStage, this, "1_3"));
	LoadingData::AddFunc("1-4", std::bind(&Overcooked::LoadStage, this, "1_4"));

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
	CreateLevel<MapToolLevel>("MapToolLevel");
	CreateLevel<MeshToolLevel>("MeshToolLevel");
	CreateLevel<TitleLevel>("TitleLevel");

	ChangeLevel("SelectStage");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
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
		std::shared_ptr<GameEngineMaterial> NewPipe = GameEngineMaterial::Create("JBMWater");
		NewPipe->SetVertexShader("JBMWater.hlsl");
		NewPipe->SetPixelShader("JBMWater.hlsl");
	}
}

void Overcooked::Update(float _DeltaTime)
{
}

void Overcooked::End()
{
}

void Overcooked::MeshLoad()
{
	//std::vector<std::string_view> TmpMeshs;
	//TmpMeshs.push_back("Object\\StaticObject\\CounterTop\\m_sk_countertop_01.FBX");
	//TmpMeshs.push_back("Object\\StaticObject\\CounterTop_Corner\\m_lorry_countertop_corner_01.FBX");
	//GameEngineFBXMesh::LoadAll(TmpMeshs);

	//std::vector<std::weak_ptr<GameEngineFBXMesh>> Test = GameEngineFBXMesh::LoadLevel("Level");

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("TitleVan");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_van_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

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
		Dir.Move("UI");

		std::vector<GameEngineFile> Textures = Dir.GetAllFile();

		for (size_t i = 0; i < Textures.size(); i++)
		{
			GameEngineTexture::Load(Textures[i].GetFullPath());
		}

		GameEngineTexture::Cut("t_sk_crate_lid_images.png", 5, 5);
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

		GameEngineFont::Load("Naughty Squirrel");
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

		//GameEngineInput::GetInst()->CreateKey("PlayerSlice", VK_CONTROL);
	}
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
	}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("MoveNPC_Beard_Orange_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Orange_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Orange_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("MoveNPC_Beard_Waiter_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Waiter_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Waiter_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("MoveNPC_Dora_Civ_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Dora_Civ_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Dora_Civ_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("MoveNPC_Hispanic_Yellow_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Hispanic_Yellow_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Hispanic_Yellow_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("MoveNPC_Mike_Civ_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Mike_Civ_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Mike_Civ_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Asian_Blue_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Asian_Blue_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Asian_Blue_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Beard_Green_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Green_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Green_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Beard_Waiter_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Waiter_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Waiter_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Beard_Yellow_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Yellow_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Yellow_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Dora_Civ_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Dora_Civ_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Dora_Civ_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Dora_Orange_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Dora_Orange_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Dora_Orange_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Dora_Wizard_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Dora_Wizard_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Dora_Wizard_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_DoraBlonde_Blue_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Blue_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Blue_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_DoraBlonde_Green_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Green_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Green_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_DoraBlonde_Orange_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Orange_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Orange_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_DoraBlonde_Wizard_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Wizard_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Wizard_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_DoraBlonde_Yellow_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Yellow_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Yellow_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Ginger_Blue_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Ginger_Blue_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Ginger_Blue_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Ginger_Green_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Ginger_Green_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Ginger_Green_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Hispanic_Brown_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Hispanic_Brown_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Hispanic_Brown_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Hispanic_Orange_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Hispanic_Orange_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Hispanic_Orange_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Hispanic_Wizard_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Hispanic_Wizard_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Hispanic_Wizard_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_MiddleEastern_Waiter_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEastern_Waiter_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEastern_Waiter_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_MiddleEatern_Green_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Green_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Green_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_MiddleEatern_Orange_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Orange_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Orange_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_MiddleEatern_Wizard_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Wizard_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Wizard_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Mike_Blue_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Blue_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Blue_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Mike_Wizard_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Wizard_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Wizard_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Mike_Yellow_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Yellow_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Yellow_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Beard_Brown_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Brown_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Brown_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_Mike_Brown_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Brown_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Brown_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Npc");
	//	Dir.Move("NPC_WizBoy_Blue_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_WizBoy_Blue_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_WizBoy_Blue_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("Candle1Position");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Candle1Position.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Candle1Position.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("Candle2Position");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Candle2Position.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Candle2Position.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("Candle3Position");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Candle3Position.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Candle3Position.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("m_kevin_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("m_kevin_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("m_kevin_01.FBX"));
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("m_city_pigeon_01");

	//	GameEngineDirectory MeshDir = Dir;
	//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("m_city_pigeon_01.FBX"));
	//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("m_city_pigeon_01.FBX"));
	//}
}