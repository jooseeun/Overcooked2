#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
class Pigeon_Flying : public GamePlayMapObject
{
public:
	// constrcuter destructer
	Pigeon_Flying();
	~Pigeon_Flying();

	// delete Function
	Pigeon_Flying(const Pigeon_Flying& _Other) = delete;
	Pigeon_Flying(Pigeon_Flying&& _Other) noexcept = delete;
	Pigeon_Flying& operator=(const Pigeon_Flying& _Other) = delete;
	Pigeon_Flying& operator=(Pigeon_Flying&& _Other) noexcept = delete;

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

