#include "PreCompile.h"
#include "Sink.h"
#include "Equipment_Plate.h"

Tool_Sink* Tool_Sink::Inst_ = nullptr;
Sink::Sink()
	: Collision_Sink_(nullptr)
{
}

Sink::~Sink()
{
}

void Sink::SetSinkMesh(SinkType _Type)
{
	switch (_Type)
	{
	case SinkType::Normal:
		GetFBXMesh()->SetFBXMesh("m_sk_sink_01.fbx", "Texture");
		GetFBXMesh()->GetTransform().SetWorldMove({ -60, 0, 0 });
		break;
	case SinkType::Wizard:
		GetFBXMesh()->SetFBXMesh("m_wizard_sink_01.fbx", "Texture");
		GetFBXMesh()->GetTransform().SetWorldMove({ -60, 70, 0 });
		break;
	default:
		break;
	}

	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

}

void Sink::Start()
{
	GamePlayStaticObject::Start();


	GetCollisionObject()->GetTransform().SetWorldScale({ 230, 50, 150 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, -10 });

	Collision_Sink_ = CreateComponent<GameEngineCollision>();
	Collision_Sink_->GetTransform().SetWorldScale(GetCollisionObject()->GetTransform().GetWorldScale() * 0.5f);
	Collision_Sink_->ChangeOrder(CollisionOrder::Object_Sink);

	SetStuff(GetLevel()->CreateActor<Tool_Sink>());
}



// ----------------------Tool---------------------------
Tool_Sink::Tool_Sink()


{
}

Tool_Sink::~Tool_Sink()
{
	if (Tool_Sink::Inst_ == this)
	{
		Tool_Sink::Inst_ = nullptr;
	}
}

void Tool_Sink::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	GamePlayTool::SetObjectToolType(ObjectToolType::Sink);



	Tool_Sink::Inst_ = this;
	SetMoveablePos({-120, 0, 0});
}

HoldDownEnum Tool_Sink::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		std::shared_ptr<Equipment_Plate> Plate = (*_Moveable)->CastThis<Equipment_Plate>();
		if (Plate != nullptr
			&& Plate->IsDirty())
		{
			Plate->ChangeFBXMesh();
			Plate->GetFBXMesh()->SetFBXMesh("m_sk_plate_dirty_Sink.fbx", "Texture");
			Plate->GetFBXMesh()->GetTransform().SetWorldScale({ 80, 80, 80 });
			switch (Dirty_Plate_.size())
			{
			case 0:
			{
				Plate->SetParent(shared_from_this());
				Plate->GetTransform().SetLocalPosition({ -75, -20, 5 });
				Plate->GetTransform().SetLocalRotation({ 0, 200, 0 });
				Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Plate);
			}
			break;
			case 1:
			{
				Plate->SetParent(shared_from_this());
				Plate->GetTransform().SetLocalPosition({ -75, -28, 20 });
				Plate->GetTransform().SetLocalRotation({ 0, 200, 0 });
				Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Plate);
			}
			break;
			//case 2:
			//{
			//	Plate->SetParent(shared_from_this());
			//	Plate->GetTransform().SetLocalPosition({ 150, 20, 80 });
			//	Plate->GetCollisionObject()->Off();
			//	Dirty_Plate_.push_back(Plate);
			//}
			//break;
			default:
			{
				Plate->GetFBXMesh()->Off();
				Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Plate);
			}
			break;
			}

			(*_Moveable) = nullptr;
			return HoldDownEnum::HoldUp;
		}
	}
	else
	{
		if (GetCurrentMoveable() != nullptr)
		{
			(*_Moveable) = GetCurrentMoveable();
			ReSetCurrentMoveable();
			return HoldDownEnum::HoldDown;
		}
	}
	return HoldDownEnum::Nothing;
}

UsingDownEnum Tool_Sink::UsingDown(std::shared_ptr<Player> _Player)
{
	if (!Dirty_Plate_.empty())
	{
		if (Dirty_Plate_.back()->Input_Manual(_Player, GameEngineTime::GetDeltaTime(), 5.f)) // ¿ø·¡ 12ÃÊ
		{
			Dirty_Plate_.back()->SetClean();
			if (GetCurrentMoveable() != nullptr)
			{
				GetCurrentMoveable()->CastThis<Equipment_Plate>()->SetPlate(Dirty_Plate_.back());
			}
			else
			{
				SetMoveable(Dirty_Plate_.back());
			}
			Dirty_Plate_.pop_back();

			if (Dirty_Plate_.empty())
			{
				_Player->FinishSink();
			}
			return UsingDownEnum::Nothing;
		}
	}
	return UsingDownEnum::Using;
}


//Input_PutDownOption Tool_Sink::Input_PutDown(std::shared_ptr<GamePlayMoveable> _Object)
//{
//
//	//if (_Object->GetToolInfoType() == ToolInfo::Plate &&
//	//	std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
//	//{
//
//	//	if (GetCurrentMoveable() == nullptr)
//	//	{
//	//		SetCurrentMoveable(_Object);
//	//		return Input_PutDownOption::PickUp;
//	//	}
//	//	else
//	//	{
//	//		return std::dynamic_pointer_cast<Equipment_Plate>(GetCurrentMoveable())->Input_PickUp(_Object);
//	//	}
//	//}
//	//return Input_PutDownOption::NoResponse;
//
//}
