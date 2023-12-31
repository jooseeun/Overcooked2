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

	//void Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable) override {};
	inline std::shared_ptr<GameEngineActor> GetKnife()
	{
		return Knife_;
	}

	inline void SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child) override
	{
		GamePlayTool::SetMoveable(_Child);
		Knife_->Off();
	}

	inline void ReSetCurrentMoveable() override
	{
		GamePlayTool::ReSetCurrentMoveable();
		Knife_->On();
	}
protected:
	void Start() override;
private:
	//bool HoldDown(std::shared_ptr<Player> _Player) final;
	//HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable> _Moveable) override;

	UsingDownEnum UsingDown(std::shared_ptr<Player> _Player) final;
	bool Trimming_;

	std::shared_ptr<GameEngineActor> Knife_;

	inline void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override
	{
		Packet->ToolData = GetToolInfoType();
	}

};

