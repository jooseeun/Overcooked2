#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"

GameEngineFBXRenderer::GameEngineFBXRenderer()
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer()
{
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _PipeLine)
{
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(UnitCount); SubSetCount++)
		{
			SetFBXMesh(_Name, _PipeLine, UnitCount, SubSetCount);
		}
	}
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _PipeLine, size_t _MeshIndex, size_t _SubSetIndex)
{
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_Name);
	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return;
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
	RenderUnit.SetPipeLine(_PipeLine);

	GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(_MeshIndex, _SubSetIndex);
	RenderUnit.SetMesh(FbxMesh);

	if (RenderUnit.ShaderResources.IsTexture("DiffuseTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_MeshIndex, _SubSetIndex);

		RenderUnit.ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
	}

	RenderUnit.SetRenderer(this);
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

void GameEngineFBXRenderer::CreateAnimation(const std::string& _AnimationName, const std::string& _MeshFBX, const std::string& _AnimationFBX)
{
}
