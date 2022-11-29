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
#include <GameEngineCore/GlobalBloom.h>
#include "WaterTest.h"

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
	std::shared_ptr<LevelActor> Tmp = CreateActor<LevelActor>();
	Tmp->SetLevelMesh("1_1.FBX");

	//std::vector<std::vector<GameEngineRenderUnit>>& TmpUnits2 = Tmp->GetRenderer()->GetAllRenderUnit();
	//for (size_t i = 0; i < TmpUnits2.size(); i++)
	//{
	//	for (size_t j = 0; j < TmpUnits2[i].size(); j++)
	//	{
	//		//std::shared_ptr<GameEngineMaterial> TmpMat = TmpUnits2[i][j].GetCloneMaterial();
	//		//TmpMat->SetWireFrame();
	//		TmpUnits2[i][j].GetCloneMaterial()->SetWireFrame();
	//	}
	//}

	//std::vector<GameEngineRenderUnit> TmpUnits = Tmp->GetRenderer()->GetAllRenderUnit()[7];
	//for (size_t i = 0; i < TmpUnits.size(); i++)
	//{
	//	TmpUnits[i].GetCloneMaterial()->SetOutputMergerBlend("AddBlend");
	//}

	GlobalIOManager::Load(IOType::SortMap, 0);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 0);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	std::shared_ptr<WaterTest> MainWater = CreateActor<WaterTest>();
	MainWater->GetTransform().SetLocalPosition({ -1400, 500, 200 });
	MainWater->GetTransform().SetWorldScale({ 800, 800, 800 });

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200 });

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });

	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);

	//테스트용 - 동원
	std::shared_ptr NewFoodThumbNail = CreateActor<FoodThumbnail>();
	NewFoodThumbNail->LinkObject(MainPlayer, { 0,100, 0 });
	NewFoodThumbNail->SetThumbnail(IngredientType::None);

	return;
}