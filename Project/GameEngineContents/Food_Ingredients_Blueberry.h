#pragma once
#include "GamePlayFood.h"

class Food_Ingredients_Blueberry : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Blueberry();
	~Food_Ingredients_Blueberry();

	// delete Function
	Food_Ingredients_Blueberry(const Food_Ingredients_Blueberry& _Other) = delete;
	Food_Ingredients_Blueberry(Food_Ingredients_Blueberry&& _Other) noexcept = delete;
	Food_Ingredients_Blueberry& operator=(const Food_Ingredients_Blueberry& _Other) = delete;
	Food_Ingredients_Blueberry& operator=(Food_Ingredients_Blueberry&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
	void TrimmingMixer() override;
};

