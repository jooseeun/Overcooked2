#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineFBXMesh.h"

// ���� :
class GameEngineFBXRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	virtual ~GameEngineFBXRenderer() = 0;

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	virtual void SetFBXMesh(const std::string& _Name) = 0;
	virtual void SetFBXMesh(const std::string& _Name, const std::string& _Material);
	virtual void SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex);
	virtual std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex, size_t _SubSetIndex);
	virtual void ChangeLoadMaterial();

	virtual void SetSubMaterial(int _Index, const std::string& _Material);
	virtual void SetSubConstantBufferLink(int _Index, const std::string& _Name, const void* _Data, UINT _Size);

	void Start() override;
	void Render(float _DeltaTime) override;

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& GetAllRenderUnit()
	{
		return Unit;
	}

	inline std::shared_ptr<GameEngineFBXMesh> GetFBXMesh() 
	{
		return FBXMesh;
	}

	PixelData& GetPixelDatas(int _Index)
	{
		return PixelDatas[_Index];
	}

	void SetAllPixelDataAlphaColor(float4 _Data)
	{
		for (int i = 0; i < PixelDatas.size(); ++i)
		{
			PixelDatas[i].AlphaColor = _Data;
		}
	}

	void SetAllPixelDataAlphaFlag(bool _Data)
	{
		for (int i = 0; i < PixelDatas.size(); ++i)
		{
			PixelDatas[i].AlphaFlag = _Data;
		}
	}

	void SetAllPixelDataPlusColor(float4 _Data)
	{
		for (int i = 0; i < PixelDatas.size(); ++i)
		{
			PixelDatas[i].PlusColor = _Data;
		}
	}

protected:

private:
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> Unit;
	std::vector<PixelData> PixelDatas;
};

