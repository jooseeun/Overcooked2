#pragma once
#include "GamePlayTool.h"
// Ό³Έν :
class Tool_CuttingBoard final : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_CuttingBoard();
	~Tool_CuttingBoard();

	// delete Function
	Tool_CuttingBoard(const Tool_CuttingBoard& _Other) = delete;
	Tool_CuttingBoard(Tool_CuttingBoard&& _Other) noexcept = delete;
	Tool_CuttingBoard& operator=(const Tool_CuttingBoard& _Other) = delete;
	Tool_CuttingBoard& operator=(Tool_CuttingBoard&& _Other) noexcept = delete;

	//Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	Input_InteractOption Input_Action() override
	{
		return Input_InteractOption::NoResponse;
	}
protected:
	void Start() override;
private:

};

