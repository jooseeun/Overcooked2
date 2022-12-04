#pragma once
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
// ���� :
enum class AutoOption
{
	NoResponse,
	Auto,
	Manual
};
enum class ObjectToolType
{
	  None
	, CuttingBoard // ����
	, Cooker       // ����������
	, TrashCan     // ��������
	, Mixer        // �ͼ���
	, PlateReturn  // ���ùݳ�
	, Sink         // ��ũ��
	, FoodBox      // 
	, Servicehatch //
	, Rail		   //
	, Dispenser	   //

};
class Player;
class GamePlayTool : public GamePlayStuff
{
public:
	// constrcuter destructer
	GamePlayTool();
	~GamePlayTool();

	// delete Function
	GamePlayTool(const GamePlayTool& _Other) = delete;
	GamePlayTool(GamePlayTool&& _Other) noexcept = delete;
	GamePlayTool& operator=(const GamePlayTool& _Other) = delete;
	GamePlayTool& operator=(GamePlayTool&& _Other) noexcept = delete;

	inline std::shared_ptr<GamePlayMoveable> GetCurrentMoveable() const
	{
		return Moveable_Current_;
	}
	inline virtual void ReSetCurrentMoveable()
	{
		//Moveable_Current_->GetTransform().SetLocalPosition(float4::ZERO);
		Moveable_Current_.reset();
	}

	inline ObjectToolType GetObjectToolType()
	{
		return Enum_ObjectToolType_;
	}

protected:
	void Start() override;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:

	inline void SetInteractOption(AutoOption _Option)
	{
		InteractOption_Current_ = _Option;
	}


private:
	std::shared_ptr<GamePlayMoveable> Moveable_Current_;

	//HoldDownEnum HoldDown(std::);
protected:
	inline void SetObjectToolType(ObjectToolType _Type)
	{
		Enum_ObjectToolType_ = _Type;
	}
	virtual void SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child);
	void SetMoveable(std::shared_ptr<Player> _Player);

private:
	ObjectToolType Enum_ObjectToolType_;
	AutoOption InteractOption_Current_;

	float4 MoveablePos_;


	HoldDownEnum HoldOn(std::shared_ptr<Player> _Player) override;

	inline HoldDownEnum HoldOn(std::shared_ptr<GamePlayStaticObject> _Object) override
	{
	MsgBoxAssert("����")
		return HoldDownEnum::Nothing;
	
	};

	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable> _Moveable) override;

	// Bloom
public:
	inline void SetHighlightEffectOff() override
	{
		GamePlayObject::SetHighlightEffectOff();
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->SetHighlightEffectOff();
		}
	}
	inline void SetHighlightEffectOn() override
	{
		GamePlayObject::SetHighlightEffectOn();
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->SetHighlightEffectOn();
		}
	}
};

