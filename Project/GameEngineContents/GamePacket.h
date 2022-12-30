#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	None,
	ObjectUpdate, // ������Ʈ ������Ʈ
	ObjectStart,
	LoadingData,  // �ε��������� ����ϴ� ��Ŷ ȣ��Ʈ, Ŭ�� �� �� ���
	UIUpdate,     // UI ������Ʈ
	ClinetInit,   // Ŭ���̾�Ʈ�� ������ ������ ������ ��Ŷ.
	ChangeLevel,  // ���� ���� - ȣ��Ʈ�� ����
	ReadyLevel,   // ���� ������ �Ϸ�� - �Խ�Ʈ�� ����
	StartLevel,   // ���� ���� - ��� �Խ�Ʈ�� �غ� ��ȣ�� ������ ȣ��Ʈ�� ����
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

class ObjectStartPacket : public GameServerPacket
{
public:
	int ObjectID;
	float4 Pos;
	float4 Rot;
	float4 Scale;
	ServerObjectType Type;
	int HoldObjectID;
	ToolInfo ToolData = ToolInfo::None;
	MapObjType MapObjData = MapObjType::Max;
	IngredientType IngredientData = IngredientType::None;

	ObjectStartPacket()
	{
		SetPacketID(ContentsPacketType::ObjectStart);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser.WriteEnum(Type);
		_Ser << Pos;
		_Ser << Rot;
		_Ser << Scale;
		_Ser.WriteEnum(ToolData);
		_Ser.WriteEnum(MapObjData);
		_Ser.WriteEnum(IngredientData);
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser.ReadEnum(Type);
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> Scale;
		_Ser.ReadEnum(ToolData);
		_Ser.ReadEnum(MapObjData);
		_Ser.ReadEnum(IngredientData);
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
	//
	int HoldObjectID;
	float CookingGage;

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

class StartLevelPacket : public GameServerPacket
{
public:
	StartLevelPacket()
	{
		SetPacketID(ContentsPacketType::StartLevel);
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

class UIDataPacket : public GameServerPacket
{
public:
	int ObjectID = 0;
	float LeftTime = 0.f;
	int IsReady_ = 0; //bool
	UIDataPacket()
	{
		SetPacketID(ContentsPacketType::UIUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser << LeftTime;
		_Ser << IsReady_;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> LeftTime;
		_Ser >> IsReady_;
	}
};

class LoadingDataPacket : public GameServerPacket
{
public:
	int ObjectID;
	float LoadingVisual; //ȣ��Ʈ, Ŭ�� �ϰ������� ������ ��
	float LoadingReal;   // �� ���� �ٸ� �� �ִ�.
	LoadingDataPacket()
	{
		SetPacketID(ContentsPacketType::LoadingData);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser << LoadingVisual;
		_Ser << LoadingReal;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> LoadingVisual;
		_Ser >> LoadingReal;
	}
};