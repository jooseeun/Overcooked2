#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
class Bird_Flying : public GamePlayMapObject
{
public:
	// constrcuter destructer
	Bird_Flying();
	~Bird_Flying();

	// delete Function
	Bird_Flying(const Bird_Flying& _Other) = delete;
	Bird_Flying(Bird_Flying&& _Other) noexcept = delete;
	Bird_Flying& operator=(const Bird_Flying& _Other) = delete;
	Bird_Flying& operator=(Bird_Flying&& _Other) noexcept = delete;

public:
	inline void SetStartPosition(float4 _StartPos)
	{
		StartPos_ = _StartPos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 MoveDir_;
	float4 StartPos_;

	bool IsPause_;
	float Time_;
	int RandomTime_;
};

