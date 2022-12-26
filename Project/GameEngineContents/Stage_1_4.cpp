#include "PreCompile.h"
#include "Stage_1_4.h"
#include "Player.h"
#include "TestPortal.h"

#include "PortalCollision.h"

#include "GraphicWindow.h"
#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>

Stage_1_4::Stage_1_4()
{
}

Stage_1_4::~Stage_1_4()
{
}

void Stage_1_4::PlayLevelStart()
{
	//CreateActor<LevelActor>()->SetLevelMesh("1_4.FBX");

	//GlobalIOManager::Load(IOType::SortMap, 3);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//GlobalIOManager::Load(IOType::UnsortMap, 3);
	//DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	//GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	//GetMainCameraActorTransform().SetLocalPosition({ -1173  , 3300   , 2500 });

	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	//MainPlayer->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
}

void Stage_1_4::PlayLevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
	}
}

void Stage_1_4::End()
{
}

void Stage_1_4::PlayLevelStartEvent()
{
	GameBgmPlayer::BgmPlayer_->ChangeBgm("Spellbound.wav");
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;

	if (nullptr != Player::GetMyPlayer())
	{
		if (Player::GetMyPlayer()->PlayerPNum == 1)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 2)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 3)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 4)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
		}
		Player::GetMyPlayer()->SetCurFrontDir();
	}

	else
	{
		std::shared_ptr<Player> MainPlayer_ = CreateActor<Player>();
		MainPlayer_->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
		MainPlayer_->SetCurFrontDir();
	}

	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("1_4.FBX");

	WallColor_.MulColor = float4{ 1.75f, 1.75f, 1.75f, 1.f };
	LevelActor_->GetRenderer()->SetSubConstantBufferLink(38, "PixelData", &WallColor_, sizeof(WallColor));

	CreateActor<TestPortal>();

	GlobalIOManager::Load(IOType::SortMap, 3);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 3);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1173  , 3300   , 2500 });


	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);


	std::shared_ptr<PortalCollision> Blue1 = CreateActor<PortalCollision>();
	Blue1->SetPotalType(MapObjType::Portal_Blue);
	Blue1->GetTransform().SetWorldPosition({ -370.00,1.00,250.00 });
	std::shared_ptr<PortalCollision> Blue2 = CreateActor<PortalCollision>();
	Blue2->SetPotalType(MapObjType::Portal_Blue);
	Blue2->GetTransform().SetWorldPosition({ -963.00,180.00,229.00 });

	std::shared_ptr<PortalCollision> Puple1 = CreateActor<PortalCollision>();
	Puple1->SetPotalType(MapObjType::Portal_Blue);
	Puple1->GetTransform().SetWorldPosition({ -1471.00,180.00,229.00 });
	std::shared_ptr<PortalCollision> Puple2 = CreateActor<PortalCollision>();
	Puple2->SetPotalType(MapObjType::Portal_Blue);
	Puple2->GetTransform().SetWorldPosition({ -2057.00,1.00,250.00 });


	Blue1->SetNextPotal(Blue2);
	Blue1->SetNextPos({ -963.00, 180.00, 229.00 });

	Blue2->SetNextPotal(Blue1);
	Blue2->SetNextPos({ -370.00,1.00,250.00 });

	Puple1->SetNextPotal(Puple2);
	Puple1->SetNextPos({ -2057.00,1.00,250.00 });

	Puple2->SetNextPotal(Puple1);
	Puple2->SetNextPos({ -1471.00,180.00,229.00 });

	return;
}

