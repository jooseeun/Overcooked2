#pragma once
#include "GamePlayFood.h"

// Ό³Έν :
class Food_Empty : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Empty();
	~Food_Empty();

	// delete Function
	Food_Empty(const Food_Empty& _Other) = delete;
	Food_Empty(Food_Empty&& _Other) noexcept = delete;
	Food_Empty& operator=(const Food_Empty& _Other) = delete;
	Food_Empty& operator=(Food_Empty&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

