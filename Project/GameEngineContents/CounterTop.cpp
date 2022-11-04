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


	GetCollisionObject()->GetTransform().SetWorldScale({100, 50, 100});
	GetCollisionObject()->GetTransform().SetWorldMove({0, 25, 0});

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
	default:
		break;
	}

	GetFBXMesh()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
		
}