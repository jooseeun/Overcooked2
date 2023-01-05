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

	if (Packet->ObjectID == 4010) //ȣ��Ʈ���� ������ ��Ŷ�̶��
	{
		//Visual ���� ��� ��Ŷ�� Ŭ���̾�Ʈ�� ����
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
	else // Ŭ�� ȣ��Ʈ���� ������ ��Ŷ�̶��
	{
		//Real ���� ��� ��Ŷ�� ȣ��Ʈ�� ����
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

	//��
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

void ServerInitManager::SelectStageInputDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<SelectStageInputDataPacket> Packet = std::dynamic_pointer_cast<SelectStageInputDataPacket>(_Packet);
	for (int i = 4021;; i++)
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
