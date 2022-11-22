#pragma once
#include "GamePlayStuff.h"
#include "Player.h"
// 설명 :

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
	inline Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override
	{
		return Input_PickUpOption::NoResponse;
	}
	inline Input_PickUpOption Input_PickUp(std::shared_ptr<Player> _Player) override
	{
		_Player->Input_PickUp(_Player);
		_Player->SetCurHoldType(PlayerHoldType::CanThrow);
		GetCollisionObject()->Off();
		return Input_PickUpOption::PickUp;
	}

	inline ObjectMoveableType GetObjectMoveableType() const
	{
		if (Enum_ObjectMoveableType_ == ObjectMoveableType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectStuffType_ 설정)");
		}
		return Enum_ObjectMoveableType_;
	}

	// Cooking
	inline float GetCookingTime() const
	{
		return CookingGage_;
	}
	inline virtual void PlusCookingTime(float _Time)
	{
		CookingGage_ += _Time;
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




	//inline CookedStat GetCookedStat() const
	//{
	//	return CookedStat_Current_;
	//}
	//inline void SetCookedStat(CookedStat _Stat)
	//{
	//	CookedStat_Current_ = _Stat;
	//}

	//virtual CookedStat Cook_Start_Child() = 0;
	//inline virtual void Cook_Update_Child(float _Delta)
	//{
	//	CookingGage_ += _Delta;
	//}
	//inline virtual CookedStat Cook_Check_Child()
	//{
	//	if (CookingGage_ >= 1.f)
	//	{
	//		return CookedStat::Cooked;
	//	}
	//	else
	//	{
	//		return CookedStat::Cooking;
	//	}
	//}
	//virtual GamePlayMoveable* Cook_End_Child() = 0;

private:
	ObjectMoveableType Enum_ObjectMoveableType_;

	float CookingGage_;



	//CookedStat CookedStat_Current_;


	//CookedStat Cook_Update(float _Delta);


	//inline GamePlayMoveable* Cook_End()
	//{
	//	//MsgBoxAssert("예외처리용1, 컨텐츠 담당자에게 확인");
	//	return Cook_End_Child();
	//}
};

