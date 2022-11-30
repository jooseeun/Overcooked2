#pragma once
#include "GameServerNet.h"
#include "GameEngineThread.h"

// Ό³Έν :
class GameServerNetServer : public GameServerNet
{
public:
	// constrcuter destructer
	GameServerNetServer();
	~GameServerNetServer();

	// delete Function
	//GameServerNetServer(const GameServerNetServer& _Other) = delete;
	//GameServerNetServer(GameServerNetServer&& _Other) noexcept = delete;
	//GameServerNetServer& operator=(const GameServerNetServer& _Other) = delete;
	//GameServerNetServer& operator=(GameServerNetServer&& _Other) noexcept = delete;

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

