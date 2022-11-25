#pragma once
#include "GamePlayObject.h"
// Ό³Έν :
class Equipment_FireExtinguisher : public GamePlayObject
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


protected:
	void Start() override;
private:

};

