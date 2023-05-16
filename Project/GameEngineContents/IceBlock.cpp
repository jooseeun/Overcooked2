#include "PreCompile.h"
#include "IceBlock.h"

namespace
{
	constexpr float START_ZPOS = -2755.f;
	constexpr float END_ZPOS = 824.f;
}


IceBlock::IceBlock()
	: MoveDir_({ 0.f, 0.f, 85.f })
	, IsMovable_(true)
	, RandomMaxAngle_(0.f)
	, MoveAngle_(0.f)
	, IsMaxAngle(false)
	, RandomPos_(0.f)
	, RandomSpeed_(0.f)
	, MoveAngleTypeIce11_(70.f)
	, InitRandomPosX_(-1740.f)
	, InitRandomPosY_(-30.f)
	, InitRandSpeed_(10.f)
	, InitRandomMaxAngle_(25.f)
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
		GetFBXMesh()->GetTransform().SetWorldRotation({ 90, 0, 0 });
	/*	SoundPlayer_ = GameEngineSound::SoundPlayControl("AMB_Ice_Lake.wav", -1);
		SoundPlayer_.Volume(0.2f); */
		GameSoundPlayer::EffectPlayer_->ChangeEffect("AMB_Ice_Lake.wav");
		GameSoundPlayer::EffectPlayer_->SetEffectVolume(0.5f);
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
	
	RandomPos_.x = GameEngineRandom::MainRandom.RandomFloat(InitRandomPosX_, InitRandomPosX_ + 20.f);
	RandomPos_.y = GameEngineRandom::MainRandom.RandomFloat(InitRandomPosY_, InitRandomPosY_ + 30.f);
	RandomSpeed_.x = GameEngineRandom::MainRandom.RandomFloat(InitRandSpeed_, InitRandSpeed_ + 5.f);
	RandomSpeed_.y = GameEngineRandom::MainRandom.RandomFloat(InitRandSpeed_, InitRandSpeed_ + 5.f);
	RandomSpeed_.z = GameEngineRandom::MainRandom.RandomFloat(InitRandSpeed_, InitRandSpeed_ + 5.f);
	RandomMaxAngle_= GameEngineRandom::MainRandom.RandomFloat(InitRandomMaxAngle_, InitRandomMaxAngle_ + 15.f);

}

void IceBlock::Update(float _DeltaTime)
{
	
	Move(_DeltaTime);
	RotateIce(_DeltaTime);
}

void IceBlock::LevelEndEvent()
{
	SoundPlayer_.Stop();
}

void IceBlock::Move(float _DeltaTime)
{
	if (false == IsMovable_)
	{
		return;
	}

	if (GetTransform().GetWorldPosition().z > END_ZPOS)
	{
		GetTransform().SetWorldPosition({ RandomPos_.x, RandomPos_.y, START_ZPOS });
	}
	else
	{
		GetTransform().SetWorldMove({ MoveDir_ * _DeltaTime });
	}
}

void IceBlock::RotateIce(float _DeltaTime)
{
	if (IceBlockType_ == IceBlockType::Ice11)
	{
		if (false == IsMaxAngle)
		{
			MoveAngle_.y += _DeltaTime * RandomSpeed_.y;
			MoveAngle_.z += _DeltaTime * RandomSpeed_.z;
			MoveAngleTypeIce11_ += _DeltaTime * RandomSpeed_.x;

			GetFBXMesh()->GetTransform().SetWorldRotation({ MoveAngleTypeIce11_, MoveAngle_.y, MoveAngle_.z });

			if (RandomMaxAngle_ <= MoveAngle_.y)
			{
				IsMaxAngle = true;
			}
		}

		if (true == IsMaxAngle)
		{
			MoveAngle_.y -= _DeltaTime * RandomSpeed_.y;
			MoveAngle_.z -= _DeltaTime * RandomSpeed_.z;
			MoveAngleTypeIce11_ -= _DeltaTime * RandomSpeed_.x;

			GetFBXMesh()->GetTransform().SetWorldRotation({ MoveAngleTypeIce11_, MoveAngle_.y, MoveAngle_.z });

			if (0.f >= MoveAngle_.y)
			{
				MoveAngle_ = 0.f;
				IsMaxAngle = false;
			}
		}
	}
	else
	{
		if (false == IsMaxAngle)
		{
			MoveAngle_.x += _DeltaTime * RandomSpeed_.x;
			MoveAngle_.y += _DeltaTime * RandomSpeed_.y;
			MoveAngle_.z += _DeltaTime * RandomSpeed_.z;

			GetFBXMesh()->GetTransform().SetWorldRotation({ MoveAngle_.x, 0.f, MoveAngle_.y });

			if (RandomMaxAngle_ <= MoveAngle_.x)
			{
				IsMaxAngle = true;
			}
		}

		if (true == IsMaxAngle)
		{
			MoveAngle_.x -= _DeltaTime * RandomSpeed_.x;
			MoveAngle_.y -= _DeltaTime * RandomSpeed_.y;
			MoveAngle_.z -= _DeltaTime * RandomSpeed_.z;

			GetFBXMesh()->GetTransform().SetWorldRotation({ MoveAngle_.x, 0.f, MoveAngle_.y });

			if (0.f >= MoveAngle_.x)
			{
				MoveAngle_ = 0.f;
				IsMaxAngle = false;
			}
		}
	}
}
