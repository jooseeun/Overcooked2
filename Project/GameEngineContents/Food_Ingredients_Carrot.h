#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Carrot : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Carrot();
	~Food_Ingredients_Carrot();

	// delete Function
	Food_Ingredients_Carrot(const Food_Ingredients_Carrot& _Other) = delete;
	Food_Ingredients_Carrot(Food_Ingredients_Carrot&& _Other) noexcept = delete;
	Food_Ingredients_Carrot& operator=(const Food_Ingredients_Carrot& _Other) = delete;
	Food_Ingredients_Carrot& operator=(Food_Ingredients_Carrot&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	 void TrimmingMixer() override;
};

