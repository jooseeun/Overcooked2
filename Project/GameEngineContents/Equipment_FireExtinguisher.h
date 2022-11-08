#pragma once
#include "GamePlayEquipment.h"
// Ό³Έν :
class Equipment_FireExtinguisher : public GamePlayEquipment
{
public:
	// constrcuter destructer
	Equipment_FireExtinguisher();
	~Equipment_FireExtinguisher();

	// delete Function
	Equipment_FireExtinguisher(const Equipment_FireExtinguisher& _Other) = delete;
	Equipment_FireExtinguisher(Equipment_FireExtinguisher&& _Other) noexcept = delete;
	Equipment_FireExtinguisher& operator=(const Equipment_FireExtinguisher& _Other) = delete;
	Equipment_FireExtinguisher& operator=(Equipment_FireExtinguisher&& _Other) noexcept = delete;

	Input_PickUpOption Input_PickUp(Player* _Player) override;
	// PlayerHoldType
protected:
	void Start() override;
private:

};

