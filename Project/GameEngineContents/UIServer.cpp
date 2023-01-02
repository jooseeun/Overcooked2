#include "PreCompile.h"
#include "ServerInitManager.h"
#include "GameEngineStatusWindow.h"
#include "GamePacket.h"
#include "Player.h"
#include "GlobalGameData.h"
#include "GamePlayObject.h"

void ServerInitManager::LoadingDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<LoadingDataPacket> Packet = std::dynamic_pointer_cast<LoadingDataPacket>(_Packet);

	if (Packet->ObjectID == 4010) //호스트에서 보내는 패킷이라면
	{
		//Visual 값이 담긴 패킷을 클라이언트에 전달
		for (int i = 4011;; i++)
		{
			GameServerObject* FindObject = GameServerObject::GetServerObject(i);
			if (FindObject == nullptr)
			{
				break;
			}
			else
			{
				if (FindObject->GetNetID() != i)
				{
					continue;
				}

				FindObject->PushPacket(Packet);
			}
		}
	}
	else // 클라가 호스트에게 보내는 패킷이라면
	{
		//Real 값이 담긴 패킷을 호스트에 전달
		GameServerObject* FindObject = GameServerObject::GetServerObject(4010);
		if (FindObject == nullptr)
		{
			return;
		}
		FindObject->PushPacket(Packet);
	}
}

void ServerInitManager::CreateRecipePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<CreateRecipePacket> Packet = std::dynamic_pointer_cast<CreateRecipePacket>(_Packet);

	//ㅂ
	for (int i = 4000;; i++)
	{
		GameServerObject* FindObject = GameServerObject::GetServerObject(i);
		if (FindObject == nullptr)
		{
			return;
		}

		if (FindObject->GetNetID() != i)
		{
			continue;
		}

		FindObject->PushPacket(Packet);
	}
}

void ServerInitManager::RequsetHandOverPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	//호스트가 받고 처리한다.
	std::shared_ptr<OrderHandOverPacket> Packet = std::dynamic_pointer_cast<OrderHandOverPacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(3999);
	if (FindObject == nullptr)
	{
		return;
	}
	FindObject->PushPacket(Packet);
}

void ServerInitManager::OrderHandOverPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	//클라가 받고 처리한다.

	std::shared_ptr<OrderHandOverPacket> Packet = std::dynamic_pointer_cast<OrderHandOverPacket>(_Packet);

	for (int i = 4000;; i++)
	{
		GameServerObject* FindObject = GameServerObject::GetServerObject(i);
		if (FindObject == nullptr)
		{
			return;
		}

		if (FindObject->GetNetID() != i)
		{
			continue;
		}

		FindObject->PushPacket(Packet);
	}
}