#pragma once
#include "GamePlayBowl.h"
#include "GamePlayTool.h"
#include "Food_Ingredients_Rice.h"
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
	void Update(float _DeltaTime) override;


	bool AutoTrim(float _DeltaTime, ObjectToolType _Tool)  override;
private:
	std::shared_ptr<Food_Ingredients_Rice> Rice_;
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
};

