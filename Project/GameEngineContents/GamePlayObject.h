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


struct PhysicCollision
{

};

class GamePlayMoveable;
class Player;
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

	virtual Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) { return Input_PickUpOption::NoResponse; }
	virtual Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) { return Input_PickUpOption::NoResponse; }

	inline std::shared_ptr<GameEngineFBXStaticRenderer> GetFBXMesh() const
	{
		return Mesh_Object_;
	}

	inline std::shared_ptr<GameEngineFBXAnimationRenderer> GetAnimationFBXMesh() const
	{
		return AnimationMesh_Obejct_;
	}

	inline std::shared_ptr<GameEngineCollision> GetCollisionObject() const
	{
		return Collision_Object_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
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

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Mesh_Object_;
	std::shared_ptr<GameEngineFBXAnimationRenderer> AnimationMesh_Obejct_;
	std::shared_ptr<GameEngineCollision> Collision_Object_;

	ObjectType Enum_ObjectType_;


	// Physics
	CollisionReturn CheckCollisionObjectByPhysics_Enter(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn CheckCollisionMapObjectByPhysics_Enter(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	static void CalculatorPhysic(std::weak_ptr<GamePlayObject> _ObjectA, std::weak_ptr<GamePlayObject> _ObjectB);
	static void CalculatorPhysicByMapobject(std::weak_ptr<GamePlayObject> _Object, std::weak_ptr<GamePlayObject> _MapObject);
	float4 Vector_;
	float4 External_Vector_;

	//PhysicCollision PhysicCollision_;

	// Effect
private:
	bool BloomEffect_;
public:
	inline virtual void SetBloomEffectOff()
	{
		GetFBXMesh()->RenderOptionInst.IsHighlight = 0;

		BloomEffect_ = false;
	}
	virtual inline void SetBloomEffectOn()
	{
		GetFBXMesh()->RenderOptionInst.IsHighlight = 1;

		BloomEffect_ = true;
	}
	inline bool GetBloomEffect()
	{
		return BloomEffect_;
	}
	//

};
