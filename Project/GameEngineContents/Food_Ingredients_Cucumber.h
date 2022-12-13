#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Cucumber : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Cucumber();
	~Food_Ingredients_Cucumber();

	// delete Function
	Food_Ingredients_Cucumber(const Food_Ingredients_Cucumber& _Other) = delete;
	Food_Ingredients_Cucumber(Food_Ingredients_Cucumber&& _Other) noexcept = delete;
	Food_Ingredients_Cucumber& operator=(const Food_Ingredients_Cucumber& _Other) = delete;
	Food_Ingredients_Cucumber& operator=(Food_Ingredients_Cucumber&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void FinishTrimmingFirst() final;

	void TrimmingPlatting() override;
};

