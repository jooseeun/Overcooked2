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
	: Delay_(0)
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
		Delay_ += _Delta;
		if (Delay_ > 1.f)
		{
			GetCurrentMoveable()->Death();
			GetCurrentMoveable()->Off();
			ReSetCurrentMoveable();
			Delay_ = 0;
		}
	}
}

HoldDownEnum Tool_TrashCan::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if (GetCurrentMoveable() == nullptr)
	{
		if ((*_Moveable) != nullptr &&
			(*_Moveable)->GetObjectMoveableType() == ObjectMoveableType::Food)
		{
			SetMoveable((*_Moveable));
			(*_Moveable) = nullptr;
			Delay_ = 0;
		}
		else if((*_Moveable)->CastThis<GamePlayBowl>() != nullptr)
		{
			//
			(*_Moveable)->CastThis<GamePlayBowl>()->GetCombinFood();
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