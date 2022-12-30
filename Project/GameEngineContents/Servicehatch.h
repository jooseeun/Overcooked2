#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

//요리 내는 창구
class Servicehatch : public GamePlayStaticObject
{
public:
	Servicehatch();
	~Servicehatch();

	Servicehatch(const Servicehatch& _Other) = delete;
	Servicehatch(Servicehatch&& _Other) noexcept = delete;
	Servicehatch& operator=(const Servicehatch& _Other) = delete;
	Servicehatch& operator=(Servicehatch&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	RenderOption RenderOption_;

};


class Tool_Servicehatch : public GamePlayTool
{

public:
	// constrcuter destructer
	Tool_Servicehatch();
	~Tool_Servicehatch();

	// delete Function
	Tool_Servicehatch(const Tool_Servicehatch& _Other) = delete;
	Tool_Servicehatch(Tool_Servicehatch&& _Other) noexcept = delete;
	Tool_Servicehatch& operator=(const Tool_Servicehatch& _Other) = delete;
	Tool_Servicehatch& operator=(Tool_Servicehatch&& _Other) noexcept = delete;


protected:
	void Start() override;

private:
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
};

