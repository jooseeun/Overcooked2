#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"
#include <list>
#include <map>
#include "GameEngineActor.h"
#include "ShaderStruct.h"

enum class CAMERAORDER
{
	MAINCAMERA,
	USER0,
	USER1,
	USER2,
	USER3,
	USER4,
	USER5,
	USER6,
	USER7,
	UICAMERA,
	AboveUICAMERA
};

// 설명 : 화면(타이틀 화면, 플레이 화면, 인벤토리 화면)
class GameEngineCore;
class GameEngineActor;
class GameEngineCamera;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCollision;
class GameEngineCameraActor;
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend GameEngineCore;
	friend GameEngineActor;
	friend GameEngineCamera;
	friend GameEngineRenderer;
	friend GameEngineCollision;
	// 레벨이 현재까지 얼마나 켜져있었는지 시간을 잴수 있게 한다.

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	inline std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)];
	}

	inline std::shared_ptr<GameEngineCamera> GetUICamera()
	{
		return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)];
	}

	inline std::shared_ptr<GameEngineCamera> GetCamera(CAMERAORDER _Order)
	{
		return Cameras[static_cast<int>(_Order)];
	}

	std::shared_ptr<GameEngineCameraActor> GetMainCameraActor();

	GameEngineTransform& GetMainCameraActorTransform();

	std::shared_ptr<GameEngineCameraActor> GetUICameraActor();

	GameEngineTransform& GetUICameraActorTransform();

	std::shared_ptr<GameEngineCameraActor> GetCameraActor(CAMERAORDER _Order);

	//template<typename ReturnType, typename ActorType, typename GroupIndexType>
	//ReturnType* CreateActor(GroupIndexType _ObjectGroupIndex)
	//{
	//	return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	//}

	template<typename ActorType, typename GroupIndexType>
	std::shared_ptr<ActorType> CreateActor(GroupIndexType _ObjectGroupIndex)
	{
		return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ActorType>
	ActorType* CreateActor(const std::string _Name, int _ObjectGroupIndex = 0)
	{
		CreateActor(_ObjectGroupIndex);
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _ObjectGroupIndex = 0)
	{
		std::shared_ptr<GameEngineActor> NewActor = std::make_shared<ActorType>();
		NewActor->SetLevel(this);
		NewActor->SetOrder(_ObjectGroupIndex);
		NewActor->Start();

		PushActor(NewActor, _ObjectGroupIndex);

		// AllActors[_ObjectGroupIndex]게 사용하면
		// 없으면 만들어버리고 있으면
		// 찾아서 리턴해준다.

		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

	template<typename GroupIndexType>
	std::list<std::shared_ptr< GameEngineActor>> GetGroup(GroupIndexType _ObjectGroupIndex)
	{
		return AllActors[static_cast<int>(_ObjectGroupIndex)];
	}

	std::list<std::shared_ptr< GameEngineActor>> GetGroup(int _ObjectGroupIndex)
	{
		return AllActors[_ObjectGroupIndex];
	}

	template<typename ObjectType, typename GroupIndexType>
	std::list<std::shared_ptr< ObjectType>> GetConvertToGroup(GroupIndexType _ObjectGroupIndex)
	{
		return GetConvertToGroup<ObjectType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ObjectType>
	std::list<std::shared_ptr< ObjectType>> GetConvertToGroup(int _ObjectGroupIndex)
	{
		std::list<std::shared_ptr< ObjectType>> Result;
		for (std::shared_ptr<GameEngineActor>& Object : AllActors[_ObjectGroupIndex])
		{
			Result.push_back(std::dynamic_pointer_cast<ObjectType>(Object));
		}

		return Result;
	}

	void AllClear();

	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>& GetAllCollisions()
	{
		return AllCollisions;
	}

protected:

private:
	void PushActor(std::shared_ptr < GameEngineActor> _Actor, int _ObjectGroupIndex);

	void ActorLevelStartEvent();

	void ActorLevelEndEvent();

	void ActorUpdate(float _DelataTime);

	void LevelUpdate(float DeltaTime);

	void RemoveActor(std::shared_ptr < GameEngineActor> _Actor);

	void OverChildMove(GameEngineLevel* _NextLevel);

	void PushCamera(std::shared_ptr < GameEngineCamera> _Camera, CAMERAORDER _Order)
	{
		PushCamera(_Camera, static_cast<int>(_Order));
	}

	void PushRendererToMainCamera(std::shared_ptr < GameEngineRenderer> _Renderer)
	{
		PushRenderer(_Renderer, static_cast<int>(CAMERAORDER::MAINCAMERA));
	}

	void PushRendererToUICamera(std::shared_ptr < GameEngineRenderer> _Renderer)
	{
		PushRenderer(_Renderer, static_cast<int>(CAMERAORDER::UICAMERA));
	}

	void PushRenderer(std::shared_ptr < GameEngineRenderer> _Renderer, CAMERAORDER _Order)
	{
		PushRenderer(_Renderer, static_cast<int>(_Order));
	}

	void PushCamera(std::shared_ptr < GameEngineCamera> _Camera, int _CameraOrder);

	void PushRenderer(std::shared_ptr < GameEngineRenderer> _Renderer, int _CameraOrder);

	void PushCollision(std::shared_ptr < GameEngineCollision> _Collision, int _Order);

	void Render(float _DelataTime);

	void Release(float _DelataTime);

private:
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> AllActors;

	std::list<std::shared_ptr<GameEngineUpdateObject>> DeleteObject;

	std::vector<std::shared_ptr<GameEngineCamera>> Cameras;

	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>> AllCollisions;
};
