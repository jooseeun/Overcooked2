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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

