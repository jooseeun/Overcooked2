#include "PreCompile.h"
#include "Cooker.h"
#include "GamePlayBowl.h"

Cooker::Cooker() 
{
}

Cooker::~Cooker() 
{
}

void Cooker::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 130, 50, 130 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_sk_cooker_01.fbx", "Texture");
	GetFBXMesh()->GetPixelDatas(1).AlphaFlag = true;
	GetFBXMesh()->SetSubMaterial(1, "AddBlendAlpha");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });
	ToolPos_ = {0.f, 85.f, 25.f};
	SetToolPos(ToolPos_);

	SetStuff(GetLevel()->CreateActor<Tool_Cooker>());
}


// ----------------------Tool---------------------------

Tool_Cooker::Tool_Cooker()
{
}

Tool_Cooker::~Tool_Cooker()
{
}


void Tool_Cooker::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Auto);
	//SetCookingEndTime(12.f);
	GamePlayTool::SetObjectToolType(ObjectToolType::Cooker);
}

void Tool_Cooker::Update(float _DeltaTime)
{
	if (GetCurrentMoveable() != nullptr)
	{
		if (GetCurrentMoveable()->AutoTrim(_DeltaTime, GetObjectToolType()))
		{
			//불 붙히는 애니메이션
		}
	}
}

//HoldDownEnum Tool_Cooker::HoldDown(std::shared_ptr<GamePlayStuff> _Stuff)
//{
//	//if (std::dynamic_pointer_cast<>)
//	//{
//
//	//}
//}