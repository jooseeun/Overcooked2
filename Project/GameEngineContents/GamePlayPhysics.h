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

	inline void SetCollision(std::shared_ptr<GameEngineCollision> _Col) // 원래 사용하던 collision 넣어주면됨, 아님 새로 만들어 주어서 넣어주면 됩니다
	{
		PhysicsCollision_ = _Col;
	}

	inline bool GetIsThrow() const
	{
		return IsThrow_;
	}

	inline float GetCurKineticEnergy() const
	{
		return CurKineticEnergy_;
	}

	inline void SetCurSpeed(float _Speed) // 오브젝트가 들고있는 운동에너지를 설정해주기 위해서 속력 넣어주여야 한다.
	{
		CurSpeed_ = _Speed;
	}

	inline float GetCurSpeed() const
	{
		return CurSpeed_;
	}

	inline void SetCurMass(float _Mass) // 오브젝트 질량 설정
	{
		CurMass_ = _Mass;
	}

	inline float GetCurMass() const
	{
		return CurMass_;
	}
protected:

	void Gravity(); // 중력함수 -> Update에서 일단 하는중
	void Throw(float4 _Vector);

	bool StaticObjectCollisionCheck(); // 맵 오브젝트, 테이블 등등이랑 충돌하면 true 반환함수

	void ColCheckPlayer(); //플레이어한테 차이거나 하면은 밀리는 함수
	CollisionReturn MoveFromPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	void CalculateKineticEnergy();
	void CalculateKineticEnergyMass();

private:
	float CurKineticEnergy_;
	float CurSpeed_;
	float CurMass_;

	float ThrowTime_;
	float UpTime_;
	bool IsThrow_;

	std::shared_ptr<GameEngineCollision> PhysicsCollision_;
};

