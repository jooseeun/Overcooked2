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
	//Input_PutDownOption Input_PutDown(std::shared_ptr<GamePlayMoveable> _Object) override;
	//Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override;
	//PlayerHoldType Input_Action() { return PlayerHoldType::Max; } override;

	SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type);



	inline std::shared_ptr<GamePlayStuff> GetStuff() const
	{
		return Stuff_Current_;
	}
	std::shared_ptr<GamePlayMoveable> GetMoveable() const;
	std::shared_ptr<GamePlayMoveable> GetMoveable_TakeOut();
	inline void SetStuff(std::shared_ptr<GamePlayStuff> _Stuff)
	{
		Stuff_Current_ = _Stuff;

		if (nullptr != _Stuff)
		{
			_Stuff->SetParent(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()));
		}
	}
	inline void ReSetStuff()
	{
		Stuff_Current_.reset();
	}


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

	inline void SetToolPos(float4& _Pos)
	{
		ToolPos_ = _Pos;
	}

	virtual float4 GetToolPos() 
	{
		ToolPos_ = GetTransform().GetWorldPosition() + float4{ 0, 50.f };

		return ToolPos_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

	float4 ToolPos_;

private:
	std::shared_ptr<GamePlayStuff> Stuff_Current_;

	MapObjType MyType_;


	//int X_;
	//int Y_;



	// Bloom
public:
	void SetHighlightEffectOff() override;
	void SetHighlightEffectOn() override;

	//
};


