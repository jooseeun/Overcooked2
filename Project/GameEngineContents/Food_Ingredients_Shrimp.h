#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Shrimp : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Shrimp();
	~Food_Ingredients_Shrimp();

	// delete Function
	Food_Ingredients_Shrimp(const Food_Ingredients_Shrimp& _Other) = delete;
	Food_Ingredients_Shrimp(Food_Ingredients_Shrimp&& _Other) noexcept = delete;
	Food_Ingredients_Shrimp& operator=(const Food_Ingredients_Shrimp& _Other) = delete;
	Food_Ingredients_Shrimp& operator=(Food_Ingredients_Shrimp&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

