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

	//void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) override {};
	inline std::shared_ptr<GameEngineActor> GetKnife()
	{
		return Knife_;
	}

	void SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child) override
	{
		GamePlayTool::SetMoveable(_Child);
		Knife_->Off();
	}
protected:
	void Start() override;
private:
	
	//HoldDownEnum HoldDown(std::shared_ptr<Player> _Player) final;
	bool CanHoldThis(std::shared_ptr<GamePlayMoveable> _Moveable) final;

	std::shared_ptr<GameEngineActor> Knife_;

};

