#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
class GamePlayFloor : public GamePlayMapObject
{
public:
	// constrcuter destructer
	GamePlayFloor();
	~GamePlayFloor();

	// delete Function
	GamePlayFloor(const GamePlayFloor& _Other) = delete;
	GamePlayFloor(GamePlayFloor&& _Other) noexcept = delete;
	GamePlayFloor& operator=(const GamePlayFloor& _Other) = delete;
	GamePlayFloor& operator=(GamePlayFloor&& _Other) noexcept = delete;


protected:
	void Start() override;

private:
};

