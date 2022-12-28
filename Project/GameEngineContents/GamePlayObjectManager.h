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

	static inline GamePlayObjectManager* GetInst()
	{
		return Inst_;
	}

	std::shared_ptr<GamePlayObject> PopData();
	void PushData(std::shared_ptr<ObjectStartPacket> _Update)
	{
		MapData Data;

		Data.MapObjType_ = _Update->MapObjData;
		Data.Pos_ = _Update->Pos;
		Data.Rot_ = _Update->Rot;
		Data.Scale_ = _Update->Scale;
		Data.Index_.x = static_cast<float>(_Update->ToolData);
		Data.Index_.y = static_cast<float>(_Update->IngredientData);
		Data.Index_.z = static_cast<float>(_Update->HoldObjectID);

		QueueMapData_.push(std::pair<int, MapData>(_Update->ObjectID, Data));
	}

	inline bool Isempty()
	{
		return QueueMapData_.empty();
	}



protected:
	void Start() override;
	void Update(float _Time) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::queue<std::pair<int, MapData>> QueueMapData_;

	static GamePlayObjectManager* Inst_;
};

