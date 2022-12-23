#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	None,
	ObjectUpdate, // 오브젝트 업데이트
	ClinetInit,   // 클라이언트가 들어오면 서버가 보내줄 패킷.
	ChangeLevel,  // 레벨 변경 - 호스트만 전송
	ReadyLevel,   // 레벨 변경이 완료됨 - 게스트만 전송
	LevelStart,   // 레벨 시작 - 모든 게스트의 준비 신호를 받은후 호스트가 전송
	Ignore,
};

class IgnorePacket : public GameServerPacket
{
public:
	IgnorePacket()
	{
		SetPacketID(ContentsPacketType::Ignore);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
	}
};

class ClientInitPacket : public GameServerPacket
{
public:
	int ObjectID;

	ClientInitPacket()
	{
		SetPacketID(ContentsPacketType::ClinetInit);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
	}
};

class ObjectUpdatePacket : public GameServerPacket
{
public:
	int ObjectID;
	ServerObjectType Type;
	ServerObjectBaseState State;
	float4 Pos;
	float4 Rot;
	float4 Scale;
	std::string Animation;
	int PlayerNum;
	int RendererState;

	ObjectUpdatePacket()
	{
		SetPacketID(ContentsPacketType::ObjectUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser.WriteEnum(Type);
		_Ser.WriteEnum(State);
		_Ser << Pos;
		_Ser << Rot;
		_Ser << Scale;
		_Ser << Animation;
		_Ser << PlayerNum;
		_Ser << RendererState;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser.ReadEnum(Type);
		_Ser.ReadEnum(State);
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> Scale;
		_Ser >> Animation;
		_Ser >> PlayerNum;
		_Ser >> RendererState;
	}
};

class ChangeLevelPacket : public GameServerPacket
{
public:
	std::string LevelName;

	ChangeLevelPacket()
	{
		SetPacketID(ContentsPacketType::ChangeLevel);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << LevelName;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> LevelName;
	}
};

class LevelStartPacket : public GameServerPacket
{
public:

	LevelStartPacket()
	{
		SetPacketID(ContentsPacketType::ChangeLevel);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
	}
};