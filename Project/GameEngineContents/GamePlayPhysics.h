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
		return PhysicsCollision_;
	}

	inline void SetCollision(std::shared_ptr<GameEngineCollision> _Col) // ���� ����ϴ� collision �־��ָ��, �ƴ� ���� ����� �־ �־��ָ� �˴ϴ�
	{
		PhysicsCollision_ = _Col;
	}

	inline bool GetIsThrow()
	{
		return IsThrow_;
	}

protected:

	void Gravity(); // �߷��Լ� -> Update���� �ϴ� �ϴ���

	void ColCheckPlayer(); //�÷��̾����� ���̰ų� �ϸ��� �и��� �Լ�
	CollisionReturn MoveFromPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);


	void Throw(float4 _Vector);

	bool StaticObjectCollisionCheck(); // �� ������Ʈ, ���̺� ����̶� �浹�ϸ� true ��ȯ�Լ�

private:
	float ThrowTime_;
	float UpTime_;
	bool IsThrow_;

	std::shared_ptr<GameEngineCollision> PhysicsCollision_;
};

