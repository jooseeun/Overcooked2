#include "PreCompile.h"
#include "Rail.h"

Rail::Rail() 
{
}

Rail::~Rail() 
{
}

void Rail::Start()
{
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("m_sk_conveyor_belt_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetSubConstantBufferLink(0, "RENDEROPTION", &RenderOptionMyInst, sizeof(RenderOption));

	SetStuff(GetLevel()->CreateActor<Tool_Rail>());
}

void Rail::Update(float _Delta)
{
	RenderOptionMyInst.UV.x += _Delta;

	GetTransform().SetWorldRotation({ 0, 0, 0 });
	//GameEngineDebug::OutPutString(std::to_string(GetTransform().GetWorldRotation().x) + ", " + std::to_string(GetTransform().GetWorldRotation().y) + ", " + std::to_string(GetTransform().GetWorldRotation().z));
}


Tool_Rail::Tool_Rail()
	:  FirstTimeCheck_(false)
	, MoveTime_(0)
{
}

Tool_Rail::~Tool_Rail()

{
}
void Tool_Rail::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Auto);
	GamePlayTool::SetObjectToolType(ObjectToolType::Rail);
}

void Tool_Rail::Update(float _Delta)
{
	if (FirstTimeCheck_ == false)
	{
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalPosition({0, 0, -50});
		Collision->GetTransform().SetWorldScale({50, 50, 100});
		Collision->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
			std::bind(&Tool_Rail::GetFrontStaticObject, this, std::placeholders::_1, std::placeholders::_2));
		Collision->Off();
		Collision->Death();
		Collision = nullptr;

		FirstTimeCheck_ = true;
	}

	if (Front_StaticObject_.lock() != nullptr)
	{
		if (GetCurrentMoveable() != nullptr)
		{
			if (GetCurrentMoveable() != After_Moveable_.lock())
			{
				After_Moveable_ = GetCurrentMoveable();
				float4 Pos = After_Moveable_.lock()->GetTransform().GetWorldPosition();
				After_Moveable_.lock()->SetParent(Front_StaticObject_.lock());
				After_Moveable_.lock()->GetTransform().SetLocalPosition(Front_StaticObject_.lock()->GetTransform().GetWorldPosition() - Pos);
				MoveTime_ = 0;
			}
		}


		if (After_Moveable_.lock() != nullptr)
		{
			MoveTime_ += _Delta;
			After_Moveable_.lock()->GetTransform().SetLocalPosition(float4::LerpLimit((GetTransform().GetWorldPosition()) - (Front_StaticObject_.lock()->GetTransform().GetWorldPosition()), Front_StaticObject_.lock()->GetToolPos(), MoveTime_ / 1.5f));
			if (MoveTime_ > 1.5f)
			{
				Front_StaticObject_.lock()->SetMoveable(After_Moveable_.lock());
				MoveTime_ = 0;
				After_Moveable_.reset();
				ReSetCurrentMoveable();
			}
		}
	}
}

void Tool_Rail::SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child)
{
	GamePlayTool::SetMoveable(_Child);

}


CollisionReturn Tool_Rail::GetFrontStaticObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (GetParent() == _Other->GetParent())
	{
		return CollisionReturn::ContinueCheck;
	}
	std::weak_ptr<GamePlayStaticObject> Object = _Other->GetParent()->CastThis<GamePlayStaticObject>();
	if (Object.lock() != nullptr)
	{
		Front_StaticObject_ = Object.lock();
		return CollisionReturn::Break;
	}
	return CollisionReturn::ContinueCheck;
}