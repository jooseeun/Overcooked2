#pragma once
#include "GameServerNet.h"
#include "GameEngineThread.h"
#include "GameServerDispatcher.h"

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

	int Send(const char* Data, size_t _Size) 
	{
		return 0;
	}

	int SendPacket(std::shared_ptr<GameServerPacket> _Packet) 
	{
		return 0;
	}

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

