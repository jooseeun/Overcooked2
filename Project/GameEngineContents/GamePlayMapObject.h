#pragma once
#include "GamePlayObject.h"
#include "GamePacket.h"
// Ό³Έν :
class GamePlayMapObject : public GamePlayObject
{
	friend class MapEditorWindow;

public:
	// constrcuter destructer
	GamePlayMapObject();
	~GamePlayMapObject();

	// delete Function
	GamePlayMapObject(const GamePlayMapObject& _Other) = delete;
	GamePlayMapObject(GamePlayMapObject&& _Other) noexcept = delete;
	GamePlayMapObject& operator=(const GamePlayMapObject& _Other) = delete;
	GamePlayMapObject& operator=(GamePlayMapObject&& _Other) noexcept = delete;

public:
	inline MapObjType GetMapObjType()
	{
		return ObjType_;
	}

	inline void SetMapObjType(MapObjType _ObjType)
	{
		ObjType_ = _ObjType;
	}

	void SetMapObjectMesh(const std::string& _Name, MapObjType _ObjType);

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:
	MapObjType ObjType_;

	void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override
	{
		switch (GetMapObjType())
		{
		case MapObjType::Lift:
		//case MapObjType::Car:
		//	break;
		//case MapObjType::TrafficLight:
		//	break;
		case MapObjType::Portal_Blue:
		case MapObjType::Portal_Purple:
		case MapObjType::IcePlatform:
			Packet->MapObjData = ObjType_;
			break;
		default:
			Packet->MapObjData = MapObjType::Max;
			break;
		}


	}

};

