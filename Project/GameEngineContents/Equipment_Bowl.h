#pragma once
#include "GamePlayBowl.h"

// Ό³Έν :
class Equipment_Bowl : public GamePlayBowl
{
public:
	// constrcuter destructer
	Equipment_Bowl();
	~Equipment_Bowl();

	// delete Function
	Equipment_Bowl(const Equipment_Bowl& _Other) = delete;
	Equipment_Bowl(Equipment_Bowl&& _Other) noexcept = delete;
	Equipment_Bowl& operator=(const Equipment_Bowl& _Other) = delete;
	Equipment_Bowl& operator=(Equipment_Bowl&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
	bool AutoTrim(float _DeltaTime, ObjectToolType _Tool) override;
	void FinishTrimmingFirst() final;

};

