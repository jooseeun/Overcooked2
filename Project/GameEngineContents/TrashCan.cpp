#include "PreCompile.h"
#include "TrashCan.h"
#include "GamePlayBowl.h"

TrashCan::TrashCan() 
{
}

TrashCan::~TrashCan() 
{
}

void TrashCan::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 50, 100 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_sk_bin_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetStuff(GetLevel()->CreateActor<Tool_TrashCan>());
}

// ----------------------Tool---------------------------

Tool_TrashCan::Tool_TrashCan()
	: Delay_(1.f)
{
}

Tool_TrashCan::~Tool_TrashCan()
{
}

void Tool_TrashCan::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::TrashCan);
}

void Tool_TrashCan::Update(float _Delta)
{
	if (GetCurrentMoveable() != nullptr)
	{
		TrashFood_ = GetCurrentMoveable()->CastThis<GamePlayFood>();
		TrashFood_->GetFoodThumbnail()->Off();
	}

	if (TrashFood_ != nullptr)
	{
		
		Delay_ -= _Delta;
		TrashFood_->GetTransform().SetLocalScale({ Delay_ , Delay_ , Delay_ });
		TrashFood_->GetTransform().SetLocalRotate({0, _Delta * 180.f, 0});
		if (Delay_ < 0)
		{
			TrashFood_.reset();
			GetCurrentMoveable()->GetTransform().SetWorldPosition(float4::ZERO);
			if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
			{
				GetCurrentMoveable()->Death();
			}
			GetCurrentMoveable()->Off();
			ReSetCurrentMoveable();
			Delay_ = 1.f;
		}
	}
}

HoldDownEnum Tool_TrashCan::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if (GetCurrentMoveable() == nullptr && (*_Moveable) != nullptr)
	{
		if ((*_Moveable) != nullptr &&
			(*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
		{
			SetMoveable((*_Moveable));
			(*_Moveable) = nullptr;
			Delay_ = 1.f;
			return HoldDownEnum::HoldUp;
		}
		else if((*_Moveable)->CastThis<GamePlayBowl>() != nullptr)
		{
			//
			(*_Moveable)->CastThis<GamePlayBowl>()->GetCombinFood()->Clear();
		}
	}
	return HoldDownEnum::Nothing;
}


//void Tool_TrashCan::Input_ActionToAuto_Update(std::shared_ptr<GamePlayMoveable> _Moveable, float _DeltaTime)
//{
//	_Moveable->PlusCookingTime(_DeltaTime);
//	// 돌면서 작아지는 기능
//}
//
//void Tool_TrashCan::Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable)
//{
//	_Moveable->Death();// 삭제한다
//	ReSetCurrentMoveable();
//}



//
//Input_AutoOption Tool_TrashCan::Input_Action()
//{
//	return Input_AutoOption::NoResponse;
//}