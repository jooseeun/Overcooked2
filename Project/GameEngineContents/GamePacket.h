#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	None,
	ObjectUpdate, // ������Ʈ ������Ʈ
	ObjectStart,
	ObjectParentsSet,
	ObjectInteractUpdate,
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

class ObjectParentsSetPacket : public GameServerPacket
{
public:
	int ParentsID = -10000;
	int ChildID = -10000;
	ObjectParentsSetPacket()
	{
		SetPacketID(ContentsPacketType::ObjectParentsSet);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ParentsID;
		_Ser << ChildID;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ParentsID;
		_Ser >> ChildID;
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
	int HoldObjectID;
	float4 Pos;
	float4 Rot;
	float4 Scale;
	ServerObjectType Type;
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
		_Ser << HoldObjectID;
		_Ser << Pos;
		_Ser << Rot;
		_Ser << Scale;
		_Ser.WriteEnum(Type);
		_Ser.WriteEnum(ToolData);
		_Ser.WriteEnum(MapObjData);
		_Ser.WriteEnum(IngredientData);
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> HoldObjectID;
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> Scale;
		_Ser.ReadEnum(Type);
		_Ser.ReadEnum(ToolData);
		_Ser.ReadEnum(MapObjData);
		_Ser.ReadEnum(IngredientData);
	}
};

class ObjectInteractUpdatePacket : public GameServerPacket
{
public:
	int ObjectID = -100;
	int PlayerNum = -100;
	PlayerCurStateType Type;
	//

	ObjectInteractUpdatePacket()
	{
		SetPacketID(ContentsPacketType::ObjectInteractUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser.WriteEnum(Type);
		_Ser << ObjectID;
		_Ser << PlayerNum;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser.ReadEnum(Type);
		_Ser >> ObjectID;
		_Ser >> PlayerNum;
	}
};

class ObjectUpdatePacket : public GameServerPacket
{
public:
	int ObjectID;
	ServerObjectType Type;
	ServerObjectBaseState State = ServerObjectBaseState::Base;
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
	UIDataPacket()
	{
		SetPacketID(ContentsPacketType::UIUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << LeftTime;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> LeftTime;
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