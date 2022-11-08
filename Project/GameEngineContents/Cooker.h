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

	Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;

	Input_UsingOption Input_Action(Player* _Player) override
	{
		return Input_UsingOption::NoResponse; // 수정요
	}

protected:
	void Start() override;
private:

};

