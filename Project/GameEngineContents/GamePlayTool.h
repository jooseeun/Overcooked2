#pragma once
#include "GamePlayStuff.h"

// Ό³Έν :
class GamePlayMoveable;
class GamePlayTool : public GamePlayStuff
{
public:
	// constrcuter destructer
	GamePlayTool();
	~GamePlayTool();

	// delete Function
	GamePlayTool(const GamePlayTool& _Other) = delete;
	GamePlayTool(GamePlayTool&& _Other) noexcept = delete;
	GamePlayTool& operator=(const GamePlayTool& _Other) = delete;
	GamePlayTool& operator=(GamePlayTool&& _Other) noexcept = delete;

protected:


	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:
	Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) final;
	virtual Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) = 0;

private:

	GamePlayMoveable* Food_Current_;
	float CookingGage;
	
};

