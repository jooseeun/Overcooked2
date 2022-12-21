#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Egg : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Egg();
	~Food_Ingredients_Egg();

	// delete Function
	Food_Ingredients_Egg(const Food_Ingredients_Egg& _Other) = delete;
	Food_Ingredients_Egg(Food_Ingredients_Egg&& _Other) noexcept = delete;
	Food_Ingredients_Egg& operator=(const Food_Ingredients_Egg& _Other) = delete;
	Food_Ingredients_Egg& operator=(Food_Ingredients_Egg&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	//void FinishTrimmingFirst() final;

	void TrimmingPlatting() override;
	void TrimmingSteam() override;
};

