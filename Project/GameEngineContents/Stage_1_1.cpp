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
#include "PlayerRunningPuff.h"
#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>
#include "GameEngineStatusWindow.h"

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
	GameEngineStatusWindow::AddDebugRenderTarget("1", GetMainCamera()->GetCameraDeferredGBufferRenderTarget());
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

	if (LightObject_ != nullptr)
	{
		LightObject_->GetTransform().SetWorldRotation({ GraphicWindow::Main_->GetLightPositionX(), GraphicWindow::Main_->GetLightPositionY(), GraphicWindow::Main_->GetLightPositionZ() });

		LightObject_->GetLightData().DifLightPower = GraphicWindow::Main_->GetLightDif();
		LightObject_->GetLightData().AmbLightPower = GraphicWindow::Main_->GetLightAmb();
	}


}

void Stage_1_1::End()
{

}

void Stage_1_1::PlayLevelStartEvent()
{



	if (nullptr != Player::GetMyPlayer())
	{
		if (Player::GetMyPlayer()->PlayerPNum == 1)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1158, 100, 187 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 2)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1779, 100, 187 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 3)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1158, 100, 547 });
		}
		else
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1779, 100, 547 });
		}
		Player::GetMyPlayer()->SetCurFrontDir();
	}
	else
	{
		std::shared_ptr<Player> MainPlayer_ = CreateActor<Player>();
		MainPlayer_->GetTransform().SetLocalPosition({ -1158, 100, 187 });
		MainPlayer_->SetCurFrontDir();
	}

	GameBgmPlayer::BgmPlayer_->ChangeBgm("TheNeonCity.wav");
	GameBgmPlayer::EffectBgmPlayer_->ChangeEffectBgm("Sushi_Crowd_Ambience.wav");

	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;
	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("1_1.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(6, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(30, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(32, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(33, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(16, "TextureAlpha");


	if (ServerInitManager::Net != nullptr && ServerInitManager::Net->GetIsHost())
	{
		GlobalIOManager::Load(IOType::SortMap, 0);
		DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	}

	GlobalIOManager::Load(IOType::UnsortMap, 0);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);


	{
		std::shared_ptr<GlobalBloomActor> BloomActor = CreateActor<GlobalBloomActor>();
		BloomActor->GetTransform().SetLocalPosition({ -1650, 300, -120 });
		BloomActor->GetTransform().SetWorldScale({ 450, 2000 });
		BloomActor->SetColor({ 0.12f, 0.f, 1.f, 1.f });
	}

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });

	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);

	//LightObject_ = CreateActor<GameEngineLight>();
	//LightObject_->GetTransform().SetWorldRotation({ 0.0f, 45.0f, 0.0f });

	//LightObject_->GetLightData().DifLightPower = 0.f;
	//LightObject_->GetLightData().AmbLightPower = 10.0f;
	//GetMainCamera()->PushLight(LightObject_);

	//테스트용 - 동원
	//std::shared_ptr NewFoodThumbNail = CreateActor<FoodThumbnail>();
	//NewFoodThumbNail->LinkObject(MainPlayer, { 0,100, 0 });
	//NewFoodThumbNail->SetThumbnail(IngredientType::Prawn);

	//std::weak_ptr NewFoodThumbNail = CreateActor<CookingBar>();
	//NewFoodThumbNail.lock()->LinkObject(MainPlayer, { 0,0, 0 }, &GlobalGameData::DebugValue1_.x);

	return;
}

