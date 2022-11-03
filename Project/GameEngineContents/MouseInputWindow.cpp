#include "PreCompile.h"
#include "MouseInputWindow.h"
#include "GlobalMouseInput.h"

MouseInputWindow::MouseInputWindow()
	: Input_(nullptr)
	, InputActor_(nullptr)
	, IsChanging_(false)
{
}

MouseInputWindow::~MouseInputWindow()
{
}

void MouseInputWindow::SetMouseInput(GlobalMouseInput* _Input)
{
	Input_ = _Input;
	//GEngine::GetCurrentLevel()->Create
}

void MouseInputWindow::Initialize(GameEngineLevel* _Level)
{
}

void MouseInputWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == Input_)
	{
		return;
	}

	InputActor_ = Input_->GetNearActor();
	if (nullptr == InputActor_)
	{
		return;
	}


	ImGui::Text(InputActor_->GetName().data());
	if (true == ImGui::Button("Change Value"))
	{
		IsChanging_ = !IsChanging_;
	}

	if (true == IsChanging_)
	{
		{
			ImGui::InputFloat3("Position", Pos_);
		}
		{
			ImGui::InputFloat3("Rotation", Rot_);
		}
		{
			ImGui::InputFloat3("Scale", Scale_);
		}

		InputActor_->GetTransform().SetWorldPosition({ Pos_[0], Pos_[1] ,Pos_[2] });
		InputActor_->GetTransform().SetWorldRotation({ Rot_[0], Rot_[1] ,Rot_[2] });
		InputActor_->GetTransform().SetWorldScale({ Scale_[0], Scale_[1] ,Scale_[2] });
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			Pos_[i] = InputActor_->GetTransform().GetWorldPosition().Arr1D[i];
			Rot_[i] = InputActor_->GetTransform().GetWorldRotation().Arr1D[i];
			Scale_[i] = InputActor_->GetTransform().GetWorldScale().Arr1D[i];
		}

		ImGui::Text(("Position " + InputActor_->GetTransform().GetWorldPosition().ToString()).c_str());
		ImGui::Text(("Rotation " + InputActor_->GetTransform().GetWorldRotation().ToString()).c_str());
		ImGui::Text(("Scale " + InputActor_->GetTransform().GetWorldScale().ToString()).c_str());
	}
}
