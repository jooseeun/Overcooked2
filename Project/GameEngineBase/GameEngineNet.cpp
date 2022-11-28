#include "PreCompile.h"
#include "GameEngineNet.h"
#include "GameEngineDebug.h"

GameEngineNet::GameEngineNet()
{
}

GameEngineNet::~GameEngineNet()
{
}

void GameEngineNet::WindowNetStartUp()
{
	static bool IsStart = false;

	if (true == IsStart)
	{
		return;
	}

	WSAData wsaData;
	int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (SOCKET_ERROR == errorCode)
	{
		MsgBoxAssert("winapi server socket startup fail");
		return;
	}

	IsStart = true;
}