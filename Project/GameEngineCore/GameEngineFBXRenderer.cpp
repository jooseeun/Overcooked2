#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"
#include "GlobalIOManager.h"

GameEngineFBXRenderer::GameEngineFBXRenderer()
	: FBXMesh(nullptr)
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer()
{
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _Material)
{
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(UnitCount); SubSetCount++)
		{
			SetFBXMesh(_Name, _Material, UnitCount, SubSetCount);
		}
	}
}

GameEngineRenderUnit* GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex)
{
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_Name);
	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�������� �ʴ� FBXMesh�� �����߽��ϴ�.");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
	}

	if (Unit.empty())
	{
		Unit.resize(FBXMesh->GetRenderUnitCount());
		for (size_t i = 0; i < Unit.size(); i++)
		{
			Unit[i].resize(FBXMesh->GetSubSetCount(i));
		}
	}

	GameEngineRenderUnit& RenderUnit = Unit[_MeshIndex][_SubSetIndex];
	RenderUnit.SetPipeLine(_Material);

	GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(_MeshIndex, _SubSetIndex);
	RenderUnit.SetMesh(FbxMesh);

	if (RenderUnit.ShaderResources.IsTexture("DiffuseTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_MeshIndex, _SubSetIndex);
		if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
		{
			RenderUnit.ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
		}
	}

	RenderUnit.SetRenderer(this);
	return &RenderUnit;
}

void GameEngineFBXRenderer::ChangeLoadMaterial()
{
	if (nullptr == FBXMesh)
	{
		return;
	}

	//GlobalIOManager::Load(IOType::Mesh, FBXMesh->GetName().data());
	//MeshData Data = GlobalIOManager::GetMeshData();
	//for (size_t i = 0; i < Data.PreviewMeshInfo_.size(); i++)
	//{
	//	FBXMesh->GetMaterialSettingData(0, i).DifTexturePath = Data.PreviewMeshInfo_[i].DifTexturePath_;
	//	FBXMesh->GetMaterialSettingData(0, i).DifTextureName = Data.PreviewMeshInfo_[i].DifTextureName_;
	//}




	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (int i = 0; i < AllFile.size(); ++i)
	{
		std::string FileName = AllFile[i].GetFileName();
		std::string FbxName = FBXMesh->GetName().data();
		if (FileName.find(FbxName) != std::string::npos)
		{

			
			GlobalIOManager::Load(IOType::Mesh, "_" + FBXMesh->GetNameCopy());
			MeshData Data = GlobalIOManager::GetMeshData();


			for (size_t j = 0;j < Data.PreviewMeshInfo_.size(); j++)
			{
				FBXMesh->GetMaterialSettingData(j, 0).DifTexturePath = Data.PreviewMeshInfo_[j].DifTexturePath_;
				FBXMesh->GetMaterialSettingData(j, 0).DifTextureName = Data.PreviewMeshInfo_[j].DifTextureName_;


				GameEngineRenderUnit& RenderUnit = Unit[j][0];
				RenderUnit.SetPipeLine("Texture");

				GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(j, 0);
				RenderUnit.SetMesh(FbxMesh);

				if (RenderUnit.ShaderResources.IsTexture("DiffuseTexture"))
				{
					const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(j, 0);
					if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
					{
						RenderUnit.ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
					}
				}

				RenderUnit.SetRenderer(this);
			
			}
			break;
		}

		else
		{
			continue;
		}


	}
}

void GameEngineFBXRenderer::Render(float _DeltaTime)
{
	for (size_t UnitIndex = 0; UnitIndex < Unit.size(); UnitIndex++)
	{
		for (size_t SubSetIndex = 0; SubSetIndex < Unit[UnitIndex].size(); SubSetIndex++)
		{
			if (nullptr == Unit[UnitIndex][SubSetIndex].GetPipeLine())
			{
				continue;
			}

			Unit[UnitIndex][SubSetIndex].Render(_DeltaTime);
		}
	}
}
