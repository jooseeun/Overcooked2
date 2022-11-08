#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

//쓰레기통
class TrashCan : public GamePlayStaticObject
{
public:
	TrashCan();
	~TrashCan();

	TrashCan(const TrashCan& _Other) = delete;
	TrashCan(TrashCan&& _Other) noexcept = delete;
	TrashCan& operator=(const TrashCan& _Other) = delete;
	TrashCan& operator=(TrashCan&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};


// 설명 :
class Tool_TrashCan : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_TrashCan();
	~Tool_TrashCan();

	// delete Function
	Tool_TrashCan(const Tool_TrashCan& _Other) = delete;
	Tool_TrashCan(Tool_TrashCan&& _Other) noexcept = delete;
	Tool_TrashCan& operator=(const Tool_TrashCan& _Other) = delete;
	Tool_TrashCan& operator=(Tool_TrashCan&& _Other) noexcept = delete;



protected:
	void Start() override;

	Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	Input_UsingOption Input_Action(Player* _Player) override
	{
		return Input_UsingOption::NoResponse; // 수정요
	}
private:

};

