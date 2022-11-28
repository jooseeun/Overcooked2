#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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

	void Gravity(); // 중력함수 -> Update에서 일단 하는중
	bool StaticObjectCollisionCheck(); // 맵 오브젝트, 테이블 등등이랑 충돌하면 true 반환함수

private:
	std::shared_ptr<GameEngineCollision> PhysicsCollision;
};

