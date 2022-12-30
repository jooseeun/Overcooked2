#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	None,
	ObjectUpdate, // 오브젝트 업데이트
	ObjectStart,
	LoadingData,  // 로딩레벨에서 사용하는 패킷 호스트, 클라 둘 다 사용
	UIUpdate,     // UI 업데이트
	ClinetInit,   // 클라이언트가 들어오면 서버가 보내줄 패킷.
	ChangeLevel,  // 레벨 변경 - 호스트만 전송
	ReadyLevel,   // 레벨 변경이 완료됨 - 게스트만 전송
	StartLevel,   // 레벨 시작 - 모든 게스트의 준비 신호를 받은후 호스트가 전송
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
	float LoadingVisual; //호스트, 클라가 일관적으로 동일한 값
	float LoadingReal;   // 이 값은 다를 수 있다.
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