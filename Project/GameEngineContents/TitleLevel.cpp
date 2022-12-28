#include "PreCompile.h"
#include "TitleLevel.h"
#include "Player.h"
#include "TitleVan.h"
#include "MouseInputWindow.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	{
		std::shared_ptr<GamePlayMapObject> Kevin = CreateActor<GamePlayMapObject>();
		KevinRenderer_ = Kevin->CreateComponent<GameEngineFBXAnimationRenderer>();
		KevinRenderer_->GetTransform().SetLocalPosition({ 220, 0, 160 });
		KevinRenderer_->GetTransform().SetLocalScale({ 20, 20, 20 });
		KevinRenderer_->GetTransform().SetLocalRotation({ 0, -130, 0 });
		KevinRenderer_->SetFBXMesh("m_kevin_02.fbx", "TextureAnimation");
		KevinRenderer_->CreateFBXAnimation("Phase0", GameEngineRenderingEvent("m_kevin_02.fbx", 0.04f, true), 4);
		KevinRenderer_->ChangeAnimation("Phase0");

		KevinRenderer_->AnimationBindTime("Phase0", [&](const GameEngineRenderingEvent& _Info, float _Time)
			{
				if (_Info.PlayTime >= 3.9f)
				{
					KevinRenderer_->ChangeAnimation("Phase0");
					KevinRenderer_->GetCurAnim()->bOnceEnd = false;
					KevinRenderer_->GetCurAnim()->Reset();
				}
			});
	}

	GetMainCameraActorTransform().SetLocalRotation({ 0, -163, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ 288.0f, 65.0f, 382.5f });

	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("TitleLevel.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(13, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(16, "TextureAlpha");

	PoleRenderer_ = CreateActor<GameEngineActor>()->CreateComponent<GameEngineFBXStaticRenderer>();
	PoleRenderer_->SetFBXMesh("Pole.fbx", "Texture");
	PoleRenderer_->GetTransform().SetWorldScale({ 200.f, 100.f });
	PoleRenderer_->GetTransform().SetWorldMove({ 0.f, 300.f });
	PoleRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	Shutter_ = CreateActor<GameEngineActor>();
	Shutter_->GetTransform().SetWorldPosition({0.f, 0.f, -1.f});
	ShutterRenderer_ = Shutter_->CreateComponent<GameEngineFBXStaticRenderer>();
	ShutterRenderer_->SetFBXMesh("Shatter.fbx", "Texture");
	ShutterRenderer_->GetTransform().SetWorldScale({ 200.f, 180.f });
	ShutterRenderer_->GetTransform().SetWorldRotation({ 0.f, 180.f});
	ShutterRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	std::shared_ptr<GameEngineFBXStaticRenderer> SkyPlane = CreateActor<GameEngineActor>()->CreateComponent<GameEngineFBXStaticRenderer>();
	SkyPlane->SetFBXMesh("m_menu_bg_sky.fbx", "TextureSkybox");
	SkyPlane->GetTransform().SetWorldScale({ 50.f, 50.f, 50.f });
	SkyPlane->SetSubConstantBufferLink(0, "RENDEROPTION", &SkyRenderOption_, sizeof(RenderOption));
}

void TitleLevel::Update(float _DeltaTime)
{
	SkyRenderOption_.UV.x -= _DeltaTime * 0.005f;

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

	if (-300.f < Shutter_->GetTransform().GetWorldPosition().y)
	{
		Shutter_->GetTransform().SetWorldUpMove(300.f, _DeltaTime);
	}
}

void TitleLevel::End()
{
}

void TitleLevel::LevelStartEvent()
{
	//std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();

	ServerInitManager::StartInit();
	if (nullptr != Player::GetMyPlayer())
	{
		Player::GetMyPlayer()->GetTransform().SetLocalPosition({ 0, -2000, 0 });
		Player::GetMyPlayer()->SetCurFrontDir();
	}
	GameBgmPlayer::BgmPlayer_->ChangeBgm("Frontend.wav");
}
