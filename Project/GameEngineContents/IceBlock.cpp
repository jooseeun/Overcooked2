#include "PreCompile.h"
#include "IceBlock.h"

IceBlock::IceBlock()
	: MoveDir_({ 0.f, 0.f, 70.f })
	, RandomX_(0.f)
	, RandomY_(0.f)
	, IsMovable_(true)
	, Angle_(0.f)
	, MaxAngle_(50.f)
	, IsDirChange_(false)
	, AngleDir_(20.f)
	, IsLeft_(false)
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
	
	RandomX_ = GameEngineRandom::MainRandom.RandomFloat(-1740.f, -1720.f);
	RandomY_ = GameEngineRandom::MainRandom.RandomFloat(-10.f, 40.f);
}

void IceBlock::Update(float _DeltaTime)
{
	//Move(_DeltaTime);
	RotateIce(_DeltaTime);
}

void IceBlock::Move(float _DeltaTime)
{
	if (false == IsMovable_)
	{
		return;
	}

	if (GetTransform().GetWorldPosition().z > 824.f)
	{
		GetTransform().SetWorldPosition({ RandomX_, RandomY_, -2665.f });
	}
	else
	{
		GetTransform().SetWorldMove({ MoveDir_ * _DeltaTime });
	}
}

void IceBlock::RotateIce(float _DeltaTime)
{
	//// 최대 각도에 이르기 전
	//if (MaxAngle_ >= Angle_ && false == IsDirChange_)
	//{
	//	IsDirChange_ = true;
	//}

	//// 최대 각도
	//if (true == IsDirChange_)
	//{
	//	AngleDir_ *= -1;
	//	MaxAngle_ *= -1;
	//	IsDirChange_ = false;
	//}

	//Angle_ += AngleDir_ * _DeltaTime;
	//GetTransform().SetAddWorldRotation(float4{ Angle_, 0.f, 0.f } *_DeltaTime);

}
