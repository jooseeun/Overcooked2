#pragma once
#include "GamePlayObject.h"
// Ό³Έν :
class Equipment_FryingPan : public GamePlayObject
{
public:
	// constrcuter destructer
	Equipment_FryingPan();
	~Equipment_FryingPan();

	// delete Function
	Equipment_FryingPan(const Equipment_FryingPan& _Other) = delete;
	Equipment_FryingPan(Equipment_FryingPan&& _Other) noexcept = delete;
	Equipment_FryingPan& operator=(const Equipment_FryingPan& _Other) = delete;
	Equipment_FryingPan& operator=(Equipment_FryingPan&& _Other) noexcept = delete;

	
protected:
	void Start() override;
private:

};

