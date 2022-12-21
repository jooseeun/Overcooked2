#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_DriedFruit : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_DriedFruit();
	~Food_Ingredients_DriedFruit();

	// delete Function
	Food_Ingredients_DriedFruit(const Food_Ingredients_DriedFruit& _Other) = delete;
	Food_Ingredients_DriedFruit(Food_Ingredients_DriedFruit&& _Other) noexcept = delete;
	Food_Ingredients_DriedFruit& operator=(const Food_Ingredients_DriedFruit& _Other) = delete;
	Food_Ingredients_DriedFruit& operator=(Food_Ingredients_DriedFruit&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
	void TrimmingMixer() override;
};

