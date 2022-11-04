#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

// 설명 :
enum class ObjectType
{
	None,
	StaticObject, // 상호작용 불가능
	Stuff,        // 재료, 도구
	Character,    // 플레이어
};

enum class Input_PickUpOption
{
	NoResponse,
	PickUp,
};

class GamePlayMoveable;
class GamePlayObject : public GameEngineActor
{
protected:
	GamePlayObject();

public:
	// constrcuter destructer
	virtual ~GamePlayObject();

	// delete Function
	GamePlayObject(const GamePlayObject& _Other) = delete;
	GamePlayObject(GamePlayObject&& _Other) noexcept = delete;
	GamePlayObject& operator=(const GamePlayObject& _Other) = delete;
	GamePlayObject& operator=(GamePlayObject&& _Other) noexcept = delete;

	virtual Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) { return Input_PickUpOption::NoResponse; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:
	inline void SetObjectType(ObjectType _Type)
	{
		Enum_ObjectType_ = _Type;
	}

	inline ObjectType GetObjectType() const
	{
		if (Enum_ObjectType_ == ObjectType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayObject::Enum_ObjectType_ 설정)");
		}
		return Enum_ObjectType_;
	}

	inline GameEngineFBXStaticRenderer* GetFBXMesh() const
	{
		return Mesh_Object_;
	}


	inline GameEngineCollision* GetCollisionObject() const
	{
		return Collision_Object_;
	}

private:
	GameEngineFBXStaticRenderer* Mesh_Object_;
	GameEngineCollision* Collision_Object_;

	ObjectType Enum_ObjectType_;

};

