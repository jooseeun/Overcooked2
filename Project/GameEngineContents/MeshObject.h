#pragma once
#include "GamePlayObject.h"
// Ό³Έν :
class MeshObject : public GamePlayObject
{
public:
	// constrcuter destructer
	MeshObject();
	~MeshObject();

	// delete Function
	MeshObject(const MeshObject& _Other) = delete;
	MeshObject(MeshObject&& _Other) noexcept = delete;
	MeshObject& operator=(const MeshObject& _Other) = delete;
	MeshObject& operator=(MeshObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

