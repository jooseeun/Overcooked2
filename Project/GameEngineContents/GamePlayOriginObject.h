#pragma once
#include <GameEngineCore/GameEngineActor.h>

//���ĵ� �� ������Ʈ�� ��ġ�� �� ���Ǵ� ���� ����
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

