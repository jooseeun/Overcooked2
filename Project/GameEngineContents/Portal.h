#pragma once
#include "GamePlayMapObject.h"

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
	void SetPortalMesh(MapObjType _PortalType);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> BlendRenderer_;;
};

