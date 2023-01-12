#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"
// Ό³Έν :
class Oven : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Oven();
	~Oven();

	// delete Function
	Oven(const Oven& _Other) = delete;
	Oven(Oven&& _Other) noexcept = delete;
	Oven& operator=(const Oven& _Other) = delete;
	Oven& operator=(Oven&& _Other) noexcept = delete;

	inline void SwitchInteractionOff()
	{
		IsInteraction_ = false;
	}

	inline void SwitchInteractionOn()
	{
		IsInteraction_ = true;
	}

	inline void CookingOn()
	{
		IsCooking_ = true;
	}

	inline void CookingOff()
	{
		IsCooking_ = false;
	}

	inline bool GetCookingState()
	{
		return IsCooking_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineActor> Door_;
	std::shared_ptr<GameEngineFBXStaticRenderer> DoorRenderer_;

	bool IsInteraction_;
	bool IsCooking_;
	bool IsSound_;
	bool IsSoundDone_;
	float Angle_;
};

class Tool_Oven : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Oven();
	~Tool_Oven();

	// delete Function
	Tool_Oven(const Tool_Oven& _Other) = delete;
	Tool_Oven(Tool_Oven&& _Other) noexcept = delete;
	Tool_Oven& operator=(const Tool_Oven& _Other) = delete;
	Tool_Oven& operator=(Tool_Oven&& _Other) noexcept = delete;
	inline void SetOven(std::shared_ptr<Oven> _Oven)
	{
		Oven_ = _Oven;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
	std::shared_ptr<Oven> Oven_;
};