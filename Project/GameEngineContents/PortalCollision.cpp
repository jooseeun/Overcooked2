#include "PreCompile.h"
#include "PortalCollision.h"

PortalCollision::PortalCollision()
	:PotalType_()
	, PotalCol_(nullptr)
	, NextPotal_(nullptr)
	, IsBig_(false)
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
	PotalCol_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
		std::bind(&PortalCollision::SmallActor, this, std::placeholders::_1, std::placeholders::_2));
	PotalCol_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Moveable, CollisionType::CT_OBB,
		std::bind(&PortalCollision::SmallActor, this, std::placeholders::_1, std::placeholders::_2));

	if (IsBig_ == true)
	{
		BigActor();
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
			InterActor_=nullptr;
			IsBig_ = false;
			return;
		}
		InterActor_->GetTransform().SetWorldScale(InterActor_->GetTransform().GetWorldScale() + float4{ 0.5,0.5,0.5 } *GameEngineTime::GetDeltaTime());
	}
}

CollisionReturn PortalCollision::SmallActor(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (_Other->GetParent()->CastThis<GameEngineActor>()->GetTransform().GetWorldScale().x > 0.0f)
	{
		_Other->GetParent()->CastThis<GameEngineActor>()->GetTransform().SetWorldScale(_Other->GetParent()->CastThis<GameEngineActor>()->GetTransform().GetWorldScale() 
			- float4{ 0.5,0.5,0.5 } * GameEngineTime::GetDeltaTime());
	}		
	else
	{
		if (InterActor_  == nullptr||_Other->GetParent()->CastThis<GameEngineActor>() != InterActor_)
		{
			_Other->GetParent()->CastThis<GameEngineActor>()->GetTransform().SetWorldPosition(NextPos_ + float4{0,0,110.0f});
			_Other->GetParent()->CastThis<GameEngineActor>()->GetTransform().SetLocalRotation({ 0,180.0f, 0 });;
			NextPotal_->IsBig_ = true;
			NextPotal_->SetActor(_Other->GetParent()->CastThis<GameEngineActor>());
		}

	}

	return CollisionReturn::ContinueCheck;
}

