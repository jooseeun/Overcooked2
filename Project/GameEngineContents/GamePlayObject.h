	#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "GamePlayPhysics.h"
#include "GameServerObject.h"
#include "GamePacket.h"

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

enum class ExceptionObject
{
	None = -1,
	MoveCar
};


class ObjectUpdatePacket;
class ObjectStartPacket;
class GamePlayMoveable;
class GamePlayStuff;
class Player;
class GamePlayObject : public GamePlayPhysics, public GameServerObject
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

	virtual SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable = nullptr, bool _FromNet = false) {
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
		Mesh_Object_->Off();
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
public:
	inline virtual void SetHighlightEffectOff()
	{
		GetFBXMesh()->SetAllPixelDataPlusColor(float4(0,0,0,0));
	}
	virtual inline void SetHighlightEffectOn()
	{
		GetFBXMesh()->SetAllPixelDataPlusColor(float4(0.2f, 0.2f, 0.2f, 0.0f));
	}
	// Sever
public:
	inline void DontWantSend()
	{
		InitFirst = true;
	}
	inline void WantSend()
	{
		InitFirst = false;
	}
	static inline int FindEmptyServerNumber()
	{
		GameServerObject* Object = nullptr;
		for (int i = ObjectNumberInServer_; ; i++)
		{
			Object = GameServerObject::GetServerObject(i);
			if (Object == nullptr)
			{
				ObjectNumberInServer_ = i;
				return ObjectNumberInServer_;
			}
		}
	}

	virtual void SetParentsServerHoldObject(int _ServerID) { MsgBoxAssert("GamePlayObject SetParentsServerHoldObject ���� �θ� ���� ����") };
	virtual void SetServerHoldObject(int _ServerID) { MsgBoxAssert("GamePlayObject SetServerHoldObject ���� �θ� ���� ����") };
	void ServerStart(int _ParentsID = -1000);
protected:
	virtual void ChildServerStart() {};

	void ServerUpdate(float _DeltaTime);
	

	//void SendParentObject();


	//virtual void SendPacket(std::shared_ptr<ObjectUpdatePacket> Packet) {}
	virtual int GetChildNetID() { return -1000; };
	virtual void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) {}

	virtual void SetDeleteChild() { MsgBoxAssert("GamePlayObject / SetDeleteChild() is not setting ") };
	virtual void SetChild(std::shared_ptr<GamePlayStuff> _Child) { MsgBoxAssert("GamePlayObject / SetChild() is not setting ") }
	virtual void SetServerCookingGage(std::shared_ptr<ObjectCookingGagePacket> _Packet) { SetServerCookingGage(_Packet->CookingGage); };
	virtual void SetServerCookingGage(float _Time) { MsgBoxAssert("GamePlayObject / SetServerCookingGage() is not setting ") };

	//std::shared_ptr<ObjectUpdatePacket> InteractPacket_;
	bool InitFirst;


	static int ObjectNumberInServer_;
};