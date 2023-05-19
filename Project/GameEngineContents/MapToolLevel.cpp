#include "PreCompile.h"
#include "MapToolLevel.h"
#include "SoundControlWindow.h"

MapToolLevel::MapToolLevel() 
{
}

MapToolLevel::~MapToolLevel() 
{
}

void MapToolLevel::Start()
{
	Window_ = MapEditorGUI::CreateGUIWindow<MapEditorWindow>("MapEditor", nullptr);

	Window_->SetLevel(this);
	Window_->Off();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2300, 1600 });

	// 생성 가능한 UnSortActor 
	UnsortNameLoader_->Load(Window_->GetAllUnSortActorName(), "AllUnsortActorName");
}

void MapToolLevel::Update(float _DeltaTime)
{
}

void MapToolLevel::End()
{
}

void MapToolLevel::LevelStartEvent()
{
	GameSoundPlayer::BgmPlayer_->BgmStop();
	GameSoundPlayer::EffectPlayer_->EffectStop();
	SoundControlWindow::Main_->Off();
	Window_->On();
}

void MapToolLevel::LevelEndEvent()
{
	Window_->Off();
}
