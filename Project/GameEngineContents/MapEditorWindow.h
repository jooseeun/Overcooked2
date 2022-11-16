#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapDataParser.h"

class GamePlayOriginObject;
class GamePlayLevel;
class LevelActor;
class GamePlayMapObject;
class GamePlayStaticObject;
class MapEditorWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	MapEditorWindow();
	~MapEditorWindow();

	// delete Function
	MapEditorWindow(const MapEditorWindow& _Other) = delete;
	MapEditorWindow(MapEditorWindow&& _Other) noexcept = delete;
	MapEditorWindow& operator=(const MapEditorWindow& _Other) = delete;
	MapEditorWindow& operator=(MapEditorWindow&& _Other) noexcept = delete;

	void UnSortToolTab();
	void SortToolTab();

	void ShowLevelSelectTable();

	void SetLevel(GameEngineLevel* _CurLevel)
	{
		CurLevel_ = _CurLevel;
	}

	std::vector<std::weak_ptr<GamePlayMapObject>>& GetUnSortActorList()
	{
		return UnSortActorList_;
	}

	std::vector<std::string>& GetAllUnSortActorName()
	{
		return AllUnSortActorName_;
	}

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
	std::vector<std::weak_ptr<GamePlayMapObject>> UnSortActorList_;
	std::vector<std::weak_ptr<GamePlayStaticObject>> SortActorList_;

	std::vector<std::string> Prefabs_;

	GameEngineLevel* CurLevel_;

	std::weak_ptr<LevelActor> LevelActor_;

	//타일맵 기준 엑터
	std::vector<std::weak_ptr<GamePlayOriginObject>> Origins_;

	//현재 생성한 타일
	std::weak_ptr<GamePlayStaticObject> CurStaticMesh_;

	MapDataParser DataParser_;

	int LevelIndex_;

private:
	float4 Rotation_;
	float4 Position_;
	float4 CollisionScale_;

	std::string ObjectName_;

	std::vector<std::string> AllUnSortActorName_;

	bool IsUnSort_;
	bool IsSort_;

	bool IsCandleCheckBox_;
};

