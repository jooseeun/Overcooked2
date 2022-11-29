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
		return PhysicsCollision_;
	}
	inline void SetCollision(std::shared_ptr<GameEngineCollision> _Col)
	{
		PhysicsCollision_ = _Col;
	}
	inline bool GetIsThrow()
	{
		return IsThrow_;
	}

protected:

	void Gravity(); // 중력함수 -> Update에서 일단 하는중
	void Throw(float4 _Vector);
	void ThrowUpdate();
	bool StaticObjectCollisionCheck(); // 맵 오브젝트, 테이블 등등이랑 충돌하면 true 반환함수

private:
	float ThrowTime_;
	float UpTime_;
	bool IsThrow_;

	std::shared_ptr<GameEngineCollision> PhysicsCollision_;
};

