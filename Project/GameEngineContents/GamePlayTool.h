#pragma once
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
// 설명 :
enum class AutoOption
{
	NoResponse,
	Auto,
	Manual
};
enum class ObjectToolType
{
	  None
	, CuttingBoard // 도마
	, Cooker       // 가스레인지
	, TrashCan     // 쓰레기통
	, Mixer        // 믹서기
	, PlateReturn  // 접시반납
	, Sink         // 싱크대
	, FoodBox      // 
	, Servicehatch //
	, Rail		   //
	, Dispenser	   //

};

class GamePlayTool : public GamePlayStuff
{
public:
	// constrcuter destructer
	GamePlayTool();
	~GamePlayTool();

	// delete Function
	GamePlayTool(const GamePlayTool& _Other) = delete;
	GamePlayTool(GamePlayTool&& _Other) noexcept = delete;
	GamePlayTool& operator=(const GamePlayTool& _Other) = delete;
	GamePlayTool& operator=(GamePlayTool&& _Other) noexcept = delete;

	inline std::shared_ptr<GamePlayMoveable> GetCurrentMoveable() const
	{
		return Moveable_Current_;
	}
	inline void ReSetCurrentMoveable()
	{
		Moveable_Current_->GetTransform().SetLocalPosition(float4::ZERO);
		Moveable_Current_.reset();
	}
	//inline void SetCurrentMoveable(std::shared_ptr<GamePlayMoveable> _Moveable)
	//{
	//	if (_Moveable == nullptr)
	//	{
	//		ReSetCurrentMoveable();
	//	}
	//	Moveable_Current_ = _Moveable;
	//}

	inline ObjectToolType GetObjectToolType()
	{
		return Enum_ObjectToolType_;
	}

protected:
	void Start() override;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

	virtual bool CanHoldThis(std::shared_ptr<GamePlayMoveable> _Moveable) { return true; };

protected:

	inline void SetInteractOption(AutoOption _Option)
	{
		InteractOption_Current_ = _Option;
	}


private:
	std::shared_ptr<GamePlayMoveable> Moveable_Current_;

	HoldDownEnum HoldDown(std::shared_ptr<Player> _Player) override;


protected:
	inline void SetObjectToolType(ObjectToolType _Type)
	{
		Enum_ObjectToolType_ = _Type;
	}
	virtual void SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child);
	void SetMoveable(std::shared_ptr<Player> _Player);

private:
	ObjectToolType Enum_ObjectToolType_;
	AutoOption InteractOption_Current_;

	float4 MoveablePos_;

	//void SetMoveableObject(std::shared_ptr<GamePlayMoveable> _Object);

	// Bloom
public:
	inline void SetHighlightEffectOff() override
	{
		GamePlayObject::SetHighlightEffectOff();
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->SetHighlightEffectOff();
		}
	}
	inline void SetHighlightEffectOn() override
	{
		GamePlayObject::SetHighlightEffectOn();
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->SetHighlightEffectOn();
		}
	}
};

