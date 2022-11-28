#include "PreCompile.h"
#include "GameEngineNetServer.h"

GameEngineNetServer::GameEngineNetServer() 
{
}

GameEngineNetServer::~GameEngineNetServer() 
{
}

void GameEngineNetServer::Accept(int Port)
{
	GameEngineNet::WindowNetStartUp();

	SOCKADDR_IN Add;
	Add.sin_family = AF_INET; // ip4 аж╪р
	Add.sin_port = htons(Port);

	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
	{
		return;
	}

}

