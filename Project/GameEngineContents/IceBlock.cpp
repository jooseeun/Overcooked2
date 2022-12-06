#include "PreCompile.h"
#include "IceBlock.h"

IceBlock::IceBlock() 
{
}

IceBlock::~IceBlock() 
{
}

void IceBlock::SetIceBlockMesh(IceBlockType _Type)
{
	std::string Name = "";

	switch (_Type)
	{
	case IceBlockType::Ice01:
		Name = "p_dlc09_iceblock_02 (1)1.fbx";
		break;
	case IceBlockType::Ice02:
		Name = "p_dlc09_iceblock_02 (2)1.fbx";
		break;
	case IceBlockType::Ice03:
		Name = "p_dlc09_iceblock_02 (3)1.fbx";
		break;
	case IceBlockType::Ice04:
		Name = "p_dlc09_iceblock_02 (4)1.fbx";
		break;
	case IceBlockType::Ice06:
		Name = "p_dlc09_iceblock_02 (6)1.fbx";
		break;
	case IceBlockType::Ice08:
		Name = "p_dlc09_iceblock_02 (8)1.fbx";
		break;
	case IceBlockType::Ice10:
		Name = "p_dlc09_iceblock_02 (10)1.fbx";
		break;
	case IceBlockType::Ice11:
		Name = "p_dlc09_iceblock_02 (11)1.fbx";
		break;
	default:
		break;
	}

	GetFBXMesh()->SetFBXMesh(Name, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void IceBlock::Start()
{
	GamePlayMapObject::Start();
}

void IceBlock::Update(float _DeltaTime)
{
}

