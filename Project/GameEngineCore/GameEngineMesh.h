#pragma once
#include <string.h>
#include "GameEngineRes.h"

// 설명 :
class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineMesh : public GameEngineRes<GameEngineMesh>
{
public:
	static GameEngineMesh* Create(const std::string& _Name);

	static GameEngineMesh* Create(const std::string& _Name, const std::string& _Vtx, const std::string& _Idx);

	static GameEngineMesh* Create(GameEngineVertexBuffer* _Vtx, GameEngineIndexBuffer* _Idx);

public:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	void SetInputAssembler1VertexBuffer(const std::string& _Name);
	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	void SetInputAssembler1VertexBuffer(GameEngineVertexBuffer* _Res);
	void SetInputAssembler2IndexBuffer(GameEngineIndexBuffer* _Res);

	void InputAssembler1VertexBufferSetting();

	void InputAssembler2IndexBufferSetting();

	void Setting();

	void Render();

	const class GameEngineLayOutDesc& GetLayOutDesc();

protected:

private:
	GameEngineVertexBuffer* VertexBuffer; // 인풋어셈블러1 세팅
	// HLSL이라는 다른 언어를 사용하는 단계에요.
	// HLSL은 그래픽카드에 특정 데이터에 대한 처리 단계를 우리가 직접 작성해서
	// 그래픽카드에 올려줄수 있는 겁니다.
	GameEngineIndexBuffer* IndexBuffer; // 인풋어셈블러2 세팅

};

