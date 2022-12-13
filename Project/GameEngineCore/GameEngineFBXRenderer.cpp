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

// SetFbxMesh를 해서 만들어진 랜더 유니트를 사용하게 하기 위해서 리턴해준다.
std::shared_ptr<GameEngineRenderUnit> GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name,
	std::string _Material,
	size_t Index, 
	size_t _SubSetIndex /*= 0*/)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
		// 지금까지 만든거 다 날립니다.
	}

	if (Unit.empty())
	{
		Unit.resize(FBXMesh->GetRenderUnitCount());
		for (size_t i = 0; i < Unit.size(); i++)
		{
			int Count = FBXMesh->GetSubSetCount(i);

			Unit[i].resize(Count);
			for (size_t j = 0; j < Count; j++)
			{
				Unit[i][j] = std::make_shared<GameEngineRenderUnit>();
			}
		}
	}
	
	std::shared_ptr<GameEngineRenderUnit> RenderUnit = Unit[Index][_SubSetIndex];
	RenderUnit->SetMaterial(_Material);
	RenderUnit->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	RenderUnit->PushCamera();

	std::shared_ptr <GameEngineMesh> FbxMesh = FBXMesh->GetGameEngineMesh(Index, _SubSetIndex);
	RenderUnit->SetMesh(FbxMesh);

	if (RenderUnit->ShaderResources.IsTexture("DiffuseTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(Index, _SubSetIndex);

		if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
		{
			RenderUnit->ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
		}
	}

	return RenderUnit;
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

			std::shared_ptr<GameEngineRenderUnit> RenderUnit = Unit[j][0];
			if (RenderUnit->ShaderResources.IsTexture("DiffuseTexture"))
			{
				const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(j, 0);
				if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
				{
					RenderUnit->ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
				}
			}

			RenderUnit->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
		}
	}
}

void GameEngineFBXRenderer::SetSubMaterial(int _Index, const std::string& _Material)
{
	std::vector<std::shared_ptr<GameEngineRenderUnit>>& RenderUnit = Unit[_Index];

	for (size_t i = 0; i < RenderUnit.size(); i++)
	{
		RenderUnit[i]->SetMaterial(_Material);

		std::shared_ptr <GameEngineMesh> FbxMesh = FBXMesh->GetGameEngineMesh(_Index, i);
		RenderUnit[i]->SetMesh(FbxMesh);

		if (RenderUnit[i]->ShaderResources.IsTexture("DiffuseTexture"))
		{
			const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_Index, i);

			if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
			{
				RenderUnit[i]->ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
			}
		}

		RenderUnit[i]->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
		RenderUnit[i]->ShaderResources.SetConstantBufferLink("PixelData", &(PixelDatas[_Index]), sizeof(PixelData));
	}
	
	return;
}

void GameEngineFBXRenderer::SetSubConstantBufferLink(int _Index, const std::string& _Name, const void* _Data, UINT _Size)
{
	std::vector<std::shared_ptr<GameEngineRenderUnit>>& TmpUnits = Unit[_Index];
	for (size_t i = 0; i < TmpUnits.size(); i++)
	{
		TmpUnits[i]->ShaderResources.SetConstantBufferLink(_Name, _Data, _Size);
	}
}

void GameEngineFBXRenderer::Render(float _DeltaTime) 
{
	std::vector<std::shared_ptr<GameEngineRenderUnit>> TmpUnits;
	for (size_t UnitIndex = 0; UnitIndex < Unit.size(); UnitIndex++)
	{
		for (size_t SubSetIndex = 0; SubSetIndex < Unit[UnitIndex].size(); SubSetIndex++)
		{
			if (nullptr == Unit[UnitIndex][SubSetIndex]->GetMaterial())
			{
				continue;
			}
			if (Unit[UnitIndex][SubSetIndex]->GetMaterial()->GetName() == "GLASS")
			{
				TmpUnits.push_back(Unit[UnitIndex][SubSetIndex]);
				continue;
			}

			Unit[UnitIndex][SubSetIndex]->Render(_DeltaTime);
		}
	}

	for (size_t i = 0; i < TmpUnits.size(); i++)
	{
		TmpUnits[i]->Render(_DeltaTime);
	}
}
