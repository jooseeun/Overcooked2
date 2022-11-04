#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class GamePlayLevel : public GameEngineLevel
{
public:
	GamePlayLevel();
	~GamePlayLevel();

	GamePlayLevel(const GamePlayLevel& _Other) = delete;
	GamePlayLevel(GamePlayLevel&& _Other) noexcept = delete;
	GamePlayLevel& operator=(const GamePlayLevel& _Other) = delete;
	GamePlayLevel& operator=(GamePlayLevel&& _Other) noexcept = delete;

protected:
	void Start() override = 0;
	void Update(float _DeltaTime) override;
	void End() override;

	//정렬된 맵 데이터를 읽어온다
	void ParsingSortMapData();

private:

};