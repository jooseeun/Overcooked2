#include "PreCompile.h"
#include "Overcooked.h"

#include "SelectStageLevel.h"
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
	//������ Hlsl ���� �ε�
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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Level");
		Dir.Move("1_1");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("1_1.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Level");
		Dir.Move("1_2");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("1_2.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Level");
		Dir.Move("1_3");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("1_3.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Level");
		Dir.Move("1_4");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("1_4.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("CounterTop");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_countertop_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("StaticObject");
		Dir.Move("CounterTop_Corner");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_lorry_countertop_corner_01.fbx"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

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

	// ���� ������Ʈ
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
		Dir.Move("Chef1");

		GameEngineDirectory MeshDir = Dir;
		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("AlienGreen_CarDeath.FBX"));
		std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Load(MeshDir.PlusFilePath("AlienGreen_CarDeath.FBX"));
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

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("MoveNPC_Beard_Waiter_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Dora_Civ_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("MoveNPC_Dora_Civ_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Hispanic_Yellow_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("MoveNPC_Hispanic_Yellow_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("MoveNPC_Mike_Civ_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("MoveNPC_Mike_Civ_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Asian_Blue_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Asian_Blue_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Green_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Beard_Green_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Waiter_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Beard_Waiter_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Beard_Yellow_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Beard_Yellow_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Dora_Civ_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Dora_Civ_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Dora_Orange_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Dora_Orange_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Dora_Wizard_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Dora_Wizard_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Blue_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_DoraBlonde_Blue_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Green_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_DoraBlonde_Green_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Orange_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_DoraBlonde_Orange_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Wizard_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_DoraBlonde_Wizard_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_DoraBlonde_Yellow_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_DoraBlonde_Yellow_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Ginger_Blue_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Ginger_Blue_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Ginger_Green_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Ginger_Green_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Hispanic_Brown_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Hispanic_Brown_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Hispanic_Orange_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Hispanic_Orange_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Hispanic_Wizard_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Hispanic_Wizard_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEastern_Waiter_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_MiddleEastern_Waiter_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEatern_Green_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_MiddleEatern_Green_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEatern_Orange_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_MiddleEatern_Orange_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_MiddleEatern_Wizard_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_MiddleEatern_Wizard_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Blue_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Mike_Blue_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Wizard_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Mike_Wizard_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Npc");
		Dir.Move("NPC_Mike_Yellow_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("NPC_Mike_Yellow_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		//GameEngineDirectory Dir;
		//Dir.MoveParentToExitsChildDirectory("ContentsResources");
		//Dir.Move("ContentsResources");
		//Dir.Move("Mesh");
		//Dir.Move("Object");
		//Dir.Move("Etc");
		//Dir.Move("exterior_car_blue_02");
		//
		//std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("exterior_car_blue_02.fbx"));
		//std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("exterior_car_green_01");

	//	GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("exterior_car_green_01.FBX"));
	//	std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	//}
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//	Dir.Move("ContentsResources");
	//	Dir.Move("Mesh");
	//	Dir.Move("Object");
	//	Dir.Move("Etc");
	//	Dir.Move("exterior_car_yellow_01");

	//	GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("exterior_car_yellow_01.FBX"));
	//	std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	//}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Candle1Position");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Candle1Position.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Candle2Position");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Candle2Position.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("Candle3Position");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Candle3Position.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
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

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_kevin_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Mesh");
		Dir.Move("Object");
		Dir.Move("Etc");
		Dir.Move("m_city_pigeon_01");

		std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_city_pigeon_01.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
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