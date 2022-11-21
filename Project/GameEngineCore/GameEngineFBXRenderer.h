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
	virtual GameEngineRenderUnit* SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex, size_t _SubSetIndex);
	virtual void ChangeLoadMaterial();

	void Start() override;
	void Render(float _DeltaTime) override;

	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

	inline std::shared_ptr<GameEngineFBXMesh> GetFBXMesh() 
	{
		return FBXMesh;
	}

protected:

private:
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::vector<std::vector<GameEngineRenderUnit>> Unit;
	std::vector<PixelData> PixelDatas;


};

