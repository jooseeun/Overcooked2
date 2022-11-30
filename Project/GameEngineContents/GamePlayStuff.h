#pragma once
#include "GamePlayObject.h"

// ���� :
enum class ObjectStuffType
{
	None,
	Tool,
	Moveable,
};
enum class HoldDownEnum
{
	Nothing,
	HoldDown,
	HoldDown_Already,
	ExitMe,
	HoldUp,
	HoldUp_Already,
};
enum class UsingDownEnum
{
	Nothing,
	Using,
	Throwing
};

class GamePlayStuff : public GamePlayObject
{
	friend class GamePlayStaticObject;
protected:
	GamePlayStuff();
public:
	// constrcuter destructer
	~GamePlayStuff();

	// delete Function
	GamePlayStuff(const GamePlayStuff& _Other) = delete;
	GamePlayStuff(GamePlayStuff&& _Other) noexcept = delete;
	GamePlayStuff& operator=(const GamePlayStuff& _Other) = delete;
	GamePlayStuff& operator=(GamePlayStuff&& _Other) noexcept = delete;



	inline ObjectStuffType GetObjectStuffType() const
	{
		if (Enum_ObjectStuffType_ == ObjectStuffType::None)
		{
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayStuff::Enum_ObjectStuffType_ ����)");
		}
		return Enum_ObjectStuffType_;
	}

	inline ToolInfo GetToolInfoType()
	{
		return Enum_ToolInfo_;
	}

	inline void SetToolInfoType(ToolInfo _Info)
	{
		Enum_ToolInfo_ = _Info;
	}

	//virtual void SetParentObject(std::shared_ptr<GameEngineUpdateObject> _Object);


	inline virtual HoldDownEnum HoldDown(std::shared_ptr<Player> _Player)
	{
		return HoldDownEnum::Nothing;
	};

	inline virtual UsingDownEnum UsingDown(std::shared_ptr<Player> _Player)
	{
		return UsingDownEnum::Nothing;
	};


protected:

	void Start() override;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

protected:
	inline void SetObjectStuffType(ObjectStuffType _Type)
	{
		Enum_ObjectStuffType_ = _Type;
	}

private:
	float4 Pos;
	SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type) final;

	// Enum
private:
	ObjectStuffType Enum_ObjectStuffType_;

private:
	ToolInfo Enum_ToolInfo_;
};

