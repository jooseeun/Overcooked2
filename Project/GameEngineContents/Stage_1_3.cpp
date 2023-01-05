#include "PreCompile.h"
#include "Stage_1_3.h"
#include "Player.h"

#include "GraphicWindow.h"
#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>

Stage_1_3::Stage_1_3()
{
}

Stage_1_3::~Stage_1_3()
{
}

void Stage_1_3::PlayLevelStart()
{
	//CreateActor<LevelActor>()->SetLevelMesh("1_3.FBX");

	//GlobalIOManager::Load(IOType::SortMap, 2);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//GlobalIOManager::Load(IOType::UnsortMap, 2);
	//DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	//GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	//GetMainCameraActorTransform().SetLocalPosition({ -2606 , 1900  , 900 });

	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	//MainPlayer->GetTransform().SetLocalPosition({ -2606, 500, 0 });


}

void Stage_1_3::PlayLevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
	}
}

void Stage_1_3::End()
{
}

void Stage_1_3::PlayLevelStartEvent()
{
	GameBgmPlayer::BgmPlayer_->ChangeBgm("CityLiving.wav");
	GameBgmPlayer::EffectBgmPlayer_->ChangeEffectBgm("Sushi_Crowd_Ambience.wav");
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;

	if (nullptr != Player::GetMyPlayer())
	{
		if (Player::GetMyPlayer()->PlayerPNum == 1)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1506, 500, 0 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 2)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1706, 500, 0 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 3)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -2006, 500, 0 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 4)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -2006, 500, 0 });
		}
		else
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -2006, 500, 0 });
		}
		Player::GetMyPlayer()->SetCurFrontDir();
	}

	else
	{
		std::shared_ptr<Player> MainPlayer_ = CreateActor<Player>();
		MainPlayer_->GetTransform().SetLocalPosition({ -2006, 500, 0 });
		MainPlayer_->SetCurFrontDir();
	}

	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("1_3.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(1, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(19, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(38, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(56, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(57, "TextureAlpha");

	if (ServerInitManager::Net != nullptr && ServerInitManager::Net->GetIsHost())
	{
		GlobalIOManager::Load(IOType::SortMap, 2);
		DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	}

	GlobalIOManager::Load(IOType::UnsortMap, 2);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -2606 , 1950  , 1000 });


	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);
	return;
}
