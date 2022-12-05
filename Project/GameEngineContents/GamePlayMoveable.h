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
class GamePlayFood;
class GamePlayEquipment;
class GamePlayBowl;
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
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayMoveable::Enum_ObjectStuffType_ ����)");
		}
		return Enum_ObjectMoveableType_;
	}
	inline PlayerHoldType GetHoldType() const
	{
		if (Enum_HoldType_ == PlayerHoldType::Max)
		{
			MsgBoxAssert("Object�� PlayerHoldType�� �������� �ʾҽ��ϴ�. (GamePlayMoveable::Enum_HoldType_ ����)");
		}
		return Enum_HoldType_;
	}


	inline float GetCookingGage() const
	{
		return CookingGage_;
	}
	bool Input_Manual(std::shared_ptr<Player> _Player, float _Delta, float _MaxTime);
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
	inline void SetHoldType(PlayerHoldType _Type)
	{
		Enum_HoldType_ = _Type;
	}

private:
	ObjectMoveableType Enum_ObjectMoveableType_;
	float CookingGage_;
	bool TrimmingFirstTime_;
	PlayerHoldType Enum_HoldType_;

	virtual void FinishTrimmingFirst() {}
	virtual void FinishTrimming() {}

	

};

