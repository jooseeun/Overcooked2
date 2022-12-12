#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Ingredients_Seaweed : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Seaweed();
	~Food_Ingredients_Seaweed();

	// delete Function
	Food_Ingredients_Seaweed(const Food_Ingredients_Seaweed& _Other) = delete;
	Food_Ingredients_Seaweed(Food_Ingredients_Seaweed&& _Other) noexcept = delete;
	Food_Ingredients_Seaweed& operator=(const Food_Ingredients_Seaweed& _Other) = delete;
	Food_Ingredients_Seaweed& operator=(Food_Ingredients_Seaweed&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};


