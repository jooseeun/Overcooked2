#pragma once
#include "GamePlayObject.h"

// Ό³Έν :
class GamePlayMapObject : public GamePlayObject
{
	friend class MapEditorWindow;

public:
	// constrcuter destructer
	GamePlayMapObject();
	~GamePlayMapObject();

	// delete Function
	GamePlayMapObject(const GamePlayMapObject& _Other) = delete;
	GamePlayMapObject(GamePlayMapObject&& _Other) noexcept = delete;
	GamePlayMapObject& operator=(const GamePlayMapObject& _Other) = delete;
	GamePlayMapObject& operator=(GamePlayMapObject&& _Other) noexcept = delete;

public:
	void SetMapObjectMesh(const std::string& _Name);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

