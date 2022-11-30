#pragma once

// ���� :
class GameServerPacket : public std::enable_shared_from_this<GameServerPacket>
{
public:
	// constrcuter destructer
	GameServerPacket();
	~GameServerPacket();

	// delete Function
	GameServerPacket(const GameServerPacket& _Other) = delete;
	GameServerPacket(GameServerPacket&& _Other) noexcept = delete;
	GameServerPacket& operator=(const GameServerPacket& _Other) = delete;
	GameServerPacket& operator=(GameServerPacket&& _Other) noexcept = delete;

	int PacketID; // ��Ŷ�� ����
	int Size; // ��Ŷ�� ũ��

	void DataInput()
	{
	}

protected:

private:

};

