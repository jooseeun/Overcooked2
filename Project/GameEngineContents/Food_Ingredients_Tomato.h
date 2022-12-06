#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Tomato : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Tomato();
	~Food_Ingredients_Tomato();

	// delete Function
	Food_Ingredients_Tomato(const Food_Ingredients_Tomato& _Other) = delete;
	Food_Ingredients_Tomato(Food_Ingredients_Tomato&& _Other) noexcept = delete;
	Food_Ingredients_Tomato& operator=(const Food_Ingredients_Tomato& _Other) = delete;
	Food_Ingredients_Tomato& operator=(Food_Ingredients_Tomato&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void FinishTrimmingFirst() final;

};

