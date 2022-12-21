#include "PreCompile.h"
#include "Equipment_Steamer.h"
#include "Equipment_Bowl.h"

Equipment_Steamer::Equipment_Steamer() 
	: Angle_(0.f)
	, IsInteraction_(false)
	, SteamerState_(SteamerState::Idle)
	, OpenPos_(0, 30, -20)
	, CurPos_(0.f)
	, IsMoveDone_(false)
	, ToolPos_(0.f)
	, IsRotateDone_(false)
	, IsChangeRot_(false)
	, CookingAngle_(0.f)
{
}

Equipment_Steamer::~Equipment_Steamer() 
{
}

void Equipment_Steamer::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Steamer);

	Lid_ = GetLevel()->CreateActor<GameEngineActor>();
	Lid_->SetParent(shared_from_this());

	LidRenderer_ = Lid_->CreateComponent<GameEngineFBXStaticRenderer>();
	LidRenderer_->SetFBXMesh("Steamer3.fbx", "Texture", 0);
	LidRenderer_->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	LidRenderer_->GetTransform().SetLocalRotation({ -45, 0, 0 });
	LidRenderer_->GetTransform().SetLocalMove({ OpenPos_ });

	GetFBXMesh()->SetFBXMesh("Steamer3.FBX", "Texture", 1);
	GetFBXMesh()->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	GetCollisionObject()->GetTransform().SetLocalScale({ 100 , 100, 100 });

	ToolPos_ = { 0.f, 85.f, 25.f };

	StateManager.CreateStateMember("Idle"
		, std::bind(&Equipment_Steamer::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Open"
		, std::bind(&Equipment_Steamer::OpenUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::OpenStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Cooking"
		, std::bind(&Equipment_Steamer::CookingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::CookingStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Close"
		, std::bind(&Equipment_Steamer::CloseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Equipment_Steamer::CloseStart, this, std::placeholders::_1)
	); 

	StateManager.ChangeState("Idle");

	GetCombinFood()->Start(2, shared_from_this());
}

void Equipment_Steamer::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst()->IsDownKey("SteamerTest"))
	{
		IsInteraction_ = true;
	}
}

void Equipment_Steamer::IdleStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Idle);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
	Angle_ = -45.f;
	CurPos_ = OpenPos_;
}

void Equipment_Steamer::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsInteraction_)
	{
		StateManager.ChangeState("Close");
	}
}

void Equipment_Steamer::OpenStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Open);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
}

void Equipment_Steamer::OpenUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsRotateDone_ && true == IsMoveDone_)
	{
		StateManager.ChangeState("Idle");
	}
	if (-45.f >= Angle_)
	{
		Angle_ = -45.f;
		IsRotateDone_ = true;
	}

	if (CurPos_.y >= OpenPos_.y && CurPos_.z <= OpenPos_.z)
	{
		IsMoveDone_ = true;
	}

	if (CurPos_.y >= OpenPos_.y)
	{
		CurPos_.y = OpenPos_.y;
	}
	if (CurPos_.z <= OpenPos_.z)
	{
		CurPos_.z = OpenPos_.z;
	}

	Angle_ -= _DeltaTime * 150.f;
	CurPos_.y += _DeltaTime * 110.f;
	CurPos_.z -= _DeltaTime * 130.f;

	if (false == IsRotateDone_)
	{
		LidRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
	}
	if (false == IsMoveDone_)
	{
		LidRenderer_->GetTransform().SetLocalPosition({ CurPos_ });
	}
}

void Equipment_Steamer::CookingStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Cooking);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
}

void Equipment_Steamer::CookingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsInteraction_)
	{
		StateManager.ChangeState("Open");
	}


	if (false == IsChangeRot_)
	{
		if (3.f >= CookingAngle_.y)
		{
			CookingAngle_ = 3.f;
			IsChangeRot_ = true;
			RandomAngle_.x = GameEngineRandom::MainRandom.RandomFloat(60.f, 100.f);
			RandomAngle_.y = GameEngineRandom::MainRandom.RandomFloat(40.f, 150.f);
		}

		CookingAngle_.x -= _DeltaTime * RandomAngle_.x;
		CookingAngle_.y -= _DeltaTime * RandomAngle_.y;
		LidRenderer_->GetTransform().SetLocalRotation({ CookingAngle_.x, CookingAngle_.y, 0.f });
	}
	if (true == IsChangeRot_)
	{
		if (10.f <= CookingAngle_.y)
		{
			IsChangeRot_ = false;
			RandomAngle_.x = GameEngineRandom::MainRandom.RandomFloat(60.f, 100.f);
			RandomAngle_.y = GameEngineRandom::MainRandom.RandomFloat(40.f, 150.f);
		}

		CookingAngle_.x += _DeltaTime * RandomAngle_.x;
		CookingAngle_.y += _DeltaTime * RandomAngle_.y;
		LidRenderer_->GetTransform().SetLocalRotation({ CookingAngle_.x, CookingAngle_.y, 0.f });
	}
}

void Equipment_Steamer::CloseStart(const StateInfo& _Info)
{
	SetSteamerState(SteamerState::Close);
	IsInteraction_ = false;
	IsMoveDone_ = false;
	IsRotateDone_ = false;
}

void Equipment_Steamer::CloseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsRotateDone_ && true == IsMoveDone_)
	{
		StateManager.ChangeState("Cooking");
	}
	if (0.f <= Angle_)
	{
		IsRotateDone_ = true;
		Angle_ = 0.f;
	}
	if (CurPos_.y <= 0.f && CurPos_.z >= 0.f)
	{
		IsMoveDone_ = true;
	}

	if (CurPos_.y <= 0.f)
	{
		CurPos_.y = 0.f;
	}
	if (CurPos_.z >= 0.f)
	{
		CurPos_.z = 0.f;
	}
	Angle_ += _DeltaTime * 140.f;
	CurPos_.y -= _DeltaTime * 110.f;
	CurPos_.z += _DeltaTime * 130.f;

	if (false == IsRotateDone_)
	{
		LidRenderer_->GetTransform().SetLocalRotation({ Angle_, 0.f, 0.f });
	}
	if (false == IsMoveDone_)
	{
		LidRenderer_->GetTransform().SetLocalPosition({ CurPos_ });
	}
}

bool Equipment_Steamer::AutoTrim(float _DeltaTime, ObjectToolType _Tool)
{
	if (_Tool == ObjectToolType::Cooker)
	{
		if (!GetCombinFood()->IsClear())
		{
			if (Input_Auto(_DeltaTime, 12.f))
			{
				return true;
			}
		}
	}
	return false;

}

HoldDownEnum Equipment_Steamer::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		return HoldDownEnum::HoldDown;
	}
	else
	{
		std::shared_ptr<GamePlayBowl> Bowl = (*_Moveable)->CastThis<GamePlayBowl>();
		if (GetCombinFood()->IsClear())
		{
			if (Bowl != nullptr)
			{
				if (Bowl->GetObjectBowlType() == ObjectBowlType::Bowl)
				{
					if (Bowl->GetCombinFood()->GetTrim() && Bowl->GetCombinFood()->GetFoodType() != FoodType::None)
					{
						BowltoSteamer((*_Moveable)->CastThis<Equipment_Bowl>());
					}
				}
				else if (Bowl->GetObjectBowlType() == ObjectBowlType::Steamer)
				{
					GetCombinFood()->Switching(Bowl->GetCombinFood());
					(*_Moveable)->SwitchingCookingGage((*_Moveable));
				}
			}
		}
		else
		{
			if (Bowl->GetObjectBowlType() == ObjectBowlType::Plate)
			{
				if (GetCombinFood()->GetTrim())
				{
					Bowl->GetCombinFood()->Move(GetCombinFood());
					Bowl->GetCombinFood()->RefreshThumbnailAndRenderer();
					ReSetCookingGage();
				}
			}
		}
	}
	return HoldDownEnum::Nothing;
}

bool Equipment_Steamer::BowltoSteamer(std::shared_ptr<Equipment_Bowl> _Bowl)
{
	if (GetCombinFood()->IsClear())
	{
		_Bowl->ReSetCookingGage();
		GetCombinFood()->Move(_Bowl->GetCombinFood());
		return true;
	}
	else
	{
		return false;
	}

}