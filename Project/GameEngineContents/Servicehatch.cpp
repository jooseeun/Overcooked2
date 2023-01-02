#include "PreCompile.h"
#include "Servicehatch.h"
#include "Equipment_Plate.h"
#include "GamePlayLevel.h"
#include "PlateReturn.h"

Servicehatch::Servicehatch()
{
}

Servicehatch::~Servicehatch()
{
}

void Servicehatch::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 230, 50, 150 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, -10 });

	GetFBXMesh()->SetFBXMesh("m_dlc08_servicehatch_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ -60, 0, 0 });

	GetFBXMesh()->SetSubConstantBufferLink(0, "RENDEROPTION", &RenderOption_, sizeof(RenderOption));
	//GetFBXMesh()->SetSubMaterial(2, "TextureAlpha");

	SetStuff(GetLevel()->CreateActor<Tool_Servicehatch>());
}

void Servicehatch::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	RenderOption_.UV.x -= _DeltaTime * 0.1f;
}

Tool_Servicehatch::Tool_Servicehatch()
{
}

Tool_Servicehatch::~Tool_Servicehatch()
{
}
void Tool_Servicehatch::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::Servicehatch);
}

HoldDownEnum Tool_Servicehatch::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		std::weak_ptr<Equipment_Plate> Plate = (*_Moveable)->CastThis<Equipment_Plate>();
		if (Plate.lock() != nullptr)
		{
			GetLevel<GamePlayLevel>()->RequestHandOverFood(Plate.lock()->GetCombinFood()->GetFoodType());
			(*_Moveable)->Off();
			Tool_PlateReturn::GetInst()->SetPlateCooltime(Plate.lock());
			Plate.lock()->GetCombinFood()->Clear();
			(*_Moveable) = nullptr;

			return HoldDownEnum::HoldUp;
		}
	}
	return HoldDownEnum::Nothing;
}