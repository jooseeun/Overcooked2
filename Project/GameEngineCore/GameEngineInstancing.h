#pragma once
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineInstancingBuffer.h"

// Ό³Έν :
class GameEngineRenderUnit;
class GameEngineInstancing
{
public:
	// constrcuter destructer
	GameEngineInstancing();
	~GameEngineInstancing();

	// delete Function
	GameEngineInstancing(const GameEngineInstancing& _Other) = delete;
	GameEngineInstancing(GameEngineInstancing&& _Other) noexcept = delete;
	GameEngineInstancing& operator=(const GameEngineInstancing& _Other) = delete;
	GameEngineInstancing& operator=(GameEngineInstancing&& _Other) noexcept = delete;

	void PushUnit(std::shared_ptr<GameEngineRenderUnit> _Unit);

private:
	std::vector<char> DataBuffer;
	int Size;
	unsigned int Count;
	int MaxDataCount;
	std::shared_ptr<GameEngineInstancingBuffer> Buffer;


	GameEngineShaderResourcesHelper ShaderResources;
	std::shared_ptr<GameEngineRenderUnit> InitUnit;

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> Units;

	void InstancingBufferChangeData();

};