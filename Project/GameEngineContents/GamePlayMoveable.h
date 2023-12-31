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
	Bowl,
	Dish
};
enum class CookedStat
{
	NoResponse,
	Cooking,
	End
};

enum class MoveableState
{
	Idle,
	Cooking,
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

	inline void CookingGageHalf()
	{
		float Gage = CookingGage_;
		if (Gage >= 200.f)
		{
			return;
		}
		else if (100.f < Gage && 200.f > Gage)
		{
			Gage = 100.f;
		}
		CookingGage_ = Gage * 0.5f;
	}


	bool Input_Manual(std::shared_ptr<Player> _Player, float _Delta, float _MaxTime);
	bool Input_Auto(float _Delta, float _MaxTime);
	virtual bool AutoTrim(float _DeltaTim, ObjectToolType _Tool) { return false; }

	// Server
	void SendObjectUpdatePacket()
	{
		if (ServerInitManager::Net && ServerInitManager::Net->GetIsHost())
		{
			std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
			Packet->ObjectID = GetNetID();
			Packet->Type = ServerObjectType::Object;
			Packet->State = IsDeath() ? ServerObjectBaseState::Base : ServerObjectBaseState::Death;
			Packet->Pos = GetTransform().GetWorldPosition();
			Packet->Rot = GetTransform().GetWorldRotation();
			Packet->Scale = GetTransform().GetWorldScale();
			ServerInitManager::Net->SendPacket(Packet);
		}
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void Update(float _DeltaTime) final;
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	//void LevelEndEvent() override {};

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

	SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable = nullptr, bool _FromNet = false) override;


	virtual void FinishTrimmingFirst() {}
	virtual void FinishTrimming() {}


	// server
	void SendCookingPacket()
	{
		if (nullptr != ServerInitManager::Net)
		{ 
			if (ServerInitManager::Net->GetIsHost())
			{
				std::shared_ptr<ObjectCookingGagePacket> Packet = std::make_shared<ObjectCookingGagePacket>();
				Packet->ObjectID = GetNetID();
				Packet->CookingGage = CookingGage_;
				ServerInitManager::Net->SendPacket(Packet);
			}
		}
	}

	void SetServerCookingGage(float _Time) override
	{
		CookingGage_ = _Time;
		if (CookingGage_ > 100.f)
		{
			if (TrimmingFirstTime_ == false)
			{
				// 플레이어, UI에게 끝났다고 신호
				TrimmingFirstTime_ = true;
				FinishTrimmingFirst();
			}

			{
				// 이건 필요한가?????
				FinishTrimming();
			}
		}
	}

protected:
	MoveableState MyMoveableState_;
};

