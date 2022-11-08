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
enum class Input_UsingOption
{
	NoResponse,          
	Using,        // 사용
	Throwing,     // 던지기
};
enum class ObjectToolType
{
	None,
	CuttingBoard,

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

	//inline void Interact_Manual(float _DeltaTime)
	//{
	//	Moveable_Current_->Cook_Update(_DeltaTime);
	//}

protected:
	void Start() override;
	void Update(float _DeltaTime) final;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:
	Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) final;
	Input_PickUpOption Input_PickUp(Player* _Player) final;
	virtual Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object);

	virtual Input_UsingOption Input_Action(Player* _Player) = 0; // 이 장치를 사용하는 Player의 정보를 인자로 받는다


	inline void SetInteractOption(AutoOption _Option)
	{
		InteractOption_Current_ = _Option;
	}

private:
	GamePlayMoveable* Moveable_Current_;
	AutoOption InteractOption_Current_;


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

