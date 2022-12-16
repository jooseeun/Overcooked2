#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

// Ό³Έν :
class GameEngineMaterial;
class GameEngineDefaultRenderer 
	: public GameEngineRenderer
{
public:

	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

	// delete Function
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);

	void SetMesh(const std::string& _Name);
	void SetMaterial(const std::string& _Name);

	inline GameEngineShaderResourcesHelper& GetShaderResources()
	{
		return Unit->ShaderResources;
	}

	inline std::shared_ptr<GameEngineRenderUnit> GetRenderUnit()
	{
		return Unit;
	}

protected:

	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	std::shared_ptr<GameEngineRenderUnit> Unit;

};

