#pragma once
#include "GamePlayStaticObject.h"

class PlateReturn : public GamePlayStaticObject
{
public:
	PlateReturn();
	~PlateReturn();

	PlateReturn(const PlateReturn& _Other) = delete;
	PlateReturn(PlateReturn&& _Other) noexcept = delete;
	PlateReturn& operator=(const PlateReturn& _Other) = delete;
	PlateReturn& operator=(PlateReturn&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

