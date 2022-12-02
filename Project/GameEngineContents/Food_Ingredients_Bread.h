#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Bread : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Bread();
	~Food_Ingredients_Bread();

	// delete Function
	Food_Ingredients_Bread(const Food_Ingredients_Bread& _Other) = delete;
	Food_Ingredients_Bread(Food_Ingredients_Bread&& _Other) noexcept = delete;
	Food_Ingredients_Bread& operator=(const Food_Ingredients_Bread& _Other) = delete;
	Food_Ingredients_Bread& operator=(Food_Ingredients_Bread&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

