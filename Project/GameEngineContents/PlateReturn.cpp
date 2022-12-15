#include "PreCompile.h"
#include "PlateReturn.h"
#include "Sink.h"

Tool_PlateReturn* Tool_PlateReturn::Inst_ = nullptr;

PlateReturn::PlateReturn() 
{
}

PlateReturn::~PlateReturn() 
{
}

void PlateReturn::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_sk_plate_return_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });

	SetStuff(GetLevel()->CreateActor<Tool_PlateReturn>());
}

Tool_PlateReturn::Tool_PlateReturn()
{
}

Tool_PlateReturn::~Tool_PlateReturn()
{
	if (Tool_PlateReturn::Inst_ == this)
	{
		Tool_PlateReturn::Inst_ = nullptr;
	}

}
void Tool_PlateReturn::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::PlateReturn);
	Tool_PlateReturn::Inst_ = this;

}
void Tool_PlateReturn::Update(float Delta)
{
	std::map<std::shared_ptr<Equipment_Plate>, float>::iterator StartIter = Map_PlateCollTime_.begin();
	std::map<std::shared_ptr<Equipment_Plate>, float>::iterator EndIter = Map_PlateCollTime_.end();

	for (; StartIter != EndIter;)
	{
		StartIter->second -= Delta;
		if (StartIter->second < 0)
		{
			if (Tool_Sink::GetInst() != nullptr)
			{
				StartIter->first->SetDirty();
			}
			else
			{
				StartIter->first->SetClean();
			}

			if (GetCurrentMoveable() == nullptr)
			{
				SetMoveable(StartIter->first);
				StartIter->first->On();
			}
			else
			{
				GetCurrentMoveable()->CastThis<Equipment_Plate>()->SetPlate(StartIter->first);
			}
			StartIter = Map_PlateCollTime_.erase(StartIter);
			continue;
		}
		StartIter++;
	}
}


HoldDownEnum Tool_PlateReturn::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		if (GetCurrentMoveable() == nullptr)
		{
			return HoldDownEnum::Nothing;
		}
		else
		{
			(*_Moveable) = GetCurrentMoveable();
			ReSetCurrentMoveable();
			return HoldDownEnum::HoldDown;
		}
	}
	return HoldDownEnum::Nothing;
}



void Tool_PlateReturn::LevelStartEvent()
{

}
void Tool_PlateReturn::LevelEndEvent()
{

}
