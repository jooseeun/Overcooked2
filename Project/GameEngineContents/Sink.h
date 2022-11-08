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

	inline int GetStack() const
	{
		return StackValue_;
	}

	inline void SetPlusStack()
	{
		++StackValue_;
	}

	inline void SetZeroStack()
	{
		StackValue_ = 0;
	}

protected:
	void Start() override;


	Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	Input_UsingOption Input_Action(Player* _Player) override;
private:
	int StackValue_;
};


