#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "MapDataParser.h"

#include "InGameUIActor.h"

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
	void Start() final;
	void Update(float _DeltaTime) final;

	virtual void PlayLevelStart() = 0;
	virtual void PlayLevelUpdate(float _DeltaTime) = 0;

	void End() override;

	void LevelStartEvent() final;
	virtual void PlayLevelStartEvent() {}; //LevelStartEvent ���� �� �Լ� �������ּ���!!

	MapDataParser DataParser_;
private:
	bool IsLevelStartFirst_ = true; //���� �̵��� �� ó�� �� ��� ���ҽ� �ε�� ���ϴ�
	std::shared_ptr< InGameUIActor> UIActor_;
};