#include "PreCompile.h"
#include "UIActor.h"
#include "OverCookedUIRenderer.h"
#include "UIDebugGUI.h"
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "GlobalGameData.h"

UIActor::UIActor()
{
}

UIActor::~UIActor()
{
}

void UIActor::Start()
{
	InitTransitionRenderer();
	UIStart();
	//std::shared_ptr<OverCookedTransition> NewEffect = GetLevel()->GetUICamera()->GetCameraRenderTarget()->AddEffect<OverCookedTransition>();
}

void UIActor::Update(float _DeltaTime)
{
	//FadeIn
	if (TransitionIcon_->IsFinishFadeIn_ == true)
	{
		TransitionIcon_->Off();
		BlackRenderer_->Off();
		TransitionIcon_->IsFinishFadeIn_ = false;
	}
	UIUpdate(_DeltaTime);
}

void UIActor::End()
{
	UIEnd();
}

void UIActor::StartFadeOut()
{
	TransitionIcon_->On();
	TransitionIcon_->StartFadeOut(7.0f);
	BlackRenderer_->On();
}

void UIActor::StartFadeIn()
{
	TransitionIcon_->On();
	TransitionIcon_->StartFadeIn();
	BlackRenderer_->On();
}

void UIActor::ResistDebug(std::string_view _Name, GameEngineTransform& Trans)
{
	UIDebugGUI::Main_->AddTransform(_Name.data(), &Trans);
}

void UIActor::CreatePlayerIcon(int _Index, std::string_view _Name)
{
	PlayerIcon NewIcon;

	NewIcon.Index = _Index;
	NewIcon.Name = _Name;

	//부모
	std::shared_ptr<OverCookedUIRenderer> NewParent = CreateUIRenderer("AvatarSelectionRing.png");
	NewParent->GetTransform().SetLocalScale({ 1,1,1 });
	NewParent->GetTransform().SetLocalPosition({ 0,-180,0 });
	NewIcon.Parent = NewParent;

	//Hat Icon
	std::string HatFile;
	switch (_Index)
	{
	case 0:
		HatFile = "hat_blue.png";
		break;
	case 1:
		HatFile = "hat_red.png";
		break;
	case 2:
		HatFile = "hat_green.png";
		break;
	case 3:
		HatFile = "hat_yellow.png";
		break;
	default:
		break;
	}

	std::shared_ptr<OverCookedUIRenderer> Hat = CreateUIRenderer(HatFile);
	Hat->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.Hat = Hat;

	std::shared_ptr<OverCookedUIRenderer> NameBox = CreateUIRenderer("UI_BigButtonsSmall_01.png");
	NameBox->GetTransform().SetLocalPosition({ 0,-80,-500 });
	NameBox->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.NameBox = NameBox;

	//숫자폰트
	std::shared_ptr<GameEngineFontRenderer> NewCountFont = CreateComponent<GameEngineFontRenderer>(_Name.data());
	NewCountFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewCountFont->SetText(std::to_string(_Index + 1), "Naughty Squirrel");
	NewCountFont->SetColor({ 0.4f,0.4f,0.4f,0.6f });
	NewCountFont->SetSize(49.f);
	NewCountFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewCountFont->SetAffectTransform(true);
	NewCountFont->GetTransform().SetLocalMove({ -80,50.f,-1 });
	NewCountFont->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.CountFont = NewCountFont;

	//이름폰트
	std::shared_ptr<GameEngineFontRenderer> NewNameFont = CreateComponent<GameEngineFontRenderer>(_Name.data());
	NewNameFont->ChangeCamera(CAMERAORDER::UICAMERA);
	NewNameFont->SetText(_Name.data(), "Naughty Squirrel");
	NewNameFont->SetColor({ 1.f,1.f,1.f,1.f });
	NewNameFont->SetSize(20.f);
	NewNameFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewNameFont->SetAffectTransform(true);
	NewNameFont->GetTransform().SetLocalMove({ 0,-62.f,-501 });
	NewNameFont->GetTransform().SetParentTransform(NewParent->GetTransform());
	NewIcon.NameFont = NewNameFont;

	//플레이어 매쉬
	std::vector<std::string> PlayerName_;
	PlayerName_.resize(6);
	PlayerName_[0] = "AlienGreen";
	PlayerName_[1] = "Buck";
	PlayerName_[2] = "Crocodile";
	PlayerName_[3] = "Dora";
	PlayerName_[4] = "Eagle";
	PlayerName_[5] = "Panda";

	int PlayerIndex = GlobalGameData::PlayerCustom_[_Index];

	std::shared_ptr< GameEngineFBXAnimationRenderer> PlayerIdleRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	PlayerIdleRenderer_->SetFBXMesh(PlayerName_[PlayerIndex] + "_Idle.FBX", "TextureAnimation");
	PlayerIdleRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	PlayerIdleRenderer_->CreateFBXAnimation(PlayerName_[PlayerIndex] + "Idle",
		GameEngineRenderingEvent(PlayerName_[PlayerIndex] + "_Idle.FBX", 0.035f, true));

	PlayerIdleRenderer_->CreateFBXAnimation(PlayerName_[_Index] + "Idle2",
		GameEngineRenderingEvent(PlayerName_[PlayerIndex] + "_Idle2.FBX", 0.035f, true));

	PlayerIdleRenderer_->ChangeAnimation(PlayerName_[PlayerIndex] + "Idle");

	PlayerIdleRenderer_->GetTransform().SetLocalPosition({ 0,-70.f,-100.f });
	PlayerIdleRenderer_->GetTransform().SetLocalScale({ 100.f,100.f,100.f });
	PlayerIdleRenderer_->GetTransform().SetLocalRotation({ 80,-140 });
	PlayerIdleRenderer_->GetTransform().SetParentTransform(NewParent->GetTransform());

	PixelData& IdleRender = PlayerIdleRenderer_->GetPixelDatas(0);
	IdleRender.AlphaFlag = 1;
	IdleRender.AlphaColor.a = 1.0f;

	if (_Index == 0)
	{
		IdleRender.AlphaColor.r = 1.0f;
		IdleRender.AlphaColor.g = 0.0f;
		IdleRender.AlphaColor.b = 0.0f;
	}
	else if (_Index == 1)
	{
		IdleRender.AlphaColor.r = 0.0f;
		IdleRender.AlphaColor.g = 0.0f;
		IdleRender.AlphaColor.b = 1.0f;
	}

	NewIcon.PlayerMesh = PlayerIdleRenderer_;
	ResistDebug(std::to_string(_Index), PlayerIdleRenderer_->GetTransform());

	//PlayerIdleRenderer_->GetTransform().SetLocalPosition(PlayerPos[i]);

	NewIcon.Off();

	Icons_.push_back(NewIcon);
}

void UIActor::UpdatePlayerIcon(float _DeltaTime)
{
	PlayerCount_ = GlobalGameData::GetPlayerCount();
	//버그 방지용
	if (PlayerCount_ >= 5)
	{
		PlayerCount_ = 4;
	}
	if (PlayerCount_ <= -1)
	{
		PlayerCount_ = 0;
	}
	for (int i = 0; i < Icons_.size(); i++)
	{
		Icons_[i].Off();
	}

	//위치 정보 Update
	std::vector<float4> IconPos;
	float4 DefaultPos = Icons_[0].Parent->GetTransform().GetWorldPosition();
	DefaultPos.x = 0;
	switch (PlayerCount_)
	{
	case 1:
	{
		float4 Player0 = DefaultPos;
		IconPos.push_back(Player0);
		break;
	}

	case 2:
	{
		float4 Player0 = DefaultPos;
		Player0.x -= 140.f;
		float4 Player1 = DefaultPos;
		Player1.x += 140.f;
		IconPos.push_back(Player0);
		IconPos.push_back(Player1);
		break;
	}
	case 3:
	{
		float4 Player0 = DefaultPos;
		Player0.x -= 230.f;
		float4 Player1 = DefaultPos;
		float4 Player2 = DefaultPos;
		Player2.x += 230.f;
		IconPos.push_back(Player0);
		IconPos.push_back(Player1);
		IconPos.push_back(Player2);
		break;
	}
	case 4:
	{
		float4 Player0 = DefaultPos;
		Player0.x -= 360.f;
		float4 Player1 = DefaultPos;
		Player1.x -= 120.f;
		float4 Player2 = DefaultPos;
		Player2.x += 120.f;
		float4 Player3 = DefaultPos;
		Player3.x += 360.f;
		IconPos.push_back(Player0);
		IconPos.push_back(Player1);
		IconPos.push_back(Player2);
		IconPos.push_back(Player3);
		break;
	}
	default:
		break;
	}
	for (int i = 0; i < IconPos.size(); i++)
	{
		Icons_[i].Parent->GetTransform().SetWorldPosition(IconPos[i]);
	}
	for (int i = 0; i < PlayerCount_; i++)
	{
		Icons_[i].On();
	}
}

std::shared_ptr<OverCookedUIRenderer> UIActor::CreateUIRenderer(std::string_view _TextrueName)
{
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateComponent<OverCookedUIRenderer>(_TextrueName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->ScaleToTexture();
	return NewRenderer;
}

std::shared_ptr<OverCookedUIRenderer> UIActor::CreateUIRenderer(std::string_view _TextrueName, std::string_view _RendererName)
{
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateComponent<OverCookedUIRenderer>(_RendererName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->ScaleToTexture();
	return NewRenderer;
}

std::shared_ptr<OverCookedUIRenderer> UIActor::CreateUIRenderer(std::string_view _TextrueName, float _ScaleRatio)
{
	std::shared_ptr<OverCookedUIRenderer> NewRenderer = CreateComponent<OverCookedUIRenderer>(_TextrueName.data());
	NewRenderer->SetTexture(_TextrueName.data());
	NewRenderer->SetScaleRatio(_ScaleRatio);
	NewRenderer->ScaleToTexture();
	return NewRenderer;
}

void UIActor::InitTransitionRenderer()
{
	if (BlackRenderer_ == nullptr)
	{
		BlackRenderer_ = CreateUIRenderer("Black.png");
		BlackRenderer_->ChangeCamera(CAMERAORDER::AboveUICAMERA);
		BlackRenderer_->Off();
	}

	TransitionIcon_ = CreateComponent<OverCookedUIRenderer>();
	TransitionIcon_->SetTexture("UI_Transitions_02.png");
	TransitionIcon_->ScaleToTexture();
	TransitionIcon_->ChangeCamera(CAMERAORDER::AboveUICAMERA);
	TransitionIcon_->Off();
}

void UIActor::PlayerIcon::Off()
{
	Parent->Off();
	Hat->Off();
	NameBox->Off();
	CountFont->Off();
	NameFont->Off();
	PlayerMesh->Off();
}

void UIActor::PlayerIcon::On()
{
	Parent->On();
	Hat->On();
	NameBox->On();
	CountFont->On();
	NameFont->On();
	PlayerMesh->On();
}