#include "PreCompile.h"
#include "GamePlayPhysics.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCollision.h>

GamePlayPhysics::GamePlayPhysics() 
	:PhysicsCollision_(nullptr)
	, UpTime_(1.0f)
	, IsThrow_(false)
	, ThrowTime_(2.0f)
	, CurKineticEnergy_(0.0f)
	, CurSpeed_(0.0f)
	, CurMass_(0.0f)
	, PhysicsGravityCollision_(nullptr)
{
}

GamePlayPhysics::~GamePlayPhysics() 
{
}

void GamePlayPhysics::Gravity()// �߷��Լ� -> Update ���ָ� ��
{
	if (PhysicsGravityCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Floor, CollisionType::CT_OBB) == false)
	{
		GetTransform().SetWorldDownMove(300.0f, GameEngineTime::GetDeltaTime());
	}
}

void GamePlayPhysics::ColCheckPlayer()//�÷��̾����� ���̰ų� �ϸ��� �и��� �Լ� �ӽû����Ѱ�
{
	PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_Character, CollisionType::CT_OBB,
		std::bind(&GamePlayPhysics::MoveFromPlayer, this, std::placeholders::_1, std::placeholders::_2));
		
}

CollisionReturn GamePlayPhysics::MoveFromPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{ // ���� �и��°�
	if (_This != _Other)
	{
		if (PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == false &&
			PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == false)
		{
			float4  Vec = _This->GetActor()->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
			Vec.Normalize3D();
			Vec.y = 0;
			GetTransform().SetWorldMove(Vec*500.0f * GameEngineTime::GetDeltaTime());
		}
	}


	return CollisionReturn::ContinueCheck;
} 

CollisionReturn GamePlayPhysics::PullPlayer(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{ // ���� �ٸ��ָ� �̴°�
	float4  Vec = _Other->GetActor()->GetTransform().GetWorldPosition() - _This->GetActor()->GetTransform().GetWorldPosition();
	Vec.Normalize3D();
	Vec.y = 0;
	float len = Vec.Length();

		if (PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PhysicsLeftCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_Other->GetActor()->GetTransform().SetWorldLeftMove(100.0f, GameEngineTime::GetDeltaTime());
		}
		else if(PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true ||
			PhysicsRightCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
		{
			_Other->GetActor()->GetTransform().SetWorldRightMove(100.0f, GameEngineTime::GetDeltaTime());
		}
	
	return CollisionReturn::ContinueCheck;
}

void GamePlayPhysics::Throw(float4 _Vector) 
{
	if (IsThrow_ == false)
	{
		IsThrow_ = true;
		UpTime_ = 1.0f;
		ThrowTime_ = 2.0f;
	}
	else
	{
		ThrowTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
		if (ThrowTime_ < 0.0f)
		{
			IsThrow_ = false;
		}

		if (UpTime_ > 0.0f)
		{
			UpTime_ -= 1.0f * GameEngineTime::GetDeltaTime();
			GetTransform().SetWorldUpMove(500.0f, GameEngineTime::GetDeltaTime());
		}
		
		GetTransform().SetWorldMove(_Vector * GameEngineTime::GetDeltaTime() * 1000.0f);
	}
	
}

bool GamePlayPhysics::StaticObjectCollisionCheck() // ��, �� ������Ʈ�� �浹�ϸ� true ��ȯ, �浹���ϸ� false ��ȯ
{
	if (PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Map_Object, CollisionType::CT_OBB) == true||
		PhysicsCollision_->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB) == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void GamePlayPhysics::CalculateKineticEnergy() //������� ��� �Լ� -> �ʿ��ϸ� Update���� �����ָ� �ȴ�
{ // �ϴ� ������ WorldScale�� ����ߴµ� Ư���� ��찡 �ʿ��ϸ� CurMass�� �����������ָ� �ȴ�.
	CurKineticEnergy_ = 0.5 * CurSpeed_ * (pow((double)GetTransform().GetWorldScale().x, 2) +
		pow((double)GetTransform().GetWorldScale().y, 2) + pow((double)GetTransform().GetWorldScale().z, 2));
}


void GamePlayPhysics::CalculateKineticEnergyMass() //������� ��� �Լ� ������ ���� �ξ��ٸ� �� �Լ� ����ϸ� �ȴ�.
{
	CurKineticEnergy_ = 0.5 * CurSpeed_ * pow(CurMass_,2);
}