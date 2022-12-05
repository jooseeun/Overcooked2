#include "PreCompile.h"
#include "TitleLevel.h"
#include "Player.h"
#include "TitleVan.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	std::shared_ptr<TitleVan> TitleVan_ = CreateActor<TitleVan>();
	TitleVan_->GetTransform().SetLocalPosition({ 0, 0, 0});

	GetMainCameraActorTransform().SetLocalRotation({ 0, -158, 0});
	GetMainCameraActorTransform().SetLocalPosition({ 659, 21, 1402});

	CreateActor<LevelActor>()->SetLevelMesh("TitleLevel.FBX");

	std::shared_ptr<GameEngineFBXStaticRenderer> SkyPlane = CreateActor<GameEngineActor>()->CreateComponent<GameEngineFBXStaticRenderer>();
	SkyPlane->SetFBXMesh("m_menu_bg_sky.fbx", "TextureSkybox");
	SkyPlane->GetTransform().SetWorldScale({ 50.f , 50.f , 50.f });
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetUICameraActor()->FreeCameraModeOnOff();
	}
}

void TitleLevel::End()
{
}
