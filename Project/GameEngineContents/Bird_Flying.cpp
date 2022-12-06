#include "PreCompile.h"
#include "Bird_Flying.h"

Bird_Flying::Bird_Flying() 
	: MoveDir_(0.f)
	, IsPause_(true)
	, Time_(0.f)
	, RandomTime_(0)
{
}

Bird_Flying::~Bird_Flying() 
{
}

void Bird_Flying::Start()
{
	GamePlayMapObject::Start();
	GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 130.f, 130.f, 130.f });
	GetAnimationFBXMesh()->SetFBXMesh("m_city_pigeon_01.fbx", "TextureAnimation", 0);	// Flying
	GetAnimationFBXMesh()->CreateFBXAnimation("Move", GameEngineRenderingEvent("m_city_pigeon_01.fbx", 0.04f, true));
	GetAnimationFBXMesh()->ChangeAnimation("Move");
	GetCollisionObject()->Off();

	MoveDir_ = { -700.f, 0.f, 300.f };
	RandomTime_ = GameEngineRandom::MainRandom.RandomInt(13, 22);
}

void Bird_Flying::Update(float _DeltaTime) 
{
	// ���� �ð� ���� �� ���� ��ġ�� �̵�
	if (Time_ > RandomTime_)
	{
		Time_ = 0.f;
		RandomTime_ = 0;
		IsPause_ = false;
		GetTransform().SetWorldPosition(StartPos_);
	}

	if (true == IsPause_)
	{
		Time_ += _DeltaTime;
	}
	else
	{
		// �� ������ ������ => ���� �ð� �Ǳ� ������ �����ֱ�
		if (GetTransform().GetWorldPosition().x < -5000.f)
		{
			RandomTime_ = GameEngineRandom::MainRandom.RandomInt(13, 22);
			IsPause_ = true;
		}
		else
		{
			GetTransform().SetWorldMove({ MoveDir_ * _DeltaTime });
		}
	}
}

