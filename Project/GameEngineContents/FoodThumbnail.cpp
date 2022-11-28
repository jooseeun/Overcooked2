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

void FoodThumbnail::SetThumbnail(IngredientType _Type)
{
	std::string _FileName = "Plus.png";
	switch (_Type)
	{
	case IngredientType::None:
		_FileName = "Plus.png";
		break;
	case IngredientType::Tomato:
		break;
	case IngredientType::Onion:
		break;
	case IngredientType::Potato:
		break;
	case IngredientType::Dough:
		break;
	case IngredientType::Seaweed:
		break;
	case IngredientType::Mushroom:
		break;
	case IngredientType::Meat:
		break;
	case IngredientType::Lettuce:
		break;
	case IngredientType::Rice:
		break;
	case IngredientType::Flour:
		break;
	case IngredientType::Bread:
		break;
	case IngredientType::Fish:
		break;
	case IngredientType::Sausage:
		break;
	case IngredientType::DumplingSkin:
		break;
	case IngredientType::Egg:
		break;
	case IngredientType::Chicken:
		break;
	case IngredientType::Burrito:
		break;
	case IngredientType::Cheese:
		break;
	case IngredientType::Carrot:
		break;
	case IngredientType::Chocolate:
		break;
	case IngredientType::Honey:
		break;
	case IngredientType::PastaNoodles:
		break;
	case IngredientType::Prawn:
		_FileName = "prawn_Icon.png";
		break;
	case IngredientType::Cucumber:
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