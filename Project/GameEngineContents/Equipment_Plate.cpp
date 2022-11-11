#include "PreCompile.h"
#include "Equipment_Plate.h"

Equipment_Plate::Equipment_Plate() 
	: Dirty(false)
	, StackValue_(1)
{
}

Equipment_Plate::~Equipment_Plate() 
{
}

void Equipment_Plate::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Plate);

}

void Equipment_Plate::SetDirty()
{
	Dirty = true;
	// �ؽ��� �����ʿ�
}

void Equipment_Plate::SetClean()
{
	Dirty = false;
	// �ؽ��� �����ʿ�
}

Input_PickUpOption Equipment_Plate::Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object)
{
	if (_Object->GetToolInfoType() == ToolInfo::Plate &&
		std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
	{
		
	}
	return Input_PickUpOption::NoResponse; // ������
}