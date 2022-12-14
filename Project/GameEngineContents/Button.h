#pragma once
#include "Cannon.h"

// 설명 :
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
	// 버튼을 누를 수 있는 상태면 true 를 반환. 
	inline bool CheckButtonReadyState()
	{
		return true == IsReady_ ? true : false;
	}

	// 버튼이 눌렸다는걸 버튼에게 알려주는 함수
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

