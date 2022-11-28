#include "PreCompile.h"
#include "FoodThumbnail.h"

#include "GlobalGameData.h"
#include "UIDebugGUI.h"

FoodThumbnail::FoodThumbnail()
{
}

FoodThumbnail::~FoodThumbnail()
{
}

void FoodThumbnail::SetThumbnail(FoodType _Type)
{
	std::string _FileName = "Plus.png";
	switch (_Type)
	{
	case FoodType::None:
		_FileName = "Plus.png";
		break;
	case FoodType::Tomato:
		break;
	case FoodType::Onion:
		break;
	case FoodType::Potato:
		break;
	case FoodType::Dough:
		break;
	case FoodType::Seaweed:
		break;
	case FoodType::Mushroom:
		break;
	case FoodType::Meat:
		break;
	case FoodType::Lettuce:
		break;
	case FoodType::Rice:
		break;
	case FoodType::Flour:
		break;
	case FoodType::Bread:
		break;
	case FoodType::Fish:
		break;
	case FoodType::Sausage:
		break;
	case FoodType::DumplingSkin:
		break;
	case FoodType::Egg:
		break;
	case FoodType::Chicken:
		break;
	case FoodType::Burrito:
		break;
	case FoodType::Cheese:
		break;
	case FoodType::Carrot:
		break;
	case FoodType::Chocolate:
		break;
	case FoodType::Honey:
		break;
	case FoodType::PastaNoodles:
		break;
	case FoodType::Prawn:
		_FileName = "prawn_Icon.png";
		break;
	case FoodType::Cucumber:
		break;
	default:
		MsgBoxAssert("선택한 이미지 리소스가 아직 추가되지 않았습니다. UI담당에게 문의하세요");
		break;
	}
	SingleThumbnail_->SetTexture(_FileName);
}

void FoodThumbnail::Start()
{
	//추후에 Main카메라 옮기면서 User7카메라도 이동시켜달라고하기
	std::string _FileName = "Plus.png";
	SingleThumbnail_ = CreateComponent<OverCookedUIRenderer>();
	SingleThumbnail_->SetTexture(_FileName);
	SingleThumbnail_->SetScaleRatio(0.30f);
	SingleThumbnail_->ScaleToTexture();
	SingleThumbnail_->ChangeCamera(CAMERAORDER::USER7);
	//SingleThumbnail_->Off();
}

void FoodThumbnail::Update(float _DeltaTime)
{
	//if(ChaseActor_ == nullptr)
	if (ChaseActor_ == nullptr)
	{
		return;
	}
	if (ChaseActor_->IsDeath() == true)
	{
		Death();
	}

	//Update Position
	float4 Pos = ChaseActor_->GetTransform().GetWorldPosition();
	float4 WantPos = GetLevel()->GetCameraActor(CAMERAORDER::MAINCAMERA)->GetCameraComponent()->GetWorldPositionToScreenPosition(Pos);
	float4 ScreenScale = GameEngineWindow::GetScale().Half();
	ScreenScale.y = -ScreenScale.y;
	WantPos = float4(WantPos.x, -WantPos.y, WantPos.z) - ScreenScale;
	WantPos.x = WantPos.x - WantPos.x * -0.02f;
	WantPos.y = WantPos.y - WantPos.y * -0.02f;
	WantPos += Offset_;
	GetTransform().SetLocalPosition(WantPos);
}

void FoodThumbnail::End()
{
}

void FoodThumbnail::LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset)
{
	ChaseActor_ = _Actor;
	Offset_ = _Offset;
}