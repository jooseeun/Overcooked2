#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

#include "Enums.h"

enum class ContentsPacketType
{
	None,
	ObjectUpdate, // 오브젝트 업데이트
	ObjectStart,
	ObjectParentsSet,       // 등록안된 오브젝트 연결
	ObjectParentsSetFrame,  // 매 프레임마다 체크
	ObjectInteractUpdate,
	ObjectCookingGageUpdate,
	LoadingData,  // 로딩레벨에서 사용하는 패킷 호스트, 클라 둘 다 사용
	UIUpdate,     // UI 업데이트
	SelectStageInputData, //SelectStage 인풋 동기화
	ResultLevelInputData,
	RecipeTimeUpdate, // Host to Client : 레시피 시간 데이터 업데이트
	CreateRecipeData,	//레시피 생성
	UserCount, //유저가 몇명 접속해 있는지
	ClinetInit,   // 클라이언트가 들어오면 서버가 보내줄 패킷.
	ChangeLevel,  // 레벨 변경 - 호스트만 전송
	ReadyLevel,   // 레벨 변경이 완료됨 - 게스트만 전송
	StartLevel,   // 레벨 시작 - 모든 게스트의 준비 신호를 받은후 호스트가 전송
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

class ObjectParentsSetPacket : public GameServerPacket     // 연결에 의미를 두는 패킷
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

class ObjectParentsSetAllFramePacket : public GameServerPacket     // 연결에 의미를 두는 패킷
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
	int CreateFoodType; //Enum 형변환 ㄱㄱ
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
	int InputBuffer; //Enum 형변환 ㄱㄱ
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
	int InputBuffer; //Enum 형변환 ㄱㄱ
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
//	int HandOverFoodType; //Enum 형변환 ㄱㄱ
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
//	int HandOverFoodType; //Enum 형변환 ㄱㄱ
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