#pragma once
#include "GameEngineNet.h"
#include "GameEngineThread.h"

// Ό³Έν :
class GameEngineNetServer : public GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNetServer();
	~GameEngineNetServer();

	// delete Function
	//GameEngineNetServer(const GameEngineNetServer& _Other) = delete;
	//GameEngineNetServer(GameEngineNetServer&& _Other) noexcept = delete;
	//GameEngineNetServer& operator=(const GameEngineNetServer& _Other) = delete;
	//GameEngineNetServer& operator=(GameEngineNetServer&& _Other) noexcept = delete;

	void Accept(int Port);

protected:


private:
	std::atomic<bool> IsRun;

	SOCKET ServerAccpetSocket;

	GameEngineThread AcceptThread;

	std::vector<SOCKET> UserSockets;
	std::vector<GameEngineThread> UserThreads;

	void AcceptFunction(GameEngineThread* Thread);

	void UserFunction(GameEngineThread* Thread, SOCKET _Socket);

};

