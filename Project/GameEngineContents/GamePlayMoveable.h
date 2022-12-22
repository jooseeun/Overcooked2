#pragma once
#include "GamePlayStuff.h"
#include "Player.h"
#include "CookingBar.h"
// 설명 :

enum class ObjectMoveableType
{
	None,
	Food,
	Equipment,
	Bowl
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
enum class ObjectToolType;
class GamePlayMoveable : public GamePlayStuff
{
	friend class GamePlayTool;
	friend class CombinFood;
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
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayMoveable::Enum_ObjectStuffType_ 설정)");
		}
		return Enum_ObjectMoveableType_;
	}
	inline PlayerHoldType GetHoldType() const
	{
		if (Enum_HoldType_ == PlayerHoldType::Max)
		{
			MsgBoxAssert("Object의 PlayerHoldType이 설정되지 않았습니다. (GamePlayMoveable::Enum_HoldType_ 설정)");
		}
		return Enum_HoldType_;
	}


	inline float GetCookingGage() const
	{
		return CookingGage_;
	}
	inline void SwitchingCookingGage(std::shared_ptr<GamePlayMoveable> _Moveable)
	{
		float CookingGage = CookingGage_;
		CookingGage_ = _Moveable->CookingGage_;
		_Moveable->CookingGage_ = CookingGage;
	}

	inline std::shared_ptr<CookingBar> GetCookingBar()
	{
		return CookingBar_;
	}
	inline void ReSetCookingGage()
	{
		CookingGage_ = 0;
	}

	bool Input_Manual(std::shared_ptr<Player> _Player, float _Delta, float _MaxTime);
	bool Input_Auto(float _Delta, float _MaxTime);
	virtual bool AutoTrim(float _DeltaTim, ObjectToolType _Tool) { return false; }
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
	bool TrimmingFirstTime_;


private:
	ObjectMoveableType Enum_ObjectMoveableType_;
	float CookingGage_;
	PlayerHoldType Enum_HoldType_;
	std::shared_ptr<CookingBar> CookingBar_;


	virtual void FinishTrimmingFirst() {}
	virtual void FinishTrimming() {}

};

