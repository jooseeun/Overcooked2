#pragma once
#include "GamePlayBowl.h"
// Ό³Έν :
class Equipment_FryingPan : public GamePlayBowl
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
	bool AutoTrim(float _DeltaTime, ObjectToolType _Tool) override;
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;

	std::shared_ptr<GamePlayFood> FryFood_;
	inline void SetFryFood(std::shared_ptr<GamePlayFood> _Food)
	{
		FryFood_ = _Food;
		if (FryFood_ != nullptr)
		{
			FryFood_->SetParent(shared_from_this());
			FryFood_->GetTransform().SetLocalPosition({ 0,0,0 });
			FryFood_->GetCollisionObject()->Off();
		}
	}
};

