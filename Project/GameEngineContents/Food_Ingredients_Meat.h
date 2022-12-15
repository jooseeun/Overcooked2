#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Meat : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Meat();
	~Food_Ingredients_Meat();

	// delete Function
	Food_Ingredients_Meat(const Food_Ingredients_Meat& _Other) = delete;
	Food_Ingredients_Meat(Food_Ingredients_Meat&& _Other) noexcept = delete;
	Food_Ingredients_Meat& operator=(const Food_Ingredients_Meat& _Other) = delete;
	Food_Ingredients_Meat& operator=(Food_Ingredients_Meat&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void FinishTrimmingFirst() override;
	
	void TrimmingPlatting() override;
	void TrimmingPried() override;
};

