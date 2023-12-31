#include "PreCompile.h"
#include "GameEngineStatusWindow.h"
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GEngine.h>
#include "ServerTestLevel.h"
#include "GamePacket.h"
#include "Player.h"

bool GameEngineStatusWindow::IsHost = false;
std::map<std::string, std::shared_ptr<GameEngineRenderTarget>> GameEngineStatusWindow::DebugRenderTarget;

void GameEngineImageShotWindow::RenderTextureSetting(ImTextureID _RenderTexture, ImVec2 _Size)
{
	RenderTexture = _RenderTexture;
	Size = _Size;
}

void GameEngineImageShotWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::ImageButton(RenderTexture, { Size.x, Size.y }))
	{
		Off();
	}
}

GameEngineStatusWindow::GameEngineStatusWindow()
{
}

GameEngineStatusWindow::~GameEngineStatusWindow()
{
}

void GameEngineStatusWindow::Initialize(class GameEngineLevel* _Level)
{
}

void GameEngineStatusWindow::AddDebugRenderTarget(const std::string& _DebugName, std::shared_ptr<GameEngineRenderTarget> _RenderTarget)
{
	if (DebugRenderTarget.end() != DebugRenderTarget.find(_DebugName))
	{
		MsgBoxAssert("이미 존재하는 디버그 랜더타겟입니다.");
	}

	DebugRenderTarget.insert(std::make_pair(_DebugName, _RenderTarget));
}

void GameEngineStatusWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	int FPS = static_cast<int>(1.0f / _DeltaTime);
	std::string Name = "FPS : " + std::to_string(GameEngineTime::GetFPS());
	ImGui::Text(Name.c_str());

	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}

	if (true == ImGui::Button("CollisionWireFrame"))
	{
		GameEngineDebug::SetWireFrame();
	}
	ImGui::SameLine();

	if (true == ImGui::Button("CollisionFillSolid"))
	{
		GameEngineDebug::SetFillSolid();
	}
	ImGui::NewLine();

	CameraGUI(_Level, _DeltaTime);
	ImGui::Text("Level Select");
	for (std::pair<std::string, GameEngineLevel*> Pair : GameEngineCore::AllLevels)
	{
		if (true == ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}

		ImGui::SameLine();
	}

	ImGui::NewLine();
	std::string AllRenderTarget = "AllRenderTarget";
	ImGui::Text(AllRenderTarget.c_str());

	for (std::pair<std::string, std::shared_ptr<GameEngineRenderTarget>> RenderTargetPair : DebugRenderTarget)
	{
		// ImGui::Text(RenderTarget.first.c_str());

		if (true == ImGui::TreeNodeEx(RenderTargetPair.first.c_str(), 0))
		{
			std::shared_ptr<GameEngineRenderTarget> RenderTarget = RenderTargetPair.second;

			for (ID3D11ShaderResourceView* _View : RenderTarget->ShaderResourceViews)
			{
				float4 Scale = GameEngineWindow::GetScale() * 0.2f;

				if (true == ImGui::ImageButton(static_cast<ImTextureID>(_View), { Scale.x, Scale.y }))
				{
					std::shared_ptr<GameEngineImageShotWindow> NewWindow = GameEngineGUI::CreateGUIWindow<GameEngineImageShotWindow>("ImageShot", nullptr);
					NewWindow->RenderTextureSetting(static_cast<ImTextureID>(_View), { GameEngineWindow::GetScale().x ,GameEngineWindow::GetScale().y });
				}
			}

			ImGui::TreePop();
		}
	}

	// 서버 테스트용
	{
		ImGui::Text("Server Status");
		ImGui::SameLine();
		ImGui::Checkbox(GameEngineString::AnsiToUTF8Return("호스트").c_str(), &IsHost);
		ImGui::SameLine();
		if (true == ImGui::Button("CheckSend"))
		{
			std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();

			Packet->ObjectID = 10;
			Packet->Scale = { 1.0f, 122.f, 122.f };
			Packet->Pos = { 999.0f, 999.f, 999.f };
			Packet->Rot = { 45.0f, 45.f, 45.f };
			Packet->Animation = "Idle";

			ServerTestLevel::Net->SendPacket(Packet);
		}
	}
	// 플레이어 위치 테스트
	{
		ImGui::Text("Player Position");
		if (Player::GetMyPlayer() != nullptr)
		{
			std::string Name = "X : " + std::to_string(Player::GetMyPlayer()->GetTransform().GetWorldPosition().x);
			ImGui::Text(Name.c_str());
			ImGui::SameLine();
			std::string Name2 = "Y : " + std::to_string(Player::GetMyPlayer()->GetTransform().GetWorldPosition().y);
			ImGui::Text(Name2.c_str());
			ImGui::SameLine();
			std::string Name3 = "Z : " + std::to_string(Player::GetMyPlayer()->GetTransform().GetWorldPosition().z);
			ImGui::Text(Name3.c_str());
			ImGui::SameLine();
		}


	}
}

void GameEngineStatusWindow::CameraGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (!ImGui::CollapsingHeader("CameraSetting"))
		return;

	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		GEngine::GetCurrentLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::Text("Pos(x,y,z) : (%.2f, %.2f, %.2f)", GEngine::GetCurrentLevel()->GetMainCameraActorTransform().GetWorldPosition().x,
		GEngine::GetCurrentLevel()->GetMainCameraActorTransform().GetWorldPosition().y,
		GEngine::GetCurrentLevel()->GetMainCameraActorTransform().GetWorldPosition().z);

	float4 Pos = GEngine::GetCurrentLevel()->GetMainCameraActorTransform().GetWorldPosition();
	ImGui::DragFloat("Inpot Pos.x", &Pos.x);

	ImGui::DragFloat("Inpot Pos.y", &Pos.y);
	ImGui::DragFloat("Inpot Pos.z", &Pos.z/*, -FLT_MAX / 2.0f, FLT_MAX / 2.0f*/);
	//IM_ASSERT(*(const float*)p_min >= -FLT_MAX / 2.0f && *(const float*)p_max <= FLT_MAX / 2.0f);

	GEngine::GetCurrentLevel()->GetMainCameraActorTransform().SetWorldPosition(Pos);
}