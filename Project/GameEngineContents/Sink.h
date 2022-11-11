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
class Equipment_Plate;
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

	Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override;
	Input_PickUpOption CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object) override;
	Input_UsingOption Input_ActionToManual(std::shared_ptr<Player> _Player, float _DeltaTime) override;
	void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) override;
private:



	std::shared_ptr<Equipment_Plate> ReturnCleanPlate_;
};


