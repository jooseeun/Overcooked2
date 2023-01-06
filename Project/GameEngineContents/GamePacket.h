#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

#include "Enums.h"

enum class ContentsPacketType
{
	None,
	ObjectUpdate, // ������Ʈ ������Ʈ
	ObjectStart,
	ObjectParentsSet,       // ��Ͼȵ� ������Ʈ ����
	ObjectParentsSetFrame,  // �� �����Ӹ��� üũ
	ObjectInteractUpdate,
	ObjectCookingGageUpdate,
	LoadingData,  // �ε��������� ����ϴ� ��Ŷ ȣ��Ʈ, Ŭ�� �� �� ���
	UIUpdate,     // UI ������Ʈ
	SelectStageInputData, //SelectStage ��ǲ ����ȭ
	ResultLevelInputData,
	RecipeTimeUpdate, // Host to Client : ������ �ð� ������ ������Ʈ
	CreateRecipeData,	//������ ����
	UserCount, //������ ��� ������ �ִ���
	ClinetInit,   // Ŭ���̾�Ʈ�� ������ ������ ������ ��Ŷ.
	ChangeLevel,  // ���� ���� - ȣ��Ʈ�� ����
	ReadyLevel,   // ���� ������ �Ϸ�� - �Խ�Ʈ�� ����
	StartLevel,   // ���� ���� - ��� �Խ�Ʈ�� �غ� ��ȣ�� ������ ȣ��Ʈ�� ����
	Ignore,
};

enum class ObjectToolType;
enum class ExceptionObject;
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

class ObjectCookingGagePacket : public GameServerPacket
{
public:
	int ObjectID = -1000;
	float CookingGage = 0;
	float4 float4_Index = float4::ZERO;
	int int_Index = -1;
	ObjectCookingGagePacket()
	{
		SetPacketID(ContentsPacketType::ObjectCookingGageUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser << CookingGage;
		_Ser << float4_Index;
		_Ser << int_Index;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> CookingGage;
		_Ser >> float4_Index;
		_Ser >> int_Index;
	}
};

class ObjectParentsSetPacket : public GameServerPacket     // ���ῡ �ǹ̸� �δ� ��Ŷ
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

class ObjectParentsSetAllFramePacket : public GameServerPacket     // ���ῡ �ǹ̸� �δ� ��Ŷ
{
public:
	int ParentsID = -10000;
	int ChildID = -1000;
	ObjectParentsSetAllFramePacket()
	{
		SetPacketID(ContentsPacketType::ObjectParentsSetFrame);
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
	int ObjectID = -1000;
	int HoldObjectID = -1000;
	float4 Pos;
	float4 Rot;
	float4 Scale;
	std::string Animation = "";
	ServerObjectType Type;
	ToolInfo ToolData = ToolInfo::None;
	MapObjType MapObjData = MapObjType::Max;
	IngredientType IngredientData = IngredientType::None;
	ObjectToolType ObjectToolData;
	ExceptionObject ExceptionData;

	ObjectStartPacket();

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser << HoldObjectID;
		_Ser << Pos;
		_Ser << Rot;
		_Ser << Scale;
		_Ser << Animation;
		_Ser.WriteEnum(Type);
		_Ser.WriteEnum(ToolData);
		_Ser.WriteEnum(MapObjData);
		_Ser.WriteEnum(IngredientData);
		_Ser.WriteEnum(ObjectToolData);
		_Ser.WriteEnum(ExceptionData);
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> HoldObjectID;
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> Scale;
		_Ser >> Animation;
		_Ser.ReadEnum(Type);
		_Ser.ReadEnum(ToolData);
		_Ser.ReadEnum(MapObjData);
		_Ser.ReadEnum(IngredientData);
		_Ser.ReadEnum(ObjectToolData);
		_Ser.ReadEnum(ExceptionData);
	}
};

class ObjectInteractUpdatePacket : public GameServerPacket
{
public:
	int ObjectID = -100;
	int PlayerNum = -100;
	int SendPacktPlayer = -100;
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
		_Ser << SendPacktPlayer;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser.ReadEnum(Type);
		_Ser >> ObjectID;
		_Ser >> PlayerNum;
		_Ser >> SendPacktPlayer;
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
	int PlayerCustomNum;
	int PlayerCountNum;
	int RendererState;
	int PlayerMove;
	int PlayerDeath;
	int IsCannon;
	int IsCannonFly;

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
		_Ser << PlayerCustomNum;
		_Ser << PlayerCountNum;
		_Ser << RendererState;
		_Ser << PlayerMove;
		_Ser << PlayerDeath;
		_Ser << IsCannon;
		_Ser << IsCannonFly;
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
		_Ser >> PlayerCustomNum;
		_Ser >> PlayerCountNum;
		_Ser >> RendererState;
		_Ser >> PlayerMove;
		_Ser >> PlayerDeath;
		_Ser >> IsCannon;
		_Ser >> IsCannonFly;
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
	float Recipe_0 = 0.f;
	float Recipe_1 = 0.f;
	float Recipe_2 = 0.f;
	float Recipe_3 = 0.f;
	float Recipe_4 = 0.f;
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
		_Ser << Recipe_0;
		_Ser << Recipe_1;
		_Ser << Recipe_2;
		_Ser << Recipe_3;
		_Ser << Recipe_4;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> LeftTime;
		_Ser >> IsReady_;
		_Ser >> Recipe_0;
		_Ser >> Recipe_1;
		_Ser >> Recipe_2;
		_Ser >> Recipe_3;
		_Ser >> Recipe_4;
	}
};

class RecipeTimeUpdatePacket : public GameServerPacket
{
public:
	float Recipe_0 = 0.f;
	float Recipe_1 = 0.f;
	float Recipe_2 = 0.f;
	float Recipe_3 = 0.f;
	float Recipe_4 = 0.f;
	RecipeTimeUpdatePacket()
	{
		SetPacketID(ContentsPacketType::RecipeTimeUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << Recipe_0;
		_Ser << Recipe_1;
		_Ser << Recipe_2;
		_Ser << Recipe_3;
		_Ser << Recipe_4;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> Recipe_0;
		_Ser >> Recipe_1;
		_Ser >> Recipe_2;
		_Ser >> Recipe_3;
		_Ser >> Recipe_4;
	}
};

class CreateRecipePacket : public GameServerPacket
{
public:
	int CreateFoodType; //Enum ����ȯ ����
public:
	CreateRecipePacket()
	{
		SetPacketID(ContentsPacketType::CreateRecipeData);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << CreateFoodType;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> CreateFoodType;
	}
};

class SelectStageInputDataPacket : public GameServerPacket
{
public:
	int InputBuffer; //Enum ����ȯ ����
public:
	SelectStageInputDataPacket()
	{
		SetPacketID(ContentsPacketType::SelectStageInputData);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << InputBuffer;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> InputBuffer;
	}
};

class ResultLevelInputDataPacket : public GameServerPacket
{
public:
	int InputBuffer; //Enum ����ȯ ����
public:
	ResultLevelInputDataPacket()
	{
		SetPacketID(ContentsPacketType::ResultLevelInputData);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << InputBuffer;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> InputBuffer;
	}
};

//class RequestHandOverPacket : public GameServerPacket
//{
//public:
//	int HandOverFoodType; //Enum ����ȯ ����
//public:
//	RequestHandOverPacket()
//	{
//		SetPacketID(ContentsPacketType::RequestHandOver);
//	}
//
//	virtual void Serialize(GameServerSerializer& _Ser)
//	{
//		GameServerPacket::Serialize(_Ser);
//		_Ser << HandOverFoodType;
//	}
//	virtual void DeSerialize(GameServerSerializer& _Ser)
//	{
//		GameServerPacket::DeSerialize(_Ser);
//		_Ser >> HandOverFoodType;
//	}
//};
//
//class OrderHandOverPacket : public GameServerPacket
//{
//public:
//	int HandOverFoodType; //Enum ����ȯ ����
//public:
//	OrderHandOverPacket()
//	{
//		SetPacketID(ContentsPacketType::OrderHandOver);
//	}
//
//	virtual void Serialize(GameServerSerializer& _Ser)
//	{
//		GameServerPacket::Serialize(_Ser);
//		_Ser << HandOverFoodType;
//	}
//	virtual void DeSerialize(GameServerSerializer& _Ser)
//	{
//		GameServerPacket::DeSerialize(_Ser);
//		_Ser >> HandOverFoodType;
//	}
//};

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

class UserCountPacket : public GameServerPacket
{
public:
	int Count;
	UserCountPacket()
	{
		SetPacketID(ContentsPacketType::UserCount);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << Count;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> Count;
	}
};