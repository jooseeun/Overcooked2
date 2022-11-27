#pragma once
#include "GamePlayStuff.h"
#include "Player.h"
// ���� :

enum class ObjectMoveableType
{
	None,
	Food,
	Equipment
};
enum class CookedStat
{
	NoResponse,
	Cooking,
	End
};
class GamePlayMoveable : public GamePlayStuff
{
	friend class GamePlayTool;
public:
	// constrcuter destructer
	GamePlayMoveable();
	~GamePlayMoveable();

	// delete Function
	GamePlayMoveable(const GamePlayMoveable& _Other) = delete;
	GamePlayMoveable(GamePlayMoveable&& _Other) noexcept = delete;
	GamePlayMoveable& operator=(const GamePlayMoveable& _Other) = delete;
	GamePlayMoveable& operator=(GamePlayMoveable&& _Other) noexcept = delete;

public:

	inline ObjectMoveableType GetObjectMoveableType() const
	{
		if (Enum_ObjectMoveableType_ == ObjectMoveableType::None)
		{
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayStuff::Enum_ObjectStuffType_ ����)");
		}
		return Enum_ObjectMoveableType_;
	}

protected:
	void Start() override;
	//void Update(float _DeltaTime) final;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};



protected:
	inline void SetObjectMoveableType(ObjectMoveableType _Type)
	{
		Enum_ObjectMoveableType_ = _Type;
	}

private:
	ObjectMoveableType Enum_ObjectMoveableType_;
	SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type) override;
};

