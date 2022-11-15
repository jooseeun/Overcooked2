#pragma once
#include "GamePlayMapObject.h"

enum class CandleType
{
	Middle,		// 0 양 옆으로 이동	
	Left,		// 1 오른쪽으로 회전
	Right,		// 2 왼쪽으로 회전
	
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
	inline CandleType GetCandleType()
	{
		return CandleType_;
	}

	void SetCandleTypeIndex(float4 TypeIndex);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	CandleType CandleType_;
};

