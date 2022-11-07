#pragma once
#include <GameEngineCore/GameEngineActor.h>

//정렬된 맵 오브젝트를 배치할 때 사용되는 기준 엑터
class GamePlayStaticObject;
class GamePlayOriginObject : public GameEngineActor
{
public:
	GamePlayOriginObject();
	~GamePlayOriginObject();

	GamePlayOriginObject(const GamePlayOriginObject& _Other) = delete;
	GamePlayOriginObject(GamePlayOriginObject&& _Other) noexcept = delete;
	GamePlayOriginObject& operator=(const GamePlayOriginObject& _Other) = delete;
	GamePlayOriginObject& operator=(GamePlayOriginObject&& _Other) noexcept = delete;

	GameEngineFBXStaticRenderer* GetRenderer()
	{
		return Renderer_;
	}

	std::vector<GamePlayStaticObject*>& GetStaticMeshInfo()
	{
		return StaticMeshDatas_;
	}

protected:
	void Start() override;

private:
	GameEngineFBXStaticRenderer* Renderer_;

	std::vector<GamePlayStaticObject*> StaticMeshDatas_;
};

