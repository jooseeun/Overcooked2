#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <queue>
#include <GameEngineCore/GlobalIOManager.h>
#include "GamePacket.h"
#include "GamePlayObject.h"
// Ό³Έν :
class GamePlayObjectManager : public GameEngineActor
{
public:
	// constrcuter destructer
	GamePlayObjectManager();
	~GamePlayObjectManager();

	// delete Function
	GamePlayObjectManager(const GamePlayObjectManager& _Other) = delete;
	GamePlayObjectManager(GamePlayObjectManager&& _Other) noexcept = delete;
	GamePlayObjectManager& operator=(const GamePlayObjectManager& _Other) = delete;
	GamePlayObjectManager& operator=(GamePlayObjectManager&& _Other) noexcept = delete;

	static GamePlayObjectManager* GetInst();


	std::shared_ptr<GamePlayObject> PopData();
	void PushData(std::shared_ptr<ObjectStartPacket> _Update);

	bool Isempty();




protected:
	void Start() override;
	void Update(float _Time) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::queue<std::shared_ptr<ObjectStartPacket>> QueueMapData_;

	static GamePlayObjectManager* Inst_;
};

