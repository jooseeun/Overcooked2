#pragma once
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
// ���� :
enum class AutoOption
{
	NoResponse,
	Auto,
	Manual
};
enum class Input_UsingOption
{
	NoResponse,          
	Using,        // ���
	Throwing,     // ������
};
enum class ObjectToolType
{
	None,
	CuttingBoard,

};
class GamePlayTool : public GamePlayStuff
{
	//friend class Tool_TrashCan; // ������ϴ� ����
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
	Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) override; // �� �̻����� Ư���� ���� ���� �������̵� ����
	Input_PickUpOption Input_PickUp(Player* _Player) override;			  // �� �̻����� Ư���� ���� ���� �������̵� ����
	virtual Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object);

	virtual Input_UsingOption Input_ActionToManual(Player* _Player, float _DeltaTime) { return Input_UsingOption::NoResponse; };         // �� ��(���� ��)�� ����ϴ� Player�� ������ ���ڷ� �޴´�
	virtual void Input_Action_End(GamePlayMoveable* _Moveable) = 0;
	virtual void Input_ActionToAuto_Update(GamePlayMoveable* _Moveable, float _DeltaTime);
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
	GamePlayMoveable* Moveable_Current_;
protected:
	inline void SetCurrentMoveable(GamePlayMoveable* _Moveable)
	{
		Moveable_Current_ = _Moveable;
	}
	inline GamePlayMoveable* GetCurrentMoveable() const
	{
		return Moveable_Current_;
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

