#pragma once
#include "GamePlayObject.h"

enum class MOVECARSTATE
{
	WAIT, //운전 준비
	DRIVE, //운전
	ARRIVAL //도착
};

class MoveCar : public GamePlayObject
{
public:
	MoveCar();
	~MoveCar();

	MoveCar(const MoveCar& _Other) = delete;
	MoveCar(MoveCar&& _Other) noexcept = delete;
	MoveCar& operator=(const MoveCar& _Other) = delete;
	MoveCar& operator=(MoveCar&& _Other) noexcept = delete;

	void SetCarMesh(const std::string& _Name)
	{
		GetFBXMesh()->SetFBXMesh(_Name);
		GetFBXMesh()->GetTransform().SetWorldScale({ 80.f, 80.f, 80.f });
	}

	void SetTimeInterval(float _Interval)
	{
		TimeInterval_ = _Interval;
	}

	void SetStartPos(float4 _Pos)
	{
		StartPos_ = _Pos;
	}

	void SetEndPos(float4 _Pos)
	{
		EndPos_ = _Pos;
	}
	
	void SetStartTime(float _Time)
	{
		StartTime_ = _Time;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	MOVECARSTATE State_;

	float TimeInterval_;

	float4 StartPos_;
	float4 EndPos_;

	bool IsMove_;

	float StartTime_;
	float StackTime_;
};

