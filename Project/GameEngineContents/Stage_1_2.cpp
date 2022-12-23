#include "PreCompile.h"
#include "Stage_1_2.h"
#include "Player.h"
#include "Bird_Flying.h"
#include "MoveCar.h"

#include "GraphicWindow.h"
#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>

Stage_1_2::Stage_1_2()
{
}

Stage_1_2::~Stage_1_2()
{
}

void Stage_1_2::PlayLevelStart()
{
	//CreateActor<LevelActor>()->SetLevelMesh("1_2.FBX");

	//GlobalIOManager::Load(IOType::SortMap, 1);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//GlobalIOManager::Load(IOType::UnsortMap, 1);
	//DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	//MainPlayer->GetTransform().SetLocalPosition({ -1500, 500, 0 });

	//GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	//GetMainCameraActorTransform().SetLocalPosition({ -2509, 2500 , 950 });
}

void Stage_1_2::PlayLevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
	}
}

void Stage_1_2::End()
{
}

void Stage_1_2::PlayLevelStartEvent()
{
	if (nullptr != Player::GetMyPlayer())
	{
		if (Player::GetMyPlayer()->PlayerPNum == 1)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1500, 500, -500 });
			Player::GetMyPlayer()->SetResponePos({ -1500, 500, -500 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 2)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1500, 500, -500 });
			Player::GetMyPlayer()->SetResponePos({ -1500, 500, -500 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 3)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1500, 500, -500 });
			Player::GetMyPlayer()->SetResponePos({ -1500, 500, -500 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 4)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1500, 500, -500 });
			Player::GetMyPlayer()->SetResponePos({ -1500, 500, -500 });
		}
		Player::GetMyPlayer()->SetCurFrontDir();
	}
	else
	{
		std::shared_ptr<Player> MainPlayer_ = CreateActor<Player>();
		MainPlayer_->GetTransform().SetLocalPosition({ -1500, 500, -500 });
		MainPlayer_->SetResponePos({ -1500, 500, -500 });


	}

	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;
	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("1_2.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(10, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(11, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(12, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(53, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(54, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(55, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(2, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(33, "TextureAlpha");

	GlobalIOManager::Load(IOType::SortMap, 1);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 1);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);



	{
		std::shared_ptr<GlobalBloomActor> BloomActor = CreateActor<GlobalBloomActor>();
		BloomActor->GetTransform().SetLocalPosition({ -3750.f, 300.f, -700.f });
		BloomActor->GetTransform().SetLocalRotation({0.f, 90.f});
		BloomActor->GetTransform().SetWorldScale({ 2500, 450 });
		BloomActor->SetColor({ 0.12f, 0.f, 1.f, 1.f });
	}

	std::shared_ptr<Bird_Flying> Pigeon_ = CreateActor<Bird_Flying>();
	Pigeon_->GetTransform().SetLocalPosition({ -700, 800, -500 });
	Pigeon_->GetTransform().SetLocalRotation({0, 10, 0});
	Pigeon_->GetTransform().PixLocalNegativeX();	
	Pigeon_->SetStartPosition(Pigeon_->GetTransform().GetLocalPosition());

	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -2509, 2500 , 950 });

	{
		std::shared_ptr<MoveCar> Car = CreateActor<MoveCar>();
		Car->GetTransform().SetWorldPosition({-2900.f, 0.f, 1000.f});
		Car->SetStartPos(Car->GetTransform().GetWorldPosition());
		Car->SetEndPos({ -2500.f, 0.f, -3000.f });
		Car->SetStartTime(20.f);
		Car->SetCarMesh("Car_Green.fbx");
	}

	{
		std::shared_ptr<MoveCar> Car = CreateActor<MoveCar>();
		Car->GetTransform().SetWorldPosition({ -2500.f, 0.f, -3000.f });
		Car->SetStartPos(Car->GetTransform().GetWorldPosition());
		Car->GetTransform().SetWorldRotation({0.f, 180.f, 0.f});
		Car->SetEndPos({ -2900.f, 0.f, 1000.f });
		Car->SetStartTime(25.f);
		Car->SetCarMesh("Car_Blue.fbx");
	}
	
	return;
}