#include "PreCompile.h"
#include "Stage_1_1.h"
#include "Player.h"

#include "UIDebugGUI.h"

#include "LoadingData.h"
#include "GlobalGameData.h"
#include <GameEngineCore/GameEngineBlur.h>

#include "FoodThumbnail.h"
#include "CookingBar.h"
#include "InGameUIActor.h"

#include "GraphicWindow.h"
#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>
#include "GlobalBloomActor.h"

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

	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
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
	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("1_1.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(6, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(31, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(32, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(33, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(16, "TextureAlpha");

	GlobalIOManager::Load(IOType::SortMap, 0);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 0);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	std::shared_ptr<GlobalBloomActor> BloomActor = CreateActor<GlobalBloomActor>();
	BloomActor->GetTransform().SetLocalPosition({ -1400, 500, 200 });
	BloomActor->GetTransform().SetWorldScale(float4::ONE * 500);

	std::shared_ptr<Player> MainPlayer_ = CreateActor<Player>();
	MainPlayer_->GetTransform().SetLocalPosition({ -1400, 500, 200 });
	MainPlayer_->SetCurFrontDir();

	ServerInitManager::StartInit();

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });

	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);

	LightObject_ = CreateActor<GameEngineLight>();
	LightObject_->GetTransform().SetWorldRotation({ 0.0f, 45.0f, 0.0f });
	GetMainCamera()->PushLight(LightObject_);

	//테스트용 - 동원
	//std::shared_ptr NewFoodThumbNail = CreateActor<FoodThumbnail>();
	//NewFoodThumbNail->LinkObject(MainPlayer, { 0,100, 0 });
	//NewFoodThumbNail->SetThumbnail(IngredientType::Prawn);

	//std::weak_ptr NewFoodThumbNail = CreateActor<CookingBar>();
	//NewFoodThumbNail.lock()->LinkObject(MainPlayer, { 0,0, 0 }, &GlobalGameData::DebugValue1_.x);

	return;
}