#pragma once
#include "GamePlayStaticObject.h"

enum class CounterTopType
{
	Normal,
	Corner,
	NoEdge,
	Wizard,
	Winter,
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

	inline void SetCounterTopType(CounterTopType _Type)
	{
		MyType_ = _Type;
	}

	inline CounterTopType GetCounterTopType()
	{
		return MyType_;
	}

	void SetConterTopMesh(CounterTopType _Type);

protected:
	void Start() override;

private:
	CounterTopType MyType_;
};

