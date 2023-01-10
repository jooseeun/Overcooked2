#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"
#include "Equipment_Plate.h"

class PlateReturn : public GamePlayStaticObject
{
public:
	PlateReturn();
	~PlateReturn();

	PlateReturn(const PlateReturn& _Other) = delete;
	PlateReturn(PlateReturn&& _Other) noexcept = delete;
	PlateReturn& operator=(const PlateReturn& _Other) = delete;
	PlateReturn& operator=(PlateReturn&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

class Tool_PlateReturn : public GamePlayTool
{

public:
	// constrcuter destructer
	Tool_PlateReturn();
	~Tool_PlateReturn();

	// delete Function
	Tool_PlateReturn(const Tool_PlateReturn& _Other) = delete;
	Tool_PlateReturn(Tool_PlateReturn&& _Other) noexcept = delete;
	Tool_PlateReturn& operator=(const Tool_PlateReturn& _Other) = delete;
	Tool_PlateReturn& operator=(Tool_PlateReturn&& _Other) noexcept = delete;

	static inline Tool_PlateReturn* GetInst()
	{
		return Inst_;
	}

	void SetPlateCooltime(std::shared_ptr<Equipment_Plate> _Plate)
	{
		Map_PlateCollTime_[_Plate] = 5.f;
	}


protected:
	void Start() override;
	void Update(float Delta) override;

	void LevelStartEvent() override;
	//void LevelEndEvent() override;


private:
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
	static Tool_PlateReturn* Inst_;

	std::map<std::shared_ptr<Equipment_Plate>, float> Map_PlateCollTime_;
};
