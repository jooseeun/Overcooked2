#pragma once
#include "GamePlayTool.h"
#include "GamePlayStaticObject.h"
// 설명 :
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


// 설명 :
class Tool_Cooker : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Cooker();
	~Tool_Cooker();

	// delete Function
	Tool_Cooker(const Tool_Cooker& _Other) = delete;
	Tool_Cooker(Tool_Cooker&& _Other) noexcept = delete;
	Tool_Cooker& operator=(const Tool_Cooker& _Other) = delete;
	Tool_Cooker& operator=(Tool_Cooker&& _Other) noexcept = delete;

	//HoldDownEnum HoldDown(std::shared_ptr<GamePlayStuff> _Stuff) override;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

