#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Rice : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Rice();
	~Food_Ingredients_Rice();

	// delete Function
	Food_Ingredients_Rice(const Food_Ingredients_Rice& _Other) = delete;
	Food_Ingredients_Rice(Food_Ingredients_Rice&& _Other) noexcept = delete;
	Food_Ingredients_Rice& operator=(const Food_Ingredients_Rice& _Other) = delete;
	Food_Ingredients_Rice& operator=(Food_Ingredients_Rice&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

