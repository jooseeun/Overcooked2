#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

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


protected:
	void Start() override;

private:
};
