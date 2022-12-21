#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Strawberry : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Strawberry();
	~Food_Ingredients_Strawberry();

	// delete Function
	Food_Ingredients_Strawberry(const Food_Ingredients_Strawberry& _Other) = delete;
	Food_Ingredients_Strawberry(Food_Ingredients_Strawberry&& _Other) noexcept = delete;
	Food_Ingredients_Strawberry& operator=(const Food_Ingredients_Strawberry& _Other) = delete;
	Food_Ingredients_Strawberry& operator=(Food_Ingredients_Strawberry&& _Other) noexcept = delete;


protected:
	void Start() override;

private:
	//void FinishTrimmingFirst() final;

	//void TrimmingPlatting() override;
	void TrimmingMixer() override;
};

