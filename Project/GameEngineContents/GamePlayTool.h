#pragma once
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"

// 설명 :
enum class AutoOption
{
	NoResponse,
	Auto,
	Manual
};
enum class ObjectToolType
{
	  None
	, CuttingBoard // 도마
	, Cooker       // 가스레인지
	, TrashCan     // 쓰레기통
	, Mixer        // 믹서기
	, PlateReturn  // 접시반납
	, Sink         // 싱크대
	, FoodBox      // 
	, Servicehatch //
	, Rail		   //
	, Dispenser	   //
	, Oven
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
		if (Moveable_Current_->IsDeath())
		{
			Moveable_Current_->Off();
			Moveable_Current_->GetFBXMesh()->Off();
		}
		Moveable_Current_.reset();
	}

	inline ObjectToolType GetObjectToolType()
	{
		return Enum_ObjectToolType_;
	}
	inline float4 GetMoveablePos() const
	{
		return MoveablePos_;
	}
	inline void SetMoveablePos(const float4& _Pos)
	{
		MoveablePos_ = _Pos;
	}

	virtual void SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child);

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

	void SetMoveable(std::shared_ptr<Player> _Player);
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;

private:
	ObjectToolType Enum_ObjectToolType_;
	AutoOption InteractOption_Current_;

	float4 MoveablePos_;


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

	// server
	void ChildServerStart() override
	{
		if (Moveable_Current_ != nullptr)
		{
			Moveable_Current_->ServerStart();
		}
	};


	int GetChildNetID() override
	{
		if (Moveable_Current_ != nullptr)
		{
			return Moveable_Current_->GetNetID();
		}
		else
		{
			return -1;
		}
	};

	//void SendServerHoldObject(std::shared_ptr<ObjectStartPacket> Packet)  override
	//{
	//	if (Moveable_Current_ != nullptr)
	//	{
	//		Packet->HoldObjectID = Moveable_Current_->GetNetID();
	//	}
	//	else
	//	{
	//		Packet->HoldObjectID = -1;
	//	}
	//}


	void SetParentsServerHoldObject(int _ServerID) override
	{
		if (Moveable_Current_ != nullptr)
		{
			if (!GameServerObject::GetServerObject(Moveable_Current_->GetNetID()))
			{
				Moveable_Current_->ClientInit(ServerObjectType::Object, _ServerID);
			}
			else
			{
				MsgBoxAssert("GamePlayTool 서버 부모 설정 오류1")
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
			ReSetCurrentMoveable();
			return;
		}

		GamePlayMoveable* Object = static_cast<GamePlayMoveable*>(GameServerObject::GetServerObject(_ServerID));
		if (Object != nullptr)
		{
			if (Moveable_Current_.get() != Object)
			{
				SetMoveable(Object->shared_from_this()->CastThis<GamePlayMoveable>());
			}
		}
		else
		{
			MsgBoxAssert("GamePlayMoveableObject_ServerHoldObject_Error")
		}
	}

};

