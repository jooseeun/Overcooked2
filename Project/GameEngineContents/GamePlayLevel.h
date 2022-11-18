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
	virtual void PlayLevelStartEvent() {}; //LevelStartEvent 말고 이 함수 구현해주세요!!

	MapDataParser DataParser_;
private:
	bool IsLevelStartFirst_ = true; //레벨 이동을 맨 처음 할 경우 리소스 로드로 갑니다
	std::shared_ptr< InGameUIActor> UIActor_;
};