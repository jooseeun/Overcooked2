#pragma once

// ���� :
class GameEngineNet
{
public:
	static void WindowNetStartUp();

public:
	// constrcuter destructer
	GameEngineNet();
	~GameEngineNet();

	// delete Function
	GameEngineNet(const GameEngineNet& _Other) = delete;
	GameEngineNet(GameEngineNet&& _Other) noexcept = delete;
	GameEngineNet& operator=(const GameEngineNet& _Other) = delete;
	GameEngineNet& operator=(GameEngineNet&& _Other) noexcept = delete;

	virtual int Send(const char* Data, size_t _Size);

protected:
	int Send(SOCKET _Socket, const char* Data, size_t _Size);

private:

};

