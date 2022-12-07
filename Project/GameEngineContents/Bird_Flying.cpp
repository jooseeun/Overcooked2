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
	// 일정 시간 지난 후 시작 위치로 이동
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
		// 맵 밖으로 나갔다 => 일정 시간 되기 전까지 멈춰있기
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

