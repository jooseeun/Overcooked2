#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"

GameEngineFBXRenderer::GameEngineFBXRenderer() 
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer() 
{
}

void GameEngineFBXRenderer::Start()
{
	PushRendererToMainCamera();



}


void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, const std::string& _Material)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (GlobalIOManager::Load(IOType::Mesh, "_" + FindFBXMesh->GetNameCopy()))
	{
		MeshData Data = GlobalIOManager::GetMeshData();

		for (size_t j = 0; j < Data.PreviewMeshInfo_.size(); j++)
		{
			FindFBXMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTexturePath = Data.PreviewMeshInfo_[j].DifTexturePath_;
			FindFBXMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTextureName = Data.PreviewMeshInfo_[j].DifTextureName_;
		}
	}

	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(UnitCount); SubSetCount++)
		{
			SetFBXMesh(_Name, _Material, UnitCount, SubSetCount);
		}
	}
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(MeshIndex); SubSetCount++)
	{
		size_t SubSet = FindFBXMesh->GetSubSetCount(MeshIndex);

		SetFBXMesh(_Name, _Material, MeshIndex, SubSetCount);
	}
}

// SetFbxMesh�� �ؼ� ������� ���� ����Ʈ�� ����ϰ� �ϱ� ���ؼ� �������ش�.
GameEngineRenderUnit* GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name,
	std::string _Material,
	size_t Index, 
	size_t _SubSetIndex /*= 0*/)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

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
		// ���ݱ��� ����� �� �����ϴ�.
	}

	if (Unit.empty())
	{
		Unit.resize(FBXMesh->GetRenderUnitCount());
		for (size_t i = 0; i < Unit.size(); i++)
		{
			Unit[i].resize(FBXMesh->GetSubSetCount(i));
		}
	}
	
	GameEngineRenderUnit& RenderUnit = Unit[Index][_SubSetIndex];
	RenderUnit.SetPipeLine(_Material);


	std::shared_ptr <GameEngineMesh> FbxMesh = FBXMesh->GetGameEngineMesh(Index, _SubSetIndex);
	RenderUnit.SetMesh(FbxMesh);

	if (RenderUnit.ShaderResources.IsTexture("DiffuseTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(Index, _SubSetIndex);

		if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
		{
			RenderUnit.ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
		}
	}


	RenderUnit.SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	RenderUnit.ShaderResources.SetConstantBufferLink("PixelData", &GetPixelData(), sizeof(PixelData));

	return &RenderUnit;
}

void GameEngineFBXRenderer::ChangeLoadMaterial()
{
	if (nullptr == FBXMesh)
	{
		return;
	}

	if (GlobalIOManager::Load(IOType::Mesh, "_" + FBXMesh->GetNameCopy()) == true)
	{
		MeshData Data = GlobalIOManager::GetMeshData();


		for (size_t j = 0; j < Data.PreviewMeshInfo_.size(); j++)
		{
			FBXMesh->GetMaterialSettingData(j, 0).DifTexturePath = Data.PreviewMeshInfo_[j].DifTexturePath_;
			FBXMesh->GetMaterialSettingData(j, 0).DifTextureName = Data.PreviewMeshInfo_[j].DifTextureName_;


			GameEngineRenderUnit& RenderUnit = Unit[j][0];

			if (RenderUnit.ShaderResources.IsTexture("DiffuseTexture"))
			{
				const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(j, 0);
				if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
				{
					RenderUnit.ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
				}
			}



			RenderUnit.SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
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
