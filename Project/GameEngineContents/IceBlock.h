#pragma once
#include "GamePlayMapObject.h"

enum class IceBlockType
{
	Ice01,
	Ice02,
	Ice03,
	Ice04,
	Ice06,
	Ice08,
	Ice10,
	Ice11,
	Max,
};

// ���� :
class IceBlock : public GamePlayMapObject
{
public:
	// constrcuter destructer
	IceBlock();
	~IceBlock();

	// delete Function
	IceBlock(const IceBlock& _Other) = delete;
	IceBlock(IceBlock&& _Other) noexcept = delete;
	IceBlock& operator=(const IceBlock& _Other) = delete;
	IceBlock& operator=(IceBlock&& _Other) noexcept = delete;

public:
	inline void SetIceBlockType(IceBlockType _Type)
	{
		IceBlockType_ = _Type;
	}

	void SetIceBlockMesh(IceBlockType _Type);

	inline void SwitchMovable()
	{
		IsMovable_ = !IsMovable_;
	}

	void RotateIce(float _DeltaTime);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Move(float _DeltaTime);

private:
	IceBlockType IceBlockType_;
	float4 MoveDir_;

	float RandomX_;
	float RandomY_;
	float Angle_;
	float MaxAngle_;
	float AngleDir_;

	bool IsMovable_;
	bool IsDirChange_;
	bool IsLeft_;
};

