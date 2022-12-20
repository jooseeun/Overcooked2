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

	{
		std::shared_ptr<GamePlayMapObject> Kevin = CreateActor<GamePlayMapObject>();
		KevinRenderer_ = Kevin->CreateComponent<GameEngineFBXAnimationRenderer>();
		KevinRenderer_->GetTransform().SetLocalPosition({ 197, 0, 150 });
		KevinRenderer_->GetTransform().SetLocalScale({ 20, 20, 20 });
		KevinRenderer_->GetTransform().SetLocalRotation({0, -160, 0});
		KevinRenderer_->SetFBXMesh("m_kevin_02.fbx", "TextureAnimation");
		KevinRenderer_->CreateFBXAnimation("Phase0", GameEngineRenderingEvent("m_kevin_02.fbx", 0.05f, true), 6);
		KevinRenderer_->ChangeAnimation("Phase0");

		KevinRenderer_->AnimationBindTime("Phase0", [&](const GameEngineRenderingEvent& _Info, float _Time)
			{
				if (_Info.PlayTime >= 7.f)
				{
					KevinRenderer_->ChangeAnimation("Phase0");
					KevinRenderer_->GetCurAnim()->bOnceEnd = false;
					KevinRenderer_->GetCurAnim()->Reset();
				}
			});
	}
	

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
