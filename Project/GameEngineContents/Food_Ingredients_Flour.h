#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Flour : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Flour();
	~Food_Ingredients_Flour();

	// delete Function
	Food_Ingredients_Flour(const Food_Ingredients_Flour& _Other) = delete;
	Food_Ingredients_Flour(Food_Ingredients_Flour&& _Other) noexcept = delete;
	Food_Ingredients_Flour& operator=(const Food_Ingredients_Flour& _Other) = delete;
	Food_Ingredients_Flour& operator=(Food_Ingredients_Flour&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};


