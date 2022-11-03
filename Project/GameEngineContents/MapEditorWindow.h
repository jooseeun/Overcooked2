#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class GamePlayLevel;
class LevelActor;
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

	std::vector<class GamePlayMapObject*>& GetUnSortActorList()
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
	std::vector<class GamePlayMapObject*> UnSortActorList_;
	std::vector<class GamePlayStaticObject*> SortActorList_;

	std::vector<std::string> Prefabs_;

	GameEngineLevel* CurLevel_;

	LevelActor* LevelActor_;

	//타일맵 기준 엑터
	std::vector<GamePlayMapObject*> Origins_;

	//현재 생성한 타일
	GamePlayStaticObject* CurStaticMesh_;

private:
	float4 Rotation_;
	float4 Position_;
	float4 Scale_;

	std::string ObjectName_;
	int Index_;

	std::vector<std::string> AllUnSortActorName_;
};

