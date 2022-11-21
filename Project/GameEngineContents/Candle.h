#pragma once
#include "GamePlayMapObject.h"

enum class CandleType
{
	Middle,		// 0 양 옆으로 이동	
	Left,		// 1 오른쪽으로 회전
	Right,		// 2 왼쪽으로 회전
	
	Max,
};

enum class CandleDir
{
	Left,
	Right,
	Up,
	Down,
	Max,
};

// 설명 :
class Candle : public GamePlayMapObject
{
public:
	// constrcuter destructer
	Candle();
	~Candle();

	// delete Function
	Candle(const Candle& _Other) = delete;
	Candle(Candle&& _Other) noexcept = delete;
	Candle& operator=(const Candle& _Other) = delete;
	Candle& operator=(Candle&& _Other) noexcept = delete;

public:
	inline int GetCandleTypeIndex()
	{
		return CandleTypeIndex_;
	}

	inline CandleType GetCandleType()
	{
		return CandleType_;
	}

	void SetCandleTypeIndex(int _TypeIndex);
	void InfoSetting();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LeftMoveStart(const StateInfo& _Info);
	void LeftMoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void RightMoveStart(const StateInfo& _Info);
	void RightMoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void UpMoveStart(const StateInfo& _Info);
	void UpMoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void DownMoveStart(const StateInfo& _Info);
	void DownMoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void UpDownMove(float _DeltaTime);

private:
	CandleType CandleType_;
	int CandleTypeIndex_;
	float Speed_;
	float ChangeTime_;
	float StopTime_;
	float MoveTime_;
	std::string StateName_;

	float4 MoveDir_;
	float4 UpDowmDir_;
	CandleDir CurDir_;


	GameEngineStateManager StateManager;

};

