#pragma once
#include "GamePlayStaticObject.h"

enum class CounterTopType
{
	Normal,
	Corner,
	NoEdge
};

// Á¶¸®´ë
class CounterTop : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	CounterTop();
	~CounterTop();

	// delete Function
	CounterTop(const CounterTop& _Other) = delete;
	CounterTop(CounterTop&& _Other) noexcept = delete;
	CounterTop& operator=(const CounterTop& _Other) = delete;
	CounterTop& operator=(CounterTop&& _Other) noexcept = delete;

	void SetType(CounterTopType _Type)
	{
		MyType_ = _Type;
	}

	CounterTopType GetType()
	{
		return MyType_;
	}

protected:
	void Start() override;

private:
	CounterTopType MyType_;
};

