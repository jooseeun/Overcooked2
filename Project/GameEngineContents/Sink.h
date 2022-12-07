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

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	static Tool_Sink* Inst_;

	//UsingDownEnum UsingDown(std::shared_ptr<GamePlayStuff> _Stuff) override;
};

