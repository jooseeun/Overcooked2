#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

enum class SinkType
{
	Normal,
	Wizard
};

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

	void SetSinkMesh(SinkType _Type);

protected:
	void Start() override;

private:

	std::shared_ptr<GameEngineCollision> Collision_Sink_;
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

	static Tool_Sink* GetInst()
	{
		return Inst_;
	}

protected:
	void Start() override;

private:
	static Tool_Sink* Inst_;
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;

};

