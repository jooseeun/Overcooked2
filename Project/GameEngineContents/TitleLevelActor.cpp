#include "Precompile.h"
#include "TitleLevelActor.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
#include "GameEngineStatusWindow.h"
#include "GlobalGameData.h"

#include "OverCookedUIRenderer.h"

TitleLevelActor::TitleLevelActor()
{
}

TitleLevelActor::~TitleLevelActor()
{
}

void TitleLevelActor::UIStart()
{
	CreateButton("스타트", { -500,300,0 }, std::bind(&TitleLevelActor::ChangeLevel, this));
	CreateButton("호스트", { -250,300,0 }, std::bind([&](void)
		{
			GameEngineStatusWindow::IsHost = true;
			ServerInitManager::StartInit();
			AllButtons_[0].Enable();
			AllButtons_[1].Disable();
			AllButtons_[2].Disable();
		}));
	CreateButton("서버접속", { 0,300,0 }, std::bind([&](void)
		{
			GameEngineStatusWindow::IsHost = false;
			ServerInitManager::StartInit();
			AllButtons_[0].Disable();
			AllButtons_[1].Disable();
			AllButtons_[2].Disable();
		}));
	CreateButton("설정", { 250,300,0 }, nullptr);
	CreateButton("종료", { 500,300,0 }, nullptr);
	AllButtons_[0].Disable();

	//플레이어
	std::vector<std::string> PlayerName_;
	PlayerName_.resize(6);
	PlayerName_[0] = "AlienGreen";
	PlayerName_[1] = "Buck";
	PlayerName_[2] = "Crocodile";
	PlayerName_[3] = "Dora";
	PlayerName_[4] = "Eagle";
	PlayerName_[5] = "Panda";

	std::vector<float4> PlayerPos;
	PlayerPos.resize(6);
	PlayerPos[0] = { 210,0,0 };
	PlayerPos[1] = { 150,0,0 };
	//PlayerPos[0] = { 210,0,0 };
	//PlayerPos[0] = { 210,0,0 };

	float4 PlayerRot = { 90,-15 };
	float4 PlayerScale = { 40.f,40.f,40.f };

	for (int i = 0; i < 6; i++)
	{
		std::weak_ptr< GameEngineFBXAnimationRenderer> PlayerIdleRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
		PlayerIdleRenderer_.lock()->SetFBXMesh(PlayerName_[i] + "_Idle.FBX", "TextureAnimation");

		PlayerIdleRenderer_.lock()->CreateFBXAnimation(PlayerName_[i] + "Idle",
			GameEngineRenderingEvent(PlayerName_[i] + "_Idle.FBX", 0.035f, true));

		PlayerIdleRenderer_.lock()->CreateFBXAnimation(PlayerName_[i] + "Idle2",
			GameEngineRenderingEvent(PlayerName_[i] + "_Idle2.FBX", 0.035f, true));

		PlayerIdleRenderer_.lock()->ChangeAnimation(PlayerName_[i] + "Idle");

		PlayerIdleRenderer_.lock()->GetTransform().SetLocalScale(PlayerScale);
		PlayerIdleRenderer_.lock()->GetTransform().SetLocalRotation(PlayerRot);
		PlayerIdleRenderer_.lock()->GetTransform().SetLocalPosition(PlayerPos[i]);

		PlayerIdleRenderer_.lock()->Off();

		PlayerMesh_.push_back(PlayerIdleRenderer_);
	}
	ResistDebug("Transform1", PlayerMesh_[1].lock()->GetTransform());
	ResistDebug("Transform2", PlayerMesh_[2].lock()->GetTransform());
	ResistDebug("Transform3", PlayerMesh_[3].lock()->GetTransform());
}

void TitleLevelActor::UIUpdate(float _DeltaTime)
{
	UpdateInput();

	//Render
	for (int i = 0; i < GlobalGameData::PlayerCount_; i++)
	{
		PlayerMesh_[i].lock()->On();
	}
}

void TitleLevelActor::UpdateInput()
{
	if (ServerInitManager::Net != nullptr)
	{
		if (ServerInitManager::Net->GetIsHost() == true)
		{
			GlobalGameData::PlayerCount_ = ServerInitManager::Server.GetUserSockets().size() + 1;
			std::shared_ptr<UserCountPacket> Packet = std::make_shared<UserCountPacket>();
			Packet->Count = ServerInitManager::Server.GetUserSockets().size() + 1;
			ServerInitManager::Net->SendPacket(Packet);
		}
	}

	if (GameEngineInput::GetInst()->IsDownKey("PlayerRight") == true)
	{
		if (AllButtons_[CurNum_].IsDisabled == false)
		{
			AllButtons_[CurNum_].Enable();
		}
		CurNum_++;
		//Check
		{
			while (true)
			{
				if (CurNum_ >= AllButtons_.size())
				{
					CurNum_ = 0;
				}

				if (AllButtons_[CurNum_].IsDisabled == true)
				{
					CurNum_++;
					continue;
				}

				//해당되는 놈을 만났어
				AllButtons_[CurNum_].Highlight();
				AllButtons_[CurNum_].Parent.lock()->StartPump(1.1f, 9.0f);
				break;
			}
		}
	}
	else if (GameEngineInput::GetInst()->IsDownKey("PlayerLeft") == true)
	{
		if (AllButtons_[CurNum_].IsDisabled == false)
		{
			AllButtons_[CurNum_].Enable();
		}
		CurNum_--;
		//Check
		{
			while (true)
			{
				if (CurNum_ < 0)
				{
					CurNum_ = static_cast<int>(AllButtons_.size()) - 1;
				}

				if (AllButtons_[CurNum_].IsDisabled == true)
				{
					CurNum_--;
					continue;
				}

				//해당되는 놈을 만났어
				AllButtons_[CurNum_].Highlight();
				AllButtons_[CurNum_].Parent.lock()->StartPump(1.1f, 9.0f);
				break;
			}
		}
	}
	else if (GameEngineInput::GetInst()->IsDownKey("PlayerHold") == true)
	{
		for (int i = 0; i < AllButtons_.size(); i++)
		{
			if (AllButtons_[i].IsHighlighted == true)
			{
				if (AllButtons_[i].CallBack != nullptr)
				{
					AllButtons_[i].CallBack();
				}
			}
		}
	}
}

void TitleLevelActor::UIEnd()
{
}

void TitleLevelActor::ChangeLevel()
{
	if (nullptr != ServerInitManager::Net)
	{
		if (ServerInitManager::Net->GetIsHost() == true)
		{
			std::shared_ptr<ChangeLevelPacket> Packet = std::make_shared<ChangeLevelPacket>();
			Packet->LevelName = "SelectStage";
			ServerInitManager::Net->SendPacket(Packet);
		}
		GEngine::ChangeLevel("SelectStage");
	}
}

void TitleLevelActor::CreateButton(std::string_view _Font, const float4& _Pos, std::function<void()> _Function)
{
	MenuButton NewButton;
	NewButton.Parent = CreateUIRenderer("Null.png");
	NewButton.Parent.lock()->GetTransform().SetWorldPosition(_Pos);
	NewButton.Parent.lock()->ResistDebug(std::to_string(AllButtons_.size()));

	float ButtonSize = 0.3f;
	NewButton.Button = CreateUIRenderer("t_ui_main_menu_button_04_d.png", ButtonSize);
	NewButton.Button.lock()->GetTransform().SetParentTransform(NewButton.Parent.lock()->GetTransform());

	NewButton.Button_Disabled = CreateUIRenderer("t_ui_main_menu_button_04_disabled_d.png", ButtonSize);
	NewButton.Button_Disabled.lock()->GetTransform().SetParentTransform(NewButton.Parent.lock()->GetTransform());
	NewButton.Button_Disabled.lock()->Off();

	NewButton.Button_Highlight = CreateUIRenderer("t_ui_main_menu_button_04_highlight_d.png", ButtonSize);
	NewButton.Button_Highlight.lock()->GetTransform().SetParentTransform(NewButton.Parent.lock()->GetTransform());
	NewButton.Button_Highlight.lock()->Off();

	NewButton.Font = CreateComponent<GameEngineFontRenderer>();
	NewButton.Font.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
	NewButton.Font.lock()->SetText(_Font.data(), "Naughty Squirrel");
	NewButton.Font.lock()->SetColor({ 1.0f,1.0f,1.0f,1 });
	NewButton.Font.lock()->SetSize(28.f);
	NewButton.Font.lock()->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	NewButton.Font.lock()->SetAffectTransform(true);
	NewButton.Font.lock()->GetTransform().SetParentTransform(NewButton.Parent.lock()->GetTransform());
	//ResistDebug("ButtonFont", NewButton.Font.lock()->GetTransform());
	NewButton.Font.lock()->GetTransform().SetLocalMove({ 0,22.f,-1 });

	//{
	//	//폰트
	//	std::shared_ptr<GameEngineFontRenderer> NewFont = CreateComponent<GameEngineFontRenderer>();
	//	NewFont->ChangeCamera(CAMERAORDER::UICAMERA);
	//	NewFont->SetText("1-1", "Naughty Squirrel");
	//	NewFont->SetColor({ 0.4f,0.4f,0.4f,1 });
	//	NewFont->SetSize(35.f);
	//	NewFont->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	//	NewFont->SetAffectTransform(true);
	//	NewFont->GetTransform().SetLocalMove({ 0,-58.f,-1 });
	//	NewFont->GetTransform().SetParentTransform(NewParent->GetTransform());
	//	NewSelect.Font = NewFont;
	//}

	NewButton.CallBack = _Function;

	AllButtons_.push_back(NewButton);
}

void TitleLevelActor::MenuButton::Disable()
{
	Button.lock()->Off();
	Button_Highlight.lock()->Off();
	Button_Disabled.lock()->On();
	IsDisabled = true;
	IsHighlighted = false;
}

void TitleLevelActor::MenuButton::Enable()
{
	Button.lock()->On();
	Button_Highlight.lock()->Off();
	Button_Disabled.lock()->Off();
	IsHighlighted = false;
	IsDisabled = false;
}

void TitleLevelActor::MenuButton::Highlight()
{
	Button.lock()->Off();
	Button_Highlight.lock()->On();
	Button_Disabled.lock()->Off();
	IsHighlighted = true;
	IsDisabled = false;
}