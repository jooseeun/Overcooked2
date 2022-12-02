#pragma once
#include "GamePlayMapObject.h"

// Ό³Έν :
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

