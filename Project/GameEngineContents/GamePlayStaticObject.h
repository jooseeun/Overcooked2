#pragma once
#include "GamePlayObject.h"
#include "Enums.h"

// Ό³Έν :
class GamePlayStuff;
class GamePlayStaticObject : public GamePlayObject
{
protected:
	GamePlayStaticObject();
public:
	// constrcuter destructer
	~GamePlayStaticObject();

	// delete Function
	GamePlayStaticObject(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject(GamePlayStaticObject&& _Other) noexcept = delete;
	GamePlayStaticObject& operator=(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject& operator=(GamePlayStaticObject&& _Other) noexcept = delete;

public:
	Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) override;
	Input_PickUpOption Input_PickUp(GamePlayCharacter* _Player) override;

	//inline int GetX() const
	//{
	//	return X_;
	//}
	//inline int GetY() const
	//{
	//	return Y_;
	//}

	//inline void SetX(int _X)
	//{
	//	X_ = _X;
	//}
	//inline void SetY(int _Y)
	//{
	//	Y_ = _Y;
	//}

	inline void SetStaticObjectType(MapObjType _Type)
	{
		MyType_ = _Type;
	}

	inline MapObjType GetStaticObjectType()
	{
		return MyType_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


private:
	GamePlayStuff* Stuff_Current_;

	MapObjType MyType_;

	//int X_;
	//int Y_;



	// Bloom
public:
	void SetBloomEffectOff() override;
	void SetBloomEffectOn() override;

	//
};


