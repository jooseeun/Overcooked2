#pragma once
#include "GamePlayBowl.h"
// Ό³Έν :
class Equipment_Pot final : public GamePlayBowl
{
public:
	// constrcuter destructer
	Equipment_Pot();
	~Equipment_Pot();

	// delete Function
	Equipment_Pot(const Equipment_Pot& _Other) = delete;
	Equipment_Pot(Equipment_Pot&& _Other) noexcept = delete;
	Equipment_Pot& operator=(const Equipment_Pot& _Other) = delete;
	Equipment_Pot& operator=(Equipment_Pot&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
};

