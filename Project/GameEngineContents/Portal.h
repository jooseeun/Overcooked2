#pragma once
#include "GamePlayMapObject.h"

enum class PortalType
{
	Blue,
	Purple,
	Max,
};

// Ό³Έν :
class Portal : public GamePlayMapObject
{
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

public:
	inline PortalType GetPortalType()
	{
		return PortalType_;
	}

	inline void SetPortalType(PortalType _PortalType)
	{
		PortalType_ = _PortalType;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	PortalType PortalType_;
};

