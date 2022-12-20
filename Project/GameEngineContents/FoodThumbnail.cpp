#include "PreCompile.h"
#include "FoodThumbnail.h"

#include "GlobalGameData.h"
#include "UIDebugGUI.h"

using namespace UI_Utility;

FoodThumbnail::FoodThumbnail()
{
}

FoodThumbnail::~FoodThumbnail()
{
}

void FoodThumbnail::SetThumbnail(IngredientType _Type)
{
	std::string _FileName = "Plus.png";
	_FileName = EnumToString(_Type);
	SingleThumbnail_.lock()->SetTexture(_FileName);
}

void FoodThumbnail::Start()
{
	//추후에 Main카메라 옮기면서 User7카메라도 이동시켜달라고하기
	std::string _FileName = "Plus.png";
	SingleThumbnail_ = CreateComponent<OverCookedUIRenderer>();
	SingleThumbnail_.lock()->SetTexture(_FileName);
	SingleThumbnail_.lock()->SetScaleRatio(0.30f);
	SingleThumbnail_.lock()->ScaleToTexture();
	SingleThumbnail_.lock()->ChangeCamera(CAMERAORDER::USER7);
	SingleThumbnail_.lock()->Off();
}

void FoodThumbnail::Update(float _DeltaTime)
{
	//if(ChaseActor_ == nullptr)
	if (ChaseActor_.lock() == nullptr)
	{
		return;
	}
	if (ChaseActor_.lock()->IsDeath() == true)
	{
		Death();
	}

	//Update Position
	float4 Pos = ChaseActor_.lock()->GetTransform().GetWorldPosition();
	float4 WantPos = GetLevel()->GetCameraActor(CAMERAORDER::MAINCAMERA)->GetCameraComponent()->GetWorldPositionToScreenPosition(Pos);
	float4 ScreenScale = GameEngineWindow::GetScale().Half();
	ScreenScale.y = -ScreenScale.y;
	WantPos = float4(WantPos.x, -WantPos.y, WantPos.z) - ScreenScale;
	WantPos.x = WantPos.x - WantPos.x * -0.02f;
	WantPos.y = WantPos.y - WantPos.y * -0.02f;
	WantPos += Offset_;
	GetTransform().SetLocalPosition(WantPos);
	SingleThumbnail_.lock()->On();
}

void FoodThumbnail::End()
{
}

void FoodThumbnail::LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset)
{
	ChaseActor_ = _Actor;
	Offset_ = _Offset;
}