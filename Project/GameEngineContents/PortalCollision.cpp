#include "PreCompile.h"
#include "PortalCollision.h"
#include "Player.h"

PortalCollision::PortalCollision()
	:PotalType_()
	, PotalCol_(nullptr)
	, NextPotal_(nullptr)
	, IsBig_(false)
	, IsSmall_(false)
{

}

PortalCollision::~PortalCollision() 
{
}

void PortalCollision::Start()
{
	PotalCol_ = CreateComponent<GameEngineCollision>();
	PotalCol_->GetTransform().SetLocalScale({ 100,100,100 });
	PotalCol_->ChangeOrder(CollisionOrder::Map_Potal);
	PotalCol_->SetDebugSetting(CollisionType::CT_AABB, { 0,0,0 });
}
void PortalCollision::Update(float _DeltaTime)
{
	PotalCol_->IsCollision(CollisionType::CT_SPHERE, CollisionOrder::Object_Character, CollisionType::CT_SPHERE,
		std::bind(&PortalCollision::ColCheckActor, this, std::placeholders::_1, std::placeholders::_2));
	//PotalCol_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
	//	std::bind(&PortalCollision::SmallActor, this, std::placeholders::_1, std::placeholders::_2));

	if (IsBig_ == true)
	{
		BigActor();
	}
	if (IsSmall_ == true)
	{
		SmallActor();
	}


}
void PortalCollision::SmallActor()
{
	if (InterActor_ == nullptr)
	{
		IsSmall_ = false;
		return;
	}
	else
	{
		if (InterActor_->GetTransform().GetWorldScale().x >= 0.0f)
		{
			InterActor_->GetTransform().SetWorldScale(InterActor_->GetTransform().GetWorldScale() - float4{ 1.0f,1.0f ,1.0f } *GameEngineTime::GetDeltaTime());
			return;
		}
		else
		{

			InterActor_->GetTransform().SetWorldPosition(NextPos_ + float4{ 0,0,120.0f });
			InterActor_->GetTransform().SetLocalRotation({ 0,180.0f, 0 });;
			NextPotal_->IsBig_ = true;
			NextPotal_->SetActor(InterActor_);
			InterActor_ = nullptr;
			IsSmall_ = false;
		}
	}

}
void PortalCollision::BigActor()
{
	if (InterActor_ == nullptr)
	{
		IsBig_ = false;
		return;
	}
	else
	{
		if (InterActor_->GetTransform().GetWorldScale().x >= 1.0f)
		{
			InterActor_->GetTransform().SetWorldScale({ 1.0,1.0,1.0 });
			InterActor_->CastThis<Player>()->IsPotal_ = false;
			InterActor_->CastThis<Player>()->SetCurFrontDir();
			InterActor_=nullptr;
			IsBig_ = false;
			return;
		}
		InterActor_->GetTransform().SetWorldScale(InterActor_->GetTransform().GetWorldScale() + float4{ 1.0f,1.0f ,1.0f } *GameEngineTime::GetDeltaTime());
	}
}

CollisionReturn PortalCollision::ColCheckActor(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (_Other->GetParent()->CastThis<GameEngineActor>()->GetTransform().GetWorldScale().x > 0.0f)
	{
		SetActor(_Other->GetParent()->CastThis<GameEngineActor>());
		IsSmall_ = true;


		_Other->GetParent()->CastThis<Player>()->IsPotal_ = true;
	}		

	return CollisionReturn::ContinueCheck;
}

