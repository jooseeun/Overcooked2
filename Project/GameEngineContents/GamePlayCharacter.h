#pragma once
#include "GamePlayObject.h"

// 설명 :
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


	// 상호작용 버튼
	void Input_PickUpButton();


private:
	GamePlayMoveable* Moveable_Current_;      // 들고 있는 오브젝트


	// Interact Collision
	GameEngineCollision* Collision_Interact_; // 상호작용 콜리전
	GamePlayMoveable* Interact_Possible_Object_;
	GamePlayStaticObject* Interact_Possible_StaticObject_;

	void Collision_AroundObject();
	CollisionReturn GetCrashObject(GameEngineCollision* _This, GameEngineCollision* _Other);

};

