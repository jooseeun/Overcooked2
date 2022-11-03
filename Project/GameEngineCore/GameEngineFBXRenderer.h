#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineFBXMesh.h"

// Ό³Έν :
class GameEngineFBXRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	~GameEngineFBXRenderer();

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _Name, std::string _PipeLine);
	void SetFBXMesh(const std::string& _Name, std::string _PipeLine, size_t _MeshIndex, size_t _SubSetIndex = 0);

	void Render(float _DeltaTime) override;

	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

	GameEngineFBXMesh* GetFBXMesh()
	{
		return FBXMesh;
	}

	void CreateAnimation(const std::string& _AnimationName, const std::string& _MeshFBX, const std::string& _AnimationFBX);

protected:

private:
	GameEngineFBXMesh* FBXMesh;

	std::vector<std::vector<GameEngineRenderUnit>> Unit;

};

