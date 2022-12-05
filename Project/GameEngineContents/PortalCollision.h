#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GlobalIOManager.h>

// Ό³Έν :

class GameEngineCollision;
class PortalCollision : public GameEngineActor
{
public:
	// constrcuter destructer
	PortalCollision();
	~PortalCollision();

	// delete Function
	PortalCollision(const PortalCollision& _Other) = delete;
	PortalCollision(PortalCollision&& _Other) noexcept = delete;
	PortalCollision& operator=(const PortalCollision& _Other) = delete;
	PortalCollision& operator=(PortalCollision&& _Other) noexcept = delete;

	inline MapObjType GetPotalType()
	{
		return PotalType_;
	}

	inline void SetPotalType(MapObjType _PotalType)
	{
		PotalType_ = _PotalType;
	}

	inline void SetNextPotal(std::shared_ptr<PortalCollision> _NextPotal)
	{
		NextPotal_ = _NextPotal;
	}
	inline void SetNextPos(float4 _NextPos)
	{
		NextPos_ = _NextPos;
	}
	inline void SetActor(std::shared_ptr<GameEngineActor> _InterActor)
	{
		InterActor_ = _InterActor;
	}
	bool IsBig_;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void BigActor();

private:
	MapObjType PotalType_;
	std::shared_ptr<GameEngineCollision> PotalCol_;
	std::shared_ptr<PortalCollision> NextPotal_;
	std::shared_ptr<GameEngineActor> InterActor_;
	float4 NextPos_;

	CollisionReturn SmallActor(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
};

