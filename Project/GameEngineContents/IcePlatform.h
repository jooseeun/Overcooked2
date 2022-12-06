#pragma once
#include "GamePlayFloor.h"

// Ό³Έν :
class IcePlatform : public GamePlayFloor
{
public:
	// constrcuter destructer
	IcePlatform();
	~IcePlatform();

	// delete Function
	IcePlatform(const IcePlatform& _Other) = delete;
	IcePlatform(IcePlatform&& _Other) noexcept = delete;
	IcePlatform& operator=(const IcePlatform& _Other) = delete;
	IcePlatform& operator=(IcePlatform&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

