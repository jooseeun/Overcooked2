#pragma once
#include "GamePlayObject.h"
#include "Enums.h"
#include "GamePlayStuff.h"
#include "Player.h"

// ���� :
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
	SetPlayerState_Return SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable = nullptr) override;
	


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
		if (InteractPacket_ != nullptr)
		{
			InteractPacket_->HoldObjectID = -1;
		}
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
	void Update(float _DeltaTime) override {};
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

	void SendPacket(std::shared_ptr<ObjectUpdatePacket> Packet) override
	{
		if (Stuff_Current_ != nullptr)
		{
			Packet->HoldObjectID = Stuff_Current_->GetNetID();
		}
		else
		{
			Packet->HoldObjectID = -1;
		}
	}

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
				Stuff_Current_ = Object->shared_from_this()->CastThis<GamePlayStuff>();
			}
		}
		else
		{
			MsgBoxAssert("GamePlayStaticObject_ServerHoldObject_Error")
		}
	}
};


