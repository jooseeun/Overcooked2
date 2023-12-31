#include "PreCompile.h"
#include "Stage_2_1.h"
#include "Player.h"
#include "IceBlock.h"
#include "Cannon.h"

#include "PortalCollision.h"
#include "GraphicWindow.h"

#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>
Stage_2_1::Stage_2_1()
	: CannonObj_(nullptr)
{
}

Stage_2_1::~Stage_2_1()
{
}

void Stage_2_1::PlayLevelStart()
{
}

void Stage_2_1::PlayLevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
	}

	WaterRenderOption1_.UV.y += _DeltaTime * 0.25f;
	WaterRenderOption2_.UV.y += _DeltaTime * 0.25f;
}

void Stage_2_1::End()
{
}

void Stage_2_1::PlayLevelStartEvent()
{
	GameSoundPlayer::BgmPlayer_->ChangeBgm("DLC09_Fairground_Music.wav");

	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;

	if (nullptr != Player::GetMyPlayer())
	{
		if (Player::GetMyPlayer()->PlayerPNum == 1)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -882,100,-1133 });
			Player::GetMyPlayer()->SetResponePos({ -882,100,-1133 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 2)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1168,100,-1133 });
			Player::GetMyPlayer()->SetResponePos({ -1168,100,-1133 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 3)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -882,100,-820 });
			Player::GetMyPlayer()->SetResponePos({ -882,100,-820 });
		}
		else if (Player::GetMyPlayer()->PlayerPNum == 4)
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -1168,100,-820 });
			Player::GetMyPlayer()->SetResponePos({ -1168,100,-820 });
		}
		else
		{
			Player::GetMyPlayer()->GetTransform().SetLocalPosition({ -882,100,-1133 });
			Player::GetMyPlayer()->SetResponePos({ -882,100,-1133 });
		}
		Player::GetMyPlayer()->SetCurFrontDir();
	}

	else
	{
		std::shared_ptr<Player> MainPlayer_ = CreateActor<Player>();
		MainPlayer_->GetTransform().SetLocalPosition({ -882,100,-1133 });
		MainPlayer_->SetResponePos({ -882,100,-1133 });
		MainPlayer_->SetCurFrontDir();
	}

	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("2_1.FBX");

	WaterActor_ = CreateActor<GameEngineActor>();
	WaterActor_->GetTransform().SetWorldScale({ 2000, 3000, 1 });
	WaterActor_->GetTransform().SetWorldPosition({ -1500.f, -50.f, -1200.f });
	WaterActor_->GetTransform().SetWorldRotation({ 90.f, 0.f, 0.f });

	{
		std::shared_ptr<GameEngineTextureRenderer> Water = WaterActor_->CreateComponent<GameEngineTextureRenderer>();
		Water->SetMaterial("Water");
		Water->SetTexture("Icy_Water.png");
		Water->GetShaderResources().SetConstantBufferLink("RENDEROPTION", &WaterRenderOption1_, sizeof(RenderOption));
	}

	{
		std::shared_ptr<GameEngineTextureRenderer> Water = WaterActor_->CreateComponent<GameEngineTextureRenderer>();
		Water->SetMaterial("Water");
		Water->SetTexture("water2.png");
		Water->GetShaderResources().SetConstantBufferLink("RENDEROPTION", &WaterRenderOption2_, sizeof(RenderOption));
	}


	if (ServerInitManager::Net != nullptr && ServerInitManager::Net->GetIsHost())
	{
		GlobalIOManager::Load(IOType::SortMap, 4);
		DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	}

	GlobalIOManager::Load(IOType::UnsortMap, 4);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1662, 2700, 400 });


	std::shared_ptr<IceBlock> Block = CreateActor <IceBlock>();
	Block->GetTransform().SetWorldPosition({ -1383.f, 0.f, -2070.f });
	Block->SetIceBlockType(IceBlockType::Ice11);
	Block->SetIceBlockMesh(IceBlockType::Ice11);
	Block->SwitchMovable();

	std::shared_ptr<PortalCollision> Puple1 = CreateActor<PortalCollision>();
	Puple1->SetPotalType(MapObjType::Portal_Blue);
	Puple1->GetTransform().SetWorldPosition({ -600.0,260.00,-1402.00 });

	std::shared_ptr<PortalCollision> Puple2 = CreateActor<PortalCollision>();
	Puple2->SetPotalType(MapObjType::Portal_Blue);
	Puple2->GetTransform().SetWorldPosition({ -2788.00,50.00,-1021.00 });

	Puple1->SetNextPotal(Puple2);
	Puple1->SetNextPos({ -2788.00,50.00,-1021.00 });

	Puple2->SetNextPotal(Puple1);
	Puple2->SetNextPos({ -600.0,260.00,-1402.00 });

	if (true == ServerInitManager::Net->GetIsHost())
	{
		CannonObj_ = CreateActor<Cannon>();
		CannonObj_->GetTransform().SetWorldPosition({ -606.f, 0.f, -1111.f });
		CannonObj_->ClientInit(ServerObjectType::Object, 99);
	}

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
	return;
}
