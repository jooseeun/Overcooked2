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

	std::weak_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}

	std::vector<std::weak_ptr<GamePlayStaticObject>>& GetStaticMeshInfo()
	{
		return StaticMeshDatas_;
	}

protected:
	void Start() override;

private:
	std::weak_ptr<GameEngineFBXStaticRenderer> Renderer_;

	std::vector<std::weak_ptr<GamePlayStaticObject>> StaticMeshDatas_;
};

