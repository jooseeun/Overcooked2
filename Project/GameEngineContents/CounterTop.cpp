#include "PreCompile.h"
#include "CounterTop.h"

CounterTop::CounterTop()
	: MyType_(CounterTopType::Normal)
{
}

CounterTop::~CounterTop()
{
}

void CounterTop::Start()
{
	GamePlayStaticObject::Start();


	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });


}

void CounterTop::SetConterTopMesh(CounterTopType _Type)
{
	std::string Name = "";

	switch (_Type)
	{
	case CounterTopType::Normal:
		Name = "m_sk_countertop_01.fbx";
		break;
	case CounterTopType::Corner:
		Name = "m_lorry_countertop_corner_01.fbx";
		break;
	case CounterTopType::NoEdge:
		Name = "m_sk_countertop_no_edge_01.fbx";
		break;
	case CounterTopType::Wizard:
		Name = "m_wizard_countertop_05.fbx";
		break;	
	case CounterTopType::Winter:
		Name = "m_wizard_countertop.fbx";
		break;
	default:
		break;
	}

	GetFBXMesh()->SetFBXMesh(Name, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	std::vector<std::vector<GameEngineRenderUnit>>& Unit = GetFBXMesh()->GetAllRenderUnit();

}