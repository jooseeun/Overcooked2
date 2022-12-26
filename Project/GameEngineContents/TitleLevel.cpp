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

	std::shared_ptr<TitleVan> TitleVan_ = CreateActor<TitleVan>();
	TitleVan_->GetTransform().SetLocalPosition({ 180, -10, 50 });
	TitleVan_->GetTransform().SetLocalRotation({ 0, 10, 0 });

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
	

	GetMainCameraActorTransform().SetLocalRotation({ 0, -163, 0});
	GetMainCameraActorTransform().SetLocalPosition({ 288.0f, 65.0f, 382.5f });

	LevelActor_ = CreateActor<LevelActor>();	
	LevelActor_->SetLevelMesh("TitleLevel.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(14, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(17, "TextureAlpha");

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

	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
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
}
