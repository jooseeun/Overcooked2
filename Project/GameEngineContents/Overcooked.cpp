#include "PreCompile.h"
#include "Overcooked.h"

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

	CreateLevel<SelectStageLevel>("SelectStage");
	CreateLevel<LoadingLevel>("LoadingLevel");

	CreateLevel<Stage_1_1>("Stage_1_1");
	CreateLevel<Stage_1_2>("Stage_1_2");
	CreateLevel<Stage_1_3>("Stage_1_3");
	CreateLevel<Stage_1_4>("Stage_1_4");
	CreateLevel<MapToolLevel>("MapToolLevel");
	CreateLevel<MeshToolLevel>("MeshToolLevel");
	CreateLevel<TitleLevel>("TitleLevel");

	ChangeLevel("Stage_1_1");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void Overcooked::LoadMaterial()
{
	//ƒ¡≈Ÿ√˜ Hlsl ∆ƒ¿œ ∑ŒµÂ
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
}

void Overcooked::Update(float _DeltaTime)
{
}

void Overcooked::End()
{
}

void Overcooked::MeshLoad()
{
	std::vector<std::string_view> TmpMeshs;
	TmpMeshs.push_back("Object\\StaticObject\\CounterTop\\m_sk_countertop_01.FBX");
	TmpMeshs.push_back("Object\\StaticObject\\CounterTop_Corner\\m_lorry_countertop_corner_01.FBX");
	GameEngineFBXMesh::LoadAll(TmpMeshs);

	std::vector<std::weak_ptr<GameEngineFBXMesh>> Test = GameEngineFBXMesh::LoadLevel("Level");

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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("CounterTop_NoEdge");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_countertop_no_edge_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("Sink");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_sink_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("FoodBox");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("CreateBox.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("TrashCan");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_bin_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("Servicehatch");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_dlc08_servicehatch_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("CounterTop_Wizard");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_wizard_countertop_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("CounterTop_Wizard");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_wizard_countertop_05.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("PlateReturn");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_plate_return_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Stuff");
		Dir.Move("Tool");
		Dir.Move("CuttingBoard");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("CuttingBoard.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Stuff");
		Dir.Move("Tool");
		Dir.Move("Plate");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_plate_02.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Stuff");
		Dir.Move("Tool");
		Dir.Move("Pot");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_pot_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Stuff");
		Dir.Move("Tool");
		Dir.Move("FryingPan");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_fryingpan_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Stuff");
		Dir.Move("Tool");
		Dir.Move("FireExtinguisher");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_fire_extinguisher_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("Cooker");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_cooker_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	// ∏ ≈¯ ø¿∫Í¡ß∆Æ
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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Chef");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("uuu.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("uuu.FBX"));
	}
	//Player Resource Animation ∑ŒµÂ
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Player");
		Dir.Move("AlienGreen");

		//{
		//	GameEngineDirectory MeshDir = Dir;
		//	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_Wash.FBX"));
		//	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_Wash.FBX"));
		//}
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

	}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Chef1");

	//	GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("ChefOriginal.FBX"));
	//	std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();

	//}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Beard_Orange_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Orange_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Orange_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Beard_Waiter_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Waiter_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Beard_Waiter_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Dora_Civ_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Dora_Civ_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Dora_Civ_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Hispanic_Yellow_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Hispanic_Yellow_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Hispanic_Yellow_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Mike_Civ_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("MoveNPC_Mike_Civ_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("MoveNPC_Mike_Civ_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Asian_Blue_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Asian_Blue_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Asian_Blue_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Green_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Green_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Green_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Waiter_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Waiter_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Waiter_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Yellow_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Yellow_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Yellow_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Dora_Civ_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Dora_Civ_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Dora_Civ_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Dora_Orange_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Dora_Orange_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Dora_Orange_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Dora_Wizard_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Dora_Wizard_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Dora_Wizard_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Blue_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Blue_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Blue_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Green_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Green_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Green_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Orange_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Orange_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Orange_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Wizard_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Wizard_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Wizard_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Yellow_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Yellow_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_DoraBlonde_Yellow_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Ginger_Blue_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Ginger_Blue_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Ginger_Blue_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Ginger_Green_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Ginger_Green_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Ginger_Green_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Hispanic_Brown_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Hispanic_Brown_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Hispanic_Brown_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Hispanic_Orange_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Hispanic_Orange_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Hispanic_Orange_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Hispanic_Wizard_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Hispanic_Wizard_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Hispanic_Wizard_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEastern_Waiter_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEastern_Waiter_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEastern_Waiter_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEatern_Green_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Green_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Green_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEatern_Orange_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Orange_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Orange_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEatern_Wizard_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Wizard_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_MiddleEatern_Wizard_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Blue_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Blue_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Blue_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Wizard_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Wizard_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Wizard_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Yellow_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Yellow_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Yellow_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Brown_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Beard_Brown_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Beard_Brown_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Brown_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_Mike_Brown_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_Mike_Brown_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_WizBoy_Blue_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("NPC_WizBoy_Blue_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("NPC_WizBoy_Blue_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Candle1Position");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Candle1Position.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Candle1Position.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Candle2Position");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Candle2Position.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Candle2Position.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Candle3Position");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Candle3Position.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("Candle3Position.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("exterior_grass_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("exterior_grass_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("m_kevin_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("m_kevin_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("m_kevin_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("m_city_pigeon_01");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("m_city_pigeon_01.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("m_city_pigeon_01.FBX"));
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("traffic_light_animated_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("traffic_light_animated_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Bamboo2");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Bamboo2.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Car_Blue");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Car_Blue.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Car_Bluegreen");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Car_Bluegreen.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Car_Green");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Car_Green.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Car_Yellow");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Car_Yellow.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
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
	}

	{
		//InGame UI
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
}