#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <Xinput.h>

class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; // 최초로 키를 눌렀을때
		bool Press_; // 계속 누르는중
		bool Up_; // 막 뗐을때
		bool Free_; // 안누르고 있을때.

		float Time_;
		int Key_; // 이 키가 눌렸다면,, 

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update(float _DeltaTime);

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}

		// 생성자 주석걸어두기
		//GameEngineKey(int _Key) 
		//	: Key_(_Key)
		//	, Down_(false)
		//	, Press_(false)
		//	, Up_(false)
		//	, Free_(true)
		//{
		//}
	};

private:
	class GameEngineButton
	{
		friend GameEngineInput;

		bool Down_;
		bool Press_;
		bool Up_;
		bool Free_;

		float Time_;
		int Button_;

		bool ButtonCheck(XINPUT_STATE _State);
		void Update(float _DeltaTime);
		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	};

	friend class GameEngineWindow;

private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void Reset();
	void Update(float _DeltaTime = 0.0f);
	void CreateKey(const std::string& _Name, int _Key);
	void CreateButton(const std::string& _Name, int _Button);

	float GetKeyTime(const std::string& _Name);
	bool IsDownKey(const std::string& _Name);
	bool IsUpKey(const std::string& _Name);
	bool IsPressKey(const std::string& _Name);
	bool IsFreeKey(const std::string& _Name);
	bool IsKey(const std::string& _Name);

	float GetButtonTime(const std::string& _Name);
	bool IsDownButton(const std::string& _Name);
	bool IsUpButton(const std::string& _Name);
	bool IsPressButton(const std::string& _Name);
	bool IsFreeButton(const std::string& _Name);
	bool IsButton(const std::string& _Name);

	inline void VibrationOn(float _Time = 1.0f)
	{
		IsVibration_ = true;
		VibrationTime_ = 0.f;
		LitmitVibrationTime_ = _Time;
	}

	void VibrationUpdate();
	void ThumbUpdate();

	inline int GetMouseWheel()
	{
		return CurWheelValue;
	}

	//왼쪽 아날로그 스틱 X축
	inline SHORT GetThumbLX()
	{
		return ThumbLX_;
	}

	inline void SetThumbLX(SHORT _Value)
	{
		ThumbLX_ = _Value;
	}

	// 왼쪽 아날로그 스틱 Y축
	inline SHORT GetThumbLY()
	{
		return ThumbLY_;
	}

	// 오른쪽 아날로그 스틱 X축
	inline SHORT GetThumbRX()
	{
		return ThumbRX_;
	}

	// 오른쪽 아날로그 스틱 Y축
	inline SHORT GetThumbRY()
	{
		return ThumbRY_;
	}

	inline BYTE GetLeftTrigger()
	{
		return LeftTrigger_;
	}

	inline void SetLeftTrigger(BYTE _Value)
	{
		LeftTrigger_ = _Value;
	}

	inline BYTE GetRightTrigger()
	{
		return RightTrigger_;
	}

	inline double GetMagnitudeL()
	{
		return sqrt(ThumbLX_ * ThumbLX_ + ThumbLY_ * ThumbLY_);
	}

	inline double GetMagnitudeLX()
	{
		return sqrt(ThumbLX_ * ThumbLX_);
	}

	inline double GetMagnitudeLY()
	{
		return sqrt(ThumbLY_ * ThumbLY_);
	}

	inline double GetMagnitudeR()
	{
		return sqrt(ThumbRX_ * ThumbRX_ + ThumbRY_ * ThumbRY_);
	}

	inline XINPUT_STATE GetInputState()
	{
		if (true == IsEditMode_)
		{
			InputState_.dwPacketNumber = 1;
		}

		return InputState_;
	}

	inline void SetEditMode(bool _Value)
	{
		IsEditMode_ = _Value;
	}

protected:


private:
	XINPUT_STATE InputState_;

	int WheelValue;
	int CurWheelValue;

	bool IsVibration_;
	float VibrationTime_;
	float LitmitVibrationTime_;

	bool IsEditMode_;

	SHORT ThumbLX_;
	SHORT ThumbLY_;
	SHORT ThumbRX_;
	SHORT ThumbRY_;

	BYTE LeftTrigger_;
	BYTE RightTrigger_;

	std::map<std::string, GameEngineKey> AllInputKey_;
	std::map<std::string, GameEngineButton> AllInputButton_;

	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
};

