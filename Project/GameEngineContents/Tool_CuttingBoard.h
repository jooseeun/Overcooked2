#pragma once
#include "GamePlayTool.h"
// ���� :
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
	Input_UsingOption Input_ActionToManual(std::shared_ptr<Player> _Player, float _DeltaTime) override
	{
		return Input_UsingOption::Using; // ������
	}
	void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) override {};
protected:
	void Start() override;
private:

};

