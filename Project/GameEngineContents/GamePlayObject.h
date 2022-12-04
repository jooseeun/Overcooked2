	#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "GamePlayPhysics.h"
// ���� :
enum class ObjectType
{
	None,
	StaticObject, // ��ȣ�ۿ� �Ұ���
	Stuff,        // ���, ����
	Character,    // �÷��̾�
};

enum class SetPlayerState_Return
{
	Nothing,
	Using
};



class GamePlayMoveable;
class Player;
class GamePlayObject : public GamePlayPhysics
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

	virtual SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type) {
		MsgBoxAssert("���� �������� �ʾҽ��ϴ�");
		return SetPlayerState_Return::Nothing;
	};
	

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

	std::shared_ptr<GameEngineFBXStaticRenderer> ChangeFBXMesh()
	{
		Mesh_Object_->Death();
		Mesh_Object_ = CreateComponent<GameEngineFBXStaticRenderer>("Mesh_Object");
		return Mesh_Object_;
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
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayObject::Enum_ObjectType_ ����)");
		}
		return Enum_ObjectType_;
	}



private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Mesh_Object_;
	std::shared_ptr<GameEngineFBXAnimationRenderer> AnimationMesh_Obejct_;
	std::shared_ptr<GameEngineCollision> Collision_Object_;

	ObjectType Enum_ObjectType_;

	//PhysicCollision PhysicCollision_;

	// Effect
private:
	bool BloomEffect_;
public:
	inline virtual void SetHighlightEffectOff()
	{
		GetFBXMesh()->SetAllPixelDataPlusColor(float4(0,0,0,0));

		BloomEffect_ = false;
	}
	virtual inline void SetHighlightEffectOn()
	{
		GetFBXMesh()->SetAllPixelDataPlusColor(float4(0.2f, 0.2f, 0.2f, 0.0f));

		BloomEffect_ = true;
	}
	inline bool GetBloomEffect()
	{
		return BloomEffect_;
	}
	//

};
