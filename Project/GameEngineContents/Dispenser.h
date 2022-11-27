#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

// Ό³Έν :
class Dispenser : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Dispenser();
	~Dispenser();

	// delete Function
	Dispenser(const Dispenser& _Other) = delete;
	Dispenser(Dispenser&& _Other) noexcept = delete;
	Dispenser& operator=(const Dispenser& _Other) = delete;
	Dispenser& operator=(Dispenser&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

class Tool_Dispenser : public GamePlayTool
{

public:
	// constrcuter destructer
	Tool_Dispenser();
	~Tool_Dispenser();

	// delete Function
	Tool_Dispenser(const Tool_Dispenser& _Other) = delete;
	Tool_Dispenser(Tool_Dispenser&& _Other) noexcept = delete;
	Tool_Dispenser& operator=(const Tool_Dispenser& _Other) = delete;
	Tool_Dispenser& operator=(Tool_Dispenser&& _Other) noexcept = delete;


protected:
	void Start() override;

private:
};

