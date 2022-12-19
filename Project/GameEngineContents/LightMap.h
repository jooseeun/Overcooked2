#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameServerObject.h"

// Ό³Έν :
class LightMap : public GameEngineActor, public GameServerObject
{
public:
	// constrcuter destructer
	LightMap();
	~LightMap();

	// delete Function
	LightMap(const LightMap& _Other) = delete;
	LightMap(LightMap&& _Other) noexcept = delete;
	LightMap& operator=(const LightMap& _Other) = delete;
	LightMap& operator=(LightMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	std::shared_ptr<GameEngineTextureRenderer> Renderer;

private:
	float4 ResultColor;

};
