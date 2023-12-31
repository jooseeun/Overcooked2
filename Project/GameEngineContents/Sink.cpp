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
		if (Plate != nullptr && Plate->IsDirty())
		{
			std::shared_ptr<Equipment_Plate> Pile_Plate;
			while (Plate->Pile_Plate_ != nullptr)
			{
				Pile_Plate = Plate->GetPlate();

				Pile_Plate->ChangeFBXMesh();
				Pile_Plate->GetFBXMesh()->SetFBXMesh("m_sk_plate_dirty_Sink.fbx", "Texture");
				Pile_Plate->GetFBXMesh()->GetTransform().SetWorldScale({ 80, 80, 80 });
				switch (Dirty_Plate_.size())
				{
				case 0:
				{
					Pile_Plate->SetParent(shared_from_this());
					Pile_Plate->GetTransform().SetLocalPosition({ -75, -20, 5 });
					Pile_Plate->GetTransform().SetLocalRotation({ 0, 200, 0 });
					Pile_Plate->GetCollisionObject()->Off();
					Dirty_Plate_.push_back(Pile_Plate);
				}
				break;
				case 1:
				{
					Pile_Plate->SetParent(shared_from_this());
					Pile_Plate->GetTransform().SetLocalPosition({ -75, -28, 20 });
					Pile_Plate->GetTransform().SetLocalRotation({ 0, 200, 0 });
					Pile_Plate->GetCollisionObject()->Off();
					Dirty_Plate_.push_back(Pile_Plate);
				}
				break;
				case 2:
				{
					Pile_Plate->SetParent(shared_from_this());
					Pile_Plate->GetFBXMesh()->Off();
					Pile_Plate->GetCollisionObject()->Off();
					Dirty_Plate_.push_back(Pile_Plate);
				}
				break;
				default:
				{
					Pile_Plate->GetFBXMesh()->Off();
					Pile_Plate->GetCollisionObject()->Off();
					Dirty_Plate_.push_back(Pile_Plate);
				}
				break;
				}
			}


			Pile_Plate = Plate->GetPlate();

			Pile_Plate->ChangeFBXMesh();
			Pile_Plate->GetFBXMesh()->SetFBXMesh("m_sk_plate_dirty_Sink.fbx", "Texture");
			Pile_Plate->GetFBXMesh()->GetTransform().SetWorldScale({ 80, 80, 80 });
			switch (Dirty_Plate_.size())
			{
			case 0:
			{
				Pile_Plate->SetParent(shared_from_this());
				Pile_Plate->GetTransform().SetLocalPosition({ -75, -20, 5 });
				Pile_Plate->GetTransform().SetLocalRotation({ 0, 200, 0 });
				Pile_Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Pile_Plate);
			}
			break;
			case 1:
			{
				Pile_Plate->SetParent(shared_from_this());
				Pile_Plate->GetTransform().SetLocalPosition({ -75, -28, 20 });
				Pile_Plate->GetTransform().SetLocalRotation({ 0, 200, 0 });
				Pile_Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Pile_Plate);
			}
			break;
			case 2:
			{
				Pile_Plate->SetParent(shared_from_this());
				Pile_Plate->GetFBXMesh()->Off();
				Pile_Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Pile_Plate);
			}
			break;
			default:
			{
				Pile_Plate->GetFBXMesh()->Off();
				Pile_Plate->GetCollisionObject()->Off();
				Dirty_Plate_.push_back(Pile_Plate);
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
		if (Dirty_Plate_.back()->Input_Manual(_Player, GameEngineTime::GetDeltaTime(), 5.f)) // ���� 12��
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
			//GameEngineSound::SoundPlayOneShot("WashedPlate.wav");

			if (Dirty_Plate_.empty())
			{
				IsSound_ = false;
				ObjSoundPlayer_.Stop();
				_Player->FinishSink();
			}
			return UsingDownEnum::Nothing;
		}
		else
		{
			if (!ObjSoundPlayer_.IsPlaying())
			{
				ObjSoundPlayer_ = GameEngineSound::SoundPlayControl("Washing1.wav");
			}

			//if (false == IsSound_)
			//{
			//	SoundTime_ = 0.4f;
			//	IsSound_ = true;
			//}
			//else
			//{
			//	if (SoundTime_ >= 0.5f)
			//	{
			//		SoundTime_ = 0.f;
			//		ObjSoundPlayer_ = GameEngineSound::SoundPlayControl("Washing1.wav");
			//	}
			//	SoundTime_ += GameEngineTime::GetDeltaTime();
			//}

			return UsingDownEnum::Using;
		}
	}

	return UsingDownEnum::Nothing;
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
