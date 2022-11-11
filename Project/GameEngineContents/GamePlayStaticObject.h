#pragma once
#include "GamePlayObject.h"
#include "Enums.h"
#include "GamePlayStuff.h"

// Ό³Έν :
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
	Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override;
	Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override;


	inline std::shared_ptr<GamePlayStuff> GetStuff() const
	{
		return Stuff_Current_;
	}
	inline void SetStuff(std::shared_ptr<GamePlayStuff> _Stuff)
	{
		Stuff_Current_ = _Stuff;

		if (nullptr != _Stuff)
		{
			_Stuff->SetParentObject(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()));
		}
	}
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

	inline ToolInfo GetToolInfo() const
	{
		if (Stuff_Current_ == nullptr)
		{
			return ToolInfo::None;
		}
		else
		{
			return Stuff_Current_->GetToolInfoType();
		}
		 
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
	std::shared_ptr<GamePlayStuff> Stuff_Current_;

	MapObjType MyType_;

	float4 ToolPos_;

	//int X_;
	//int Y_;



	// Bloom
public:
	void SetBloomEffectOff() override;
	void SetBloomEffectOn() override;

	//
};


