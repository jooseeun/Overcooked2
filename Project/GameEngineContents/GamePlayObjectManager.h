#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <queue>
#include <GameEngineCore/GlobalIOManager.h>
#include "GamePacket.h"
#include "GamePlayObject.h"
// 설명 :
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


	std::shared_ptr<GamePlayObject> PopMapDataData();
	void PopObjectInteractData();
	void PopObjectParentsSetData();
	void PopObjectParentsSetAllFrameData();
	void PushMapData(std::shared_ptr<ObjectStartPacket> _Update);
	void PushParentsSetData(std::shared_ptr<ObjectParentsSetPacket> _Packet);
	void PushObjectInteractData(std::shared_ptr<ObjectInteractUpdatePacket> _Packet);
	static void TemporaryPushData(std::shared_ptr<GameServerPacket> _Update);

	bool Isempty();

protected:
	void Start() override;
	void Update(float _Time) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::queue<std::shared_ptr<ObjectStartPacket>> QueueMapData_;
	std::queue<std::shared_ptr<ObjectInteractUpdatePacket>> QueueObjectInteraction_;
	std::queue<std::shared_ptr<ObjectParentsSetPacket>> QueueObjectParentsSet_;
	std::queue<std::shared_ptr<ObjectParentsSetAllFramePacket>> QueueObjectParentsSetAllFrame_;
	

	static GamePlayObjectManager* Inst_;

	static std::queue<std::shared_ptr<GameServerPacket>> TemporaryPacket; // 패킷 임시저장
};

