#pragma once
#include "GamePlayFood.h"
// Ό³Έν :
class Food_Recipe : public GamePlayFood
{
public:
	// constrcuter destructer
	Food_Recipe();
	~Food_Recipe();

	// delete Function
	Food_Recipe(const Food_Recipe& _Other) = delete;
	Food_Recipe(Food_Recipe&& _Other) noexcept = delete;
	Food_Recipe& operator=(const Food_Recipe& _Other) = delete;
	Food_Recipe& operator=(Food_Recipe&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

private:

};

