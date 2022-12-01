#include "PreCompile.h"
#include "Equipment_FireExtinguisher.h"

Equipment_FireExtinguisher::Equipment_FireExtinguisher() 
{
}

Equipment_FireExtinguisher::~Equipment_FireExtinguisher() 
{
}

void Equipment_FireExtinguisher::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetToolInfoType(ToolInfo::FireExtinguisher);

	GetFBXMesh()->SetFBXMesh("m_sk_fire_extinguisher_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

//HoldDownEnum Equipment_FireExtinguisher::HoldDown(std::shared_ptr<Player> _Player)
//{
//	if (_Player->GetPlayerHolding() == nullptr)
//	{
//		_Player->SetPlayerHolding(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
//		_Player->SetCurHoldType(PlayerHoldType::FireExtinguisher);
//		return HoldDownEnum::HoldUp_Already;
//	}
//	else
//	{
//		return HoldDownEnum::Nothing;
//	}
//}