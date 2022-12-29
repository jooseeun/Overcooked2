#pragma once
#include "GamePlayObject.h"
#include "Enums.h"
#include "GamePlayStuff.h"
#include "Player.h"

// 설명 :
class GamePlayStaticObject : public GamePlayObject
{
protected:
	GamePlayStaticObject();
public:
	// constrcuter destructer
	~GamePlayStaticObject();

	// delete Function
	GamePlayStaticObject(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject(GamePlayStaticObject&& _Other) noexcept = delete;
	GamePlayStaticObject& operator=(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject& operator=(GamePlayStaticObject&& _Other) noexcept = delete;

public:
	SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable = nullptr, bool _FromNet = false) override;
	


	inline std::shared_ptr<GamePlayStuff> GetStuff() const
	{
		return Stuff_Current_;
	}
	std::shared_ptr<GamePlayMoveable> GetMoveable() const;
	std::shared_ptr<GamePlayMoveable> GetMoveable_TakeOut();
	void SetMoveable(std::shared_ptr<GamePlayMoveable> _Moveable);

	inline void SetStuff(std::shared_ptr<Player> _Player)
	{
		SetStuff(_Player->GetPlayerHolding()->CastThis<GamePlayStuff>());
		_Player->DetachPlayerHolding();
	}
	void SetStuff(std::shared_ptr<GamePlayStuff> _Stuff);
	inline void ReSetStuff()
	{
		Stuff_Current_.reset();
		//if (InteractPacket_ != nullptr)
		//{
		//	InteractPacket_->HoldObjectID = -1;
		//}
	}


	inline void SetStaticObjectType(MapObjType _Type)
	{
		MyType_ = _Type;
	}

	inline MapObjType GetStaticObjectType()
	{
		return MyType_;
	}

	inline ToolInfo GetToolInfo() const
	{
		if (Stuff_Current_ == nullptr)
		{
			return ToolInfo::None;
		}
		else
		{
			return Stuff_Current_->GetToolInfoType();
		}
	}

	inline void SetToolPos(float4& _Pos)
	{
		ToolPos_ = _Pos;
	}

	virtual float4 GetToolPos() 
	{
		//ToolPos_ = GetTransform().GetWorldPosition() + float4{ 0, 50.f };

		return ToolPos_;
	}

	std::shared_ptr<GameEngineCollision> GetCrashCollision()
	{
		return CrashCollision_;
	}

protected:
	void Start() override;
	//void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

	float4 ToolPos_;

private:
	std::shared_ptr<GamePlayStuff> Stuff_Current_;
	std::shared_ptr<GameEngineCollision> CrashCollision_;

	MapObjType MyType_;



	// Bloom
public:
	void SetHighlightEffectOff() override;
	void SetHighlightEffectOn() override;


	//

private: 
	void ChildServerStart() override
	{
		if (Stuff_Current_ != nullptr)
		{
			Stuff_Current_->ServerStart();
		}
	};


	int GetChildNetID() override
	{ 
		if (Stuff_Current_ != nullptr)
		{
			return Stuff_Current_->GetNetID();
		}
		else
		{
			return -1;
		}
	};

	//void SendPacket(std::shared_ptr<ObjectUpdatePacket> Packet) override
	//{
	//	if (Stuff_Current_ != nullptr)
	//	{
	//		Packet->HoldObjectID = Stuff_Current_->GetNetID();
	//	}
	//	else
	//	{
	//		Packet->HoldObjectID = -1;
	//	}
	//}


	void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override
	{
		//switch (MyType_)
		//{
		//case MapObjType::CounterTop:
		//case MapObjType::CounterTop_Corner:
		//case MapObjType::CounterTop_NoEdge:
		//case MapObjType::CounterTop_WiZard:
		//case MapObjType::CounterTop_Winter:
		//case MapObjType::Mixer_Kevin:
		//case MapObjType::Mixer_Winter:
		//case MapObjType::Cooker:
		//case MapObjType::TrashCan:
		//case MapObjType::Sink:
		//case MapObjType::Sink_Wizard:
		//case MapObjType::Servicehatch:
		//case MapObjType::PlateReturn:
		//case MapObjType::FoodBox_Normal:
		//case MapObjType::FoodBox_Winter:
		//case MapObjType::Rail:
		//case MapObjType::Dispenser_Type1:
		//case MapObjType::Dispenser_Type2:
		//case MapObjType::Cannon:
		//case MapObjType::Button:
		//case MapObjType::Oven:
		//	break;
		//default:
		//	return;
		//	break;
		//}
		Packet->MapObjData = MyType_;
	}

	void SetParentsServerHoldObject(int _ServerID) override
	{ 
		if (Stuff_Current_ != nullptr)
		{
			if (!Stuff_Current_->GetIsNetInit())
			{
				Stuff_Current_->ClientInit(ServerObjectType::Object, _ServerID);
			}
			else
			{
				MsgBoxAssert("GamePlaystaticObject 서버 부모 설정 오류1")
			}

		}
		else
		{
			SetServerHoldObject(GetNetID());
		}
	};

	void SetServerHoldObject(int _ServerID) override
	{
		if (-1 == _ServerID)
		{
			ReSetStuff();
			return;
		}

		GamePlayStuff* Object = static_cast<GamePlayStuff*>(GameServerObject::GetServerObject(_ServerID));
		if (Object != nullptr)
		{
			if (Stuff_Current_.get() != Object)
			{
				SetStuff(Object->shared_from_this()->CastThis<GamePlayStuff>());
			}
		}
		else
		{
			MsgBoxAssert("GamePlayStaticObject_ServerHoldObject_Error")
		}
	}
};


