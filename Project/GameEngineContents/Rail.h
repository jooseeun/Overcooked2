#pragma once
#include "GamePlayStaticObject.h"

class Rail : public GamePlayStaticObject
{
public:
	Rail();
	~Rail();

	Rail(const Rail& _Other) = delete;
	Rail(Rail&& _Other) noexcept = delete;
	Rail& operator=(const Rail& _Other) = delete;
	Rail& operator=(Rail&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

