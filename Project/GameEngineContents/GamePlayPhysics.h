#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class GameEngineCollision;
class GamePlayPhysics : public GameEngineActor
{
public:
	// constrcuter destructer
	GamePlayPhysics();
	~GamePlayPhysics();

	// delete Function
	GamePlayPhysics(const GamePlayPhysics& _Other) = delete;
	GamePlayPhysics(GamePlayPhysics&& _Other) noexcept = delete;
	GamePlayPhysics& operator=(const GamePlayPhysics& _Other) = delete;
	GamePlayPhysics& operator=(GamePlayPhysics&& _Other) noexcept = delete;

	inline std::shared_ptr<GameEngineCollision> GetCollision() const
	{
		return PhysicsCollision;
	}

protected:
	void Update(float _DeltaTime);

	void Gravity(); // �߷��Լ� -> Update���� �ϴ� �ϴ���
	bool StaticObjectCollisionCheck(); // �� ������Ʈ, ���̺� ����̶� �浹�ϸ� true ��ȯ�Լ�

private:
	std::shared_ptr<GameEngineCollision> PhysicsCollision;
};

