#include "PreCompile.h"
#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineTime.h"
#include "GameEngineString.h"
#include "GameEngineWindow.h"
#include <WinUser.h>

#pragma comment(lib, "xinput.lib")

//////////////////////////////////////////////////////////////////
//#define XINPUT_GAMEPAD_DPAD_UP          0x0001
//#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
//#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
//#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
//#define XINPUT_GAMEPAD_START            0x0010
//#define XINPUT_GAMEPAD_BACK             0x0020
//#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
//#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
//#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
//#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
//#define XINPUT_GAMEPAD_A                0x1000
//#define XINPUT_GAMEPAD_B                0x2000
//#define XINPUT_GAMEPAD_X                0x4000
//#define XINPUT_GAMEPAD_Y                0x8000
//////////////////////////////////////////////////////////////////
//진동
//XINPUT_VIBRATION vibration;
//ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
//vibration.wLeftMotorSpeed = 65535;	// 0 ~ 65535 사이의 수
//vibration.wRightMotorSpeed = 0;		// 0 ~ 65535 사이의 수
//XInputSetState(0, &vibration);
//////////////////////////////////////////////////////////////////
// 아날로그 스틱
//state.Gamepad.sThumbLX	// 왼쪽 아날로그 스틱 X축
//state.Gamepad.sThumbLY	// 왼쪽 아날로그 스틱 Y축
//state.Gamepad.sThumbRX	// 오른쪽 아날로그 스틱 X축
//state.Gamepad.sThumbRY	// 오른쪽 아날로그 스틱 Y축
//////////////////////////////////////////////////////////////////
//트리거
//state.Gamepad.bLeftTrigger	// 왼쪽 트리거
//state.Gamepad.bRightTrigger	// 오른쪽 트리거
//////////////////////////////////////////////////////////////////


void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;
		}
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
		}
	}
	else
	{
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
			Time_ = 0.0f;
		}
		else if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}

////////////////////////////////////////////////////////////////

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput()
	: InputState_{}
	, WheelValue()
	, CurWheelValue()
	, IsVibration_(false)
	, VibrationTime_(0.f)
	, LitmitVibrationTime_(1.f)
	, ThumbLX_(0)
	, ThumbLY_(0)
	, ThumbRX_(0)
	, ThumbRY_(0)
	, LeftTrigger_(0)
	, RightTrigger_(0)
	, AllInputButton_{}
{
}

GameEngineInput::~GameEngineInput()
{
}


bool GameEngineInput::IsKey(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		return true;
	}

	return false;
}

bool GameEngineInput::IsDownButton(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() == AllInputButton_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 버튼 입니다.");
		return false;
	}
	return AllInputButton_[UpperKey].Down_;
}

bool GameEngineInput::IsUpButton(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() == AllInputButton_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 버튼 입니다.");
		return false;
	}
	return AllInputButton_[UpperKey].Up_;
}

bool GameEngineInput::IsPressButton(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() == AllInputButton_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 버튼 입니다.");
		return false;
	}
	return AllInputButton_[UpperKey].Press_;
}

bool GameEngineInput::IsFreeButton(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() == AllInputButton_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 버튼 입니다.");
		return false;
	}
	return AllInputButton_[UpperKey].Free_;
}

bool GameEngineInput::IsButton(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() != AllInputButton_.find(UpperKey))
	{
		return true;
	}

	return false;
}

void GameEngineInput::VibrationUpdate()
{
	if (true == IsVibration_)
	{
		VibrationTime_ += GameEngineTime::GetDeltaTime();

		XINPUT_VIBRATION Vibration;
		ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

		if (LitmitVibrationTime_ <= VibrationTime_)
		{
			VibrationTime_ = 0;
			IsVibration_ = false;

			Vibration.wLeftMotorSpeed = 0;
			Vibration.wRightMotorSpeed = 0;
			XInputSetState(0, &Vibration);

			return;
		}

		Vibration.wLeftMotorSpeed = 5000;	// 0 ~ 65535 사이의 수
		Vibration.wRightMotorSpeed = 5000;		// 0 ~ 65535 사이의 수
		XInputSetState(0, &Vibration);
	}
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다.");
		return;
	}

	AllInputKey_.insert(std::make_pair(UpperKey, GameEngineKey()));
	AllInputKey_[UpperKey].Key_ = _Key;
	AllInputKey_[UpperKey].Reset();
}

void GameEngineInput::CreateButton(const std::string& _Name, int _Button)
{
	std::string UpperButton = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() != AllInputButton_.find(UpperButton))
	{
		MsgBoxAssert("이미 존재하는 이름의 버튼을 또 만들려고 했습니다.");
		return;
	}

	AllInputButton_.insert(std::make_pair(UpperButton, GameEngineButton()));
	AllInputButton_[UpperButton].Button_ = _Button;
	AllInputButton_[UpperButton].Reset();
}

void GameEngineInput::Reset()
{
	CurWheelValue = 0;
	CurWheelValue = WheelValue;
	WheelValue = 0;

	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Reset();
	}

	std::map<std::string, GameEngineButton>::iterator ButtonUpdateStart = AllInputButton_.begin();
	std::map<std::string, GameEngineButton>::iterator ButtonUpdateEnd = AllInputButton_.end();

	for (; ButtonUpdateStart != ButtonUpdateEnd; ++ButtonUpdateStart)
	{
		GameEngineButton& CurrentButton = ButtonUpdateStart->second;

		CurrentButton.Reset();
	}
}

void GameEngineInput::Update(float _DeltaTime)
{
	CurWheelValue = 0;
	CurWheelValue = WheelValue;
	WheelValue = 0;

	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update(_DeltaTime);
	}

	std::map<std::string, GameEngineButton>::iterator ButtonUpdateStart = AllInputButton_.begin();
	std::map<std::string, GameEngineButton>::iterator ButtonUpdateEnd = AllInputButton_.end();

	for (; ButtonUpdateStart != ButtonUpdateEnd; ++ButtonUpdateStart)
	{
		GameEngineButton& CurrentButtton = ButtonUpdateStart->second;

		CurrentButtton.Update(_DeltaTime);
	}

	VibrationUpdate();
	ThumbUpdate();
}

float  GameEngineInput::GetButtonTime(const std::string& _Name)
{
	std::string UpperButton = GameEngineString::ToUpperReturn(_Name);

	if (AllInputButton_.end() == AllInputButton_.find(UpperButton))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}

	return AllInputButton_[UpperButton].Time_;
}

float GameEngineInput::GetKeyTime(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}

	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDownKey(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}

	return AllInputKey_[UpperKey].Down_;
}

bool GameEngineInput::IsUpKey(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperKey].Up_;
}

bool GameEngineInput::IsPressKey(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperKey].Press_;
}

bool GameEngineInput::IsFreeKey(const std::string& _Name)
{
	if (GameEngineWindow::GetHWND() != GetActiveWindow())
	{
		return false;
	}

	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[UpperKey].Free_;
}

bool GameEngineInput::GameEngineButton::ButtonCheck(const XINPUT_STATE _State)
{
	if (_State.Gamepad.wButtons & Button_)
	{
		return true;
	}

	return false;
}

void GameEngineInput::GameEngineButton::Update(float _DeltaTime)
{
	DWORD DwResult;
	XINPUT_STATE State_;
	ZeroMemory(&State_, sizeof(XINPUT_STATE)); //컨트롤러 상태 초기화
	DwResult = XInputGetState(0, &State_); //컨트롤러 상태 얻어오기

	if (DwResult == ERROR_SUCCESS)
	{
		if (true == ButtonCheck(State_))
		{
			if (true == Free_)
			{
				Down_ = true;
				Press_ = true;
				Up_ = false;
				Free_ = false;
				Time_ = 0.0f;
				Time_ += _DeltaTime;
			}

			else if (true == Press_)
			{
				Down_ = false;
				Press_ = true;
				Up_ = false;
				Free_ = false;
				Time_ += _DeltaTime;
			}
		}
		else
		{
			if (true == Press_)
			{
				Down_ = false;
				Press_ = false;
				Up_ = true;
				Free_ = false;
				Time_ = 0.0f;
			}
			else if (true == Up_)
			{
				Down_ = false;
				Press_ = false;
				Up_ = false;
				Free_ = true;
			}
		}

		//Sleep(30); //Cpu 점유율 100% 방지
		DwResult = XInputGetState(0, &State_); //다음 상태 얻어오기
	}
}


void GameEngineInput::ThumbUpdate()
{
	DWORD DwResult;
	ZeroMemory(&InputState_, sizeof(XINPUT_STATE)); //컨트롤러 상태 초기화
	DwResult = XInputGetState(0, &InputState_); //컨트롤러 상태 얻어오기

	InputState_.Gamepad.bLeftTrigger;

	if (DwResult == ERROR_SUCCESS)
	{
		ThumbLX_ = InputState_.Gamepad.sThumbLX;
		ThumbLY_ = InputState_.Gamepad.sThumbLY;
		ThumbRX_ = InputState_.Gamepad.sThumbRX;
		ThumbRY_ = InputState_.Gamepad.sThumbRY;

		LeftTrigger_ = InputState_.Gamepad.bLeftTrigger;
		RightTrigger_ = InputState_.Gamepad.bRightTrigger;

		DwResult = XInputGetState(0, &InputState_);
	}
}
