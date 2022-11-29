#pragma once
#include "GameEngineNet.h"

// ���� :
class GameEngineNetClient : public GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNetClient();
	~GameEngineNetClient();

	// delete Function
	GameEngineNetClient(const GameEngineNetClient& _Other) = delete;
	GameEngineNetClient(GameEngineNetClient&& _Other) noexcept = delete;
	GameEngineNetClient& operator=(const GameEngineNetClient& _Other) = delete;
	GameEngineNetClient& operator=(GameEngineNetClient&& _Other) noexcept = delete;

	void Connect(const std::string& _Ip, int Port);

	int Send(const char* Data, size_t _Size) override;

protected:

private:
	SOCKET SessionSocket;

};
