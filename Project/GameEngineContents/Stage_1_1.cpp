#include "PreCompile.h"
#include "Stage_1_1.h"
#include "Player.h"

#include "UIDebugGUI.h"

#include "LoadingData.h"
#include "GlobalGameData.h"
#include <GameEngineCore/GameEngineBlur.h>

#include "FoodThumbnail.h"

#include "GraphicWindow.h"

#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>


Stage_1_1::Stage_1_1()
{
}

Stage_1_1::~Stage_1_1()
{
}

void Stage_1_1::PlayLevelStart()
{
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	//CreateActor<LevelActor>()->SetLevelMesh("1_1.FBX");

	//GlobalIOManager::Load(IOType::SortMap, 0);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//GlobalIOManager::Load(IOType::UnsortMap, 0);
	//DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	//MainPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200 });

	//std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	//GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	//GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });
}

void Stage_1_1::PlayLevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetUICameraActor()->FreeCameraModeOnOff();
	}
}

void Stage_1_1::End()
{
}

void Stage_1_1::PlayLevelStartEvent()
{
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;
	CreateActor<LevelActor>()->SetLevelMesh("1_1.FBX");

	GlobalIOManager::Load(IOType::SortMap, 0);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 0);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200 });

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });

	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	//음식 아이콘이 보이는 카메라 입니다.- 동원
	//GetCameraActor(CAMERAORDER::USER7)->GetTransform().SetLocalRotation({ 60, 180, 0 });
	//GetCameraActor(CAMERAORDER::USER7)->GetTransform().SetLocalPosition({ -1400, 2200, 1600 });
	UIDebugGUI::Main_->AddTransform("User7", &GetCameraActor(CAMERAORDER::USER7)->GetTransform());

	//테스트용 - 동원
	std::shared_ptr NewFoodThumbNail = CreateActor<FoodThumbnail>();
	NewFoodThumbNail->GetTransform().SetLocalRotation({ -60,-180,0 });
	//	NewFoodThumbNail->SetPivot({ -1400, 500, 200 });
	NewFoodThumbNail->LinkObject(MainPlayer, { 0,280, 0 });

	return;
}