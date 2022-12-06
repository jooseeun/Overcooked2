#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Lettuce : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Lettuce();
	~Food_Ingredients_Lettuce();

	// delete Function
	Food_Ingredients_Lettuce(const Food_Ingredients_Lettuce& _Other) = delete;
	Food_Ingredients_Lettuce(Food_Ingredients_Lettuce&& _Other) noexcept = delete;
	Food_Ingredients_Lettuce& operator=(const Food_Ingredients_Lettuce& _Other) = delete;
	Food_Ingredients_Lettuce& operator=(Food_Ingredients_Lettuce&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void FinishTrimmingFirst() final;
};

