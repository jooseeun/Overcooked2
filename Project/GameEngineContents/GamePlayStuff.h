#pragma once
#include "GamePlayObject.h"

// 설명 :
enum class ObjectStuffType
{
	None,
	Tool,
	Moveable,
};
enum class HoldDownEnum
{
	Nothing,
	HoldUp,
	HoldDown,
};

enum class UsingDownEnum
{
	Nothing,
	Using,
	Throwing
};


class GamePlayTool;
class Player;
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
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectStuffType_ 설정)");
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


	//inline virtual HoldDownEnum HoldOn(std::shared_ptr<Player>* _Player)
	//{
	//	return HoldDownEnum::Nothing;
	//};
	//inline virtual HoldDownEnum HoldOn(std::shared_ptr<GamePlayStaticObject>* _Player)
	//{
	//	return HoldDownEnum::Nothing;
	//};
	inline virtual HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
	{
		return HoldDownEnum::Nothing;
	}

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

protected:
	bool IsSound_;
	bool IsSoundDone_;
	float SoundTime_;

	GameEngineSoundPlayer ObjSoundPlayer_;

private:
	float4 Pos;
	//SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable = nullptr, bool _FromNet = false) final;

	// Enum
private:
	ObjectStuffType Enum_ObjectStuffType_;

private:
	ToolInfo Enum_ToolInfo_;

	void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override
	{
		Packet->ToolData = Enum_ToolInfo_;
	}
};

