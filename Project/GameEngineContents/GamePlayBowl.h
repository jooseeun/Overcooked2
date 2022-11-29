#pragma once
#include "GamePlayEquipment.h"
#include "GamePlayFood.h"
#include "Enums.h"
#include "FoodThumbnail.h"

struct CombinFood
{
	std::vector<IngredientType> Food_Current_;
	std::vector<std::shared_ptr<FoodThumbnail>> Food_Thumbnail_;

};

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


	virtual bool IsCanCombin(IngredientType _Food) { return false;  };
protected:
	void Start() override;
private:
	std::shared_ptr<CombinFood> CombinFood_;

	HoldDownEnum HoldDown(std::shared_ptr<Player> _Player) final;

	//void RefreshFoodThumbnail();
};

