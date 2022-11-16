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
	None,
	CuttingBoard,

};
class GamePlayTool : public GamePlayStuff
{
	//friend class Tool_TrashCan; // 비워야하니 예외
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
		Moveable_Current_.reset();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) final;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:
	Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override; // 이 이상으로 특별한 이유 없이 오버라이드 금지
	Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override;			  // 이 이상으로 특별한 이유 없이 오버라이드 금지
	virtual Input_PickUpOption CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object);


	inline virtual Input_UsingOption Input_Action(std::weak_ptr<Player> _Player, float _DeltaTime)  // 이 툴(도마 등)을 사용하는 Player의 정보를 인자로 받는다
	{
		if (InteractOption_Current_ == AutoOption::Auto)
		{
			return Input_UsingOption::NoResponse;
		}
		else
		{
			MsgBoxAssert("가상함수가 설정 되지 않았습니다");
			return Input_UsingOption::NoResponse;
		}
	}



	//virtual void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) = 0;
	virtual void Input_ActionToAuto_Update(std::weak_ptr<GamePlayMoveable> _Moveable, float _DeltaTime);
	//virtual void Input_ActionToAuto_Start(GamePlayMoveable* _Moveable, float _DeltaTime) {};


	inline void SetInteractOption(AutoOption _Option)
	{
		InteractOption_Current_ = _Option;
	}

	inline void SetCookingEndTime(float _Time)
	{
		EndCookingTime_ = _Time;
	}
	inline float GetCookingEndTime()
	{
		return EndCookingTime_;
	}



private:
	std::shared_ptr<GamePlayMoveable> Moveable_Current_;
protected:
	inline void SetCurrentMoveable(std::shared_ptr<GamePlayMoveable> _Moveable)
	{
		if (_Moveable == nullptr)
		{
			ReSetCurrentMoveable();
		}
		else
		{
			Moveable_Current_ = _Moveable;
		}
		
	}



private:
	float EndCookingTime_;


	AutoOption InteractOption_Current_;

	float4 FoodPos_;


	// Bloom
public:
	inline void SetBloomEffectOff() override
	{
		GamePlayObject::SetBloomEffectOff();
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->SetBloomEffectOff();
		}
	}
	inline void SetBloomEffectOn() override
	{
		GamePlayObject::SetBloomEffectOn();
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->SetBloomEffectOn();
		}
	}
};

