#pragma once
#include "GamePlayEquipment.h"
#include "GamePlayFood.h"

class GamePlayBowl : public GamePlayEquipment
{
public:
	// constrcuter destructer
	GamePlayBowl();
	~GamePlayBowl();

	// delete Function
	GamePlayBowl(const GamePlayBowl& _Other) = delete;
	GamePlayBowl(GamePlayBowl&& _Other) noexcept = delete;
	GamePlayBowl& operator=(const GamePlayBowl& _Other) = delete;
	GamePlayBowl& operator=(GamePlayBowl&& _Other) noexcept = delete;

	virtual void IsCanCombin(GamePlayFood* _Food) {};
protected:
	void Start() override;
private:

	std::vector<ObjectFoodClass> Food_Current_;
};

