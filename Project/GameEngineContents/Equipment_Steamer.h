#pragma once
#include "GamePlayEquipment.h"

// Ό³Έν :
class Equipment_Steamer : public GamePlayEquipment
{
public:
	// constrcuter destructer
	Equipment_Steamer();
	~Equipment_Steamer();

	// delete Function
	Equipment_Steamer(const Equipment_Steamer& _Other) = delete;
	Equipment_Steamer(Equipment_Steamer&& _Other) noexcept = delete;
	Equipment_Steamer& operator=(const Equipment_Steamer& _Other) = delete;
	Equipment_Steamer& operator=(Equipment_Steamer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

