#pragma once
#include "GamePlayMapObject.h"

enum class CandleType
{
	Middle,		// 0 �� ������ �̵�	
	Left,		// 1 ���������� ȸ��
	Right,		// 2 �������� ȸ��
	
	Max,
};

// ���� :
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

