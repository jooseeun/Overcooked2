#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Ingredients_Prawn : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Ingredients_Prawn();
	~Food_Ingredients_Prawn();

	// delete Function
	Food_Ingredients_Prawn(const Food_Ingredients_Prawn& _Other) = delete;
	Food_Ingredients_Prawn(Food_Ingredients_Prawn&& _Other) noexcept = delete;
	Food_Ingredients_Prawn& operator=(const Food_Ingredients_Prawn& _Other) = delete;
	Food_Ingredients_Prawn& operator=(Food_Ingredients_Prawn&& _Other) noexcept = delete;


	//CookedStat Cook_Start_Child() override;
	//void Cook_Update_Child(float _Delta) override;
	//GamePlayMoveable* Cook_End_Child() override;
protected:
	void Start() override;

private:
	void FinishTrimmingFirst() override;

};

