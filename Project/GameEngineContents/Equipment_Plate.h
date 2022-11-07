#pragma once
#include "GamePlayBowl.h"
// Ό³Έν :

class Equipment_Plate final : public GamePlayBowl
{
public:
	// constrcuter destructer
	Equipment_Plate();
	~Equipment_Plate();

	// delete Function
	Equipment_Plate(const Equipment_Plate& _Other) = delete;
	Equipment_Plate(Equipment_Plate&& _Other) noexcept = delete;
	Equipment_Plate& operator=(const Equipment_Plate& _Other) = delete;
	Equipment_Plate& operator=(Equipment_Plate&& _Other) noexcept = delete;

	//Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	//Input_InteractOption Input_Interact() override;
protected:
	void Start() override;
private:

};

