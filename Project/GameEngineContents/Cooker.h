#pragma once
#include "GamePlayStaticObject.h"
// Ό³Έν :
class Cooker : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Cooker();
	~Cooker();

	// delete Function
	Cooker(const Cooker& _Other) = delete;
	Cooker(Cooker&& _Other) noexcept = delete;
	Cooker& operator=(const Cooker& _Other) = delete;
	Cooker& operator=(Cooker&& _Other) noexcept = delete;

	float4 GetToolPos() override
	{
		ToolPos_ = GetTransform().GetWorldPosition() + float4{ 0, 60.f };

		return ToolPos_;
	};

protected:
	void Start() override;
private:

};
