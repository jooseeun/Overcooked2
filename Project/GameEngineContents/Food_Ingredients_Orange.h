#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Orange : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Orange();
	~Food_Ingredients_Orange();

	// delete Function
	Food_Ingredients_Orange(const Food_Ingredients_Orange& _Other) = delete;
	Food_Ingredients_Orange(Food_Ingredients_Orange&& _Other) noexcept = delete;
	Food_Ingredients_Orange& operator=(const Food_Ingredients_Orange& _Other) = delete;
	Food_Ingredients_Orange& operator=(Food_Ingredients_Orange&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
	void TrimmingMixer() override;
};

