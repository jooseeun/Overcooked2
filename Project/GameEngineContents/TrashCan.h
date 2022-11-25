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

	//void Input_ActionToAuto_Update(std::shared_ptr<GamePlayMoveable> _Moveable, float _DeltaTime) override;
	Input_PickUpOption CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object) override;
	Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override;
	//Input_UsingOption Input_ActionToManual(Player* _Player) override
	//{
	//	return Input_UsingOption::NoResponse; // 수정요
	//}

	//void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) override;
private:
	
};

