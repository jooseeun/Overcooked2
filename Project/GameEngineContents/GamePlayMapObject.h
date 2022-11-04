#pragma once
#include "GamePlayStaticObject.h"

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
	inline GameEngineCollision* GetCollision()
	{
		return Collision_;
	}

protected:
	void Start() override;

private:
	std::string Name_;

	GameEngineCollision* Collision_;

};

