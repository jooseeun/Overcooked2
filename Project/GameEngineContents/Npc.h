#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
class Npc : public GamePlayMapObject
{
public:
	// constrcuter destructer
	Npc();
	~Npc();

	// delete Function
	Npc(const Npc& _Other) = delete;
	Npc(Npc&& _Other) noexcept = delete;
	Npc& operator=(const Npc& _Other) = delete;
	Npc& operator=(Npc&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int RandomTime_;

};

