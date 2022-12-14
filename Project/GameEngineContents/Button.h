#pragma once
#include "Cannon.h"

// ���� :
class Button : public Cannon
{
public:
	// constrcuter destructer
	Button();
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

public:
	// ��ư�� ���� �� �ִ� ���¸� true �� ��ȯ. 
	inline bool CheckButtonReadyState()
	{
		return true == IsReady_ ? true : false;
	}

	// ��ư�� ���ȴٴ°� ��ư���� �˷��ִ� �Լ�
	inline void SetButtonPressed()
	{
		IsPressed_ = true;
	}

	inline void SetButtonUnPressed()
	{
		IsPressed_ = false;
	}

	inline bool CheckButtonPressedState()
	{
		return true == IsPressed_ ? true : false;
	}

	inline void SwitchButtonState()
	{
		IsReady_ = !IsReady_;
	}

	bool IsReady_;
	bool IsPressed_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> ButtonRenderer_On;
	std::shared_ptr<GameEngineFBXStaticRenderer> ButtonRenderer_Off;

	std::shared_ptr<GameEngineCollision> Collision_Object_;


};

