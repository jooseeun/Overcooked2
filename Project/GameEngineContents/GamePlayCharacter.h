#pragma once
#include "GamePlayObject.h"

// ���� :
class GamePlayMoveable;
class GamePlayStaticObject;
class GamePlayCharacter : public GamePlayObject
{
public:
	// constrcuter destructer
	GamePlayCharacter();
	~GamePlayCharacter();

	// delete Function
	GamePlayCharacter(const GamePlayCharacter& _Other) = delete;
	GamePlayCharacter(GamePlayCharacter&& _Other) noexcept = delete;
	GamePlayCharacter& operator=(const GamePlayCharacter& _Other) = delete;
	GamePlayCharacter& operator=(GamePlayCharacter&& _Other) noexcept = delete;


	inline Input_PickUpOption Input_PickUp(GamePlayCharacter* _Player) override { return Input_PickUpOption::NoResponse; }
	inline Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) override
	{
		Moveable_Current_ = _Object;
		//	Moveable_Current_->SetBloomEffectOff();
		return Input_PickUpOption::PickUp;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:
	inline GameEngineCollision* GetInteractCollision() const
	{
		return Collision_Interact_;
	}


	// ��ȣ�ۿ� ��ư
	void Input_PickUpButton();


	// ��� �ִ� ������Ʈ
private:
	GamePlayMoveable* Moveable_Current_;      




	// Interact Collision
private:
	GameEngineCollision* Collision_Interact_; // ��ȣ�ۿ� �ݸ���
	GamePlayMoveable* Interact_Possible_Object_;
	GamePlayStaticObject* Interact_Possible_StaticObject_;

	void Collision_AroundObject();
	
	CollisionReturn GetCrashMoveableObject(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn GetCrashStaticObject(GameEngineCollision* _This, GameEngineCollision* _Other);
	// Bloom Effect
public: 
	inline void SetBloomEffectOff() override
	{
		MsgBoxAssert("�����ڵ� / ĳ���� ��� ������")
	}
	inline void SetBloomEffectOn() override
	{
		MsgBoxAssert("�����ڵ� / ĳ���� ��� ������")
	}

	//
private:



};

