#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "MapDataParser.h"

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
	void LevelStartEvent() final;
	virtual void PlayLevelStartEvent() {}; //LevelStartEvent ���� �� �Լ� �������ּ���!!

	MapDataParser DataParser_;
private:
	bool IsLevelStartFirst_ = true; //���ҽ� �ε�� ���ϴ�
};