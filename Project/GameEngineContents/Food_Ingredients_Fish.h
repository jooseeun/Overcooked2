#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Fish : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Fish();
	~Food_Ingredients_Fish();

	// delete Function
	Food_Ingredients_Fish(const Food_Ingredients_Fish& _Other) = delete;
	Food_Ingredients_Fish(Food_Ingredients_Fish&& _Other) noexcept = delete;
	Food_Ingredients_Fish& operator=(const Food_Ingredients_Fish& _Other) = delete;
	Food_Ingredients_Fish& operator=(Food_Ingredients_Fish&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

