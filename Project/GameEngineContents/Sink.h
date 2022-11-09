#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

//ΩÃ≈©¥Î
class Sink : public GamePlayStaticObject
{
public:
	Sink();
	~Sink();

	Sink(const Sink& _Other) = delete;
	Sink(Sink&& _Other) noexcept = delete;
	Sink& operator=(const Sink& _Other) = delete;
	Sink& operator=(Sink&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

// º≥∏Ì :
class Tool_Sink : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Sink();
	~Tool_Sink();

	// delete Function
	Tool_Sink(const Tool_Sink& _Other) = delete;
	Tool_Sink(Tool_Sink&& _Other) noexcept = delete;
	Tool_Sink& operator=(const Tool_Sink& _Other) = delete;
	Tool_Sink& operator=(Tool_Sink&& _Other) noexcept = delete;



protected:
	void Start() override;

	Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) override;
	Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	Input_UsingOption Input_ActionToManual(Player* _Player, float _DeltaTime) override;
	void Input_Action_End(GamePlayMoveable* _Moveable) override;
private:

};


