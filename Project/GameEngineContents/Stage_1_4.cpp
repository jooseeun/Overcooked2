#include "PreCompile.h"
#include "Stage_1_4.h"
#include "Player.h"
#include "TestPortal.h"

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
}

void Stage_1_4::End()
{
}

void Stage_1_4::PlayLevelStartEvent()
{
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;

	CreateActor<LevelActor>()->SetLevelMesh("1_4.FBX");

	CreateActor<TestPortal>();

	GlobalIOManager::Load(IOType::SortMap, 3);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 3);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1173  , 3300   , 2500 });

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });

	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);

	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	GraphicWindow::Main_->SetBloom(GlobalBloom_);

	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();
	GraphicWindow::Main_->SetVignette(GlobalVignette_);

	return;
}