#pragma once
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineInstancingBuffer.h"

// ���� :
class GameEngineInstancing
{
public:
	static unsigned int MinInstancingCount;
	static unsigned int StartInstancingCount;

public:
	// constrcuter destructer
	GameEngineInstancing();
	~GameEngineInstancing();

	// delete Function
	GameEngineInstancing(const GameEngineInstancing& _Other) = delete;
	GameEngineInstancing(GameEngineInstancing&& _Other) noexcept = delete;
	GameEngineInstancing& operator=(const GameEngineInstancing& _Other) = delete;
	GameEngineInstancing& operator=(GameEngineInstancing&& _Other) noexcept = delete;


public:
	int DataInsert;
	std::vector<char> DataBuffer;
	GameEngineShaderResourcesHelper ShaderResources;
	std::shared_ptr<GameEngineRenderUnit> RenderUnit;
	int Size;
	unsigned int Count;
	int MaxDataCount;
	std::shared_ptr<GameEngineInstancingBuffer> Buffer;

	void InstancingBufferChangeData();

protected:

private:

};

