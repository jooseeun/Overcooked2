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


	void Accept(int Port);

	int Send(const char* Data, size_t _Size) override
	{
		return 0;
	}

	int SendPacket(std::shared_ptr<GameServerPacket> _Packet) override;

	std::function<void(SOCKET)> AcceptCallBack;

	inline std::vector<SOCKET>& GetUserSockets()
	{
		return UserSockets;
	}

	inline std::vector<bool>& GetReadyLevels()
	{
		return ReadyLevels;
	}

protected:

private:
	std::atomic<bool> IsRun;

	SOCKET ServerAccpetSocket;

	GameEngineThread AcceptThread;

	std::vector<bool> ReadyLevels;
	std::vector<SOCKET> UserSockets;
	std::vector<std::shared_ptr<GameEngineThread>> UserThreads;

	void AcceptFunction(GameEngineThread* Thread);

	void UserFunction(GameEngineThread* Thread, SOCKET _Socket);

};

