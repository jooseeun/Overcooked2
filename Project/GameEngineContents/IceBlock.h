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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	IceBlockType IceBlockType_;
};

