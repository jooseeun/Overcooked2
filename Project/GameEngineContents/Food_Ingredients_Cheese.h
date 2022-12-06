#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Cheese : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Cheese();
	~Food_Ingredients_Cheese();

	// delete Function
	Food_Ingredients_Cheese(const Food_Ingredients_Cheese& _Other) = delete;
	Food_Ingredients_Cheese(Food_Ingredients_Cheese&& _Other) noexcept = delete;
	Food_Ingredients_Cheese& operator=(const Food_Ingredients_Cheese& _Other) = delete;
	Food_Ingredients_Cheese& operator=(Food_Ingredients_Cheese&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void FinishTrimmingFirst() final;

};

