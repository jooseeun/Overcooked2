#include "PreCompile.h"
#include "MouseInputWindow.h"
#include "GlobalMouseInput.h"

std::shared_ptr<MouseInputWindow> MouseInputWindow::Main_ = nullptr;

MouseInputWindow::MouseInputWindow()
	: Input_(nullptr)
	, InputTransform_(nullptr)
	, IsChanging_(false)
	, Pos_()
	, Rot_()
	, Scale_()
{
}

MouseInputWindow::~MouseInputWindow()
{
}

void MouseInputWindow::SetForceInput(GameEngineTransform* _Transform)
{
	Input_->SetNearTransform(_Transform);
	InputTransform_ = _Transform;
}

void MouseInputWindow::SetMouseInput(GlobalMouseInput* _Input)
{
	if (true == IsChanging_)
	{
		return;
	}

	Input_ = _Input;
	InputTransform_ = Input_->GetNearTransform();
}

void MouseInputWindow::Initialize(GameEngineLevel* _Level)
{
}

void MouseInputWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr != Input_)
	{
		return;
	}

	if (true == ImGui::Button("UI"))
	{
		Input_->SetIsUI(true);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Obj"))
	{
		Input_->SetIsUI(false);
	}

	InputTransform_ = Input_->GetNearTransform();
	if (nullptr == InputTransform_)
	{
		return;
	}

	if (true == ImGui::Button("Change Value"))
	{
		IsChanging_ = !IsChanging_;
	}

	if (true == IsChanging_)
	{
		{
			ImGui::DragFloat3("Position", Pos_);
		}
		{
			ImGui::DragFloat3("Rotation", Rot_);
		}
		{
			ImGui::DragFloat3("Scale", Scale_);
		}

		InputTransform_->SetWorldPosition({ Pos_[0], Pos_[1] ,Pos_[2] });
		InputTransform_->SetWorldRotation({ Rot_[0], Rot_[1] ,Rot_[2] });
		InputTransform_->SetWorldScale({ Scale_[0], Scale_[1] ,Scale_[2] });
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			Pos_[i] = InputTransform_->GetWorldPosition().Arr1D[i];
			Rot_[i] = InputTransform_->GetWorldRotation().Arr1D[i];
			Scale_[i] = InputTransform_->GetWorldScale().Arr1D[i];
		}

		ImGui::Text(("Position " + InputTransform_->GetWorldPosition().ToString()).c_str());
		ImGui::Text(("Rotation " + InputTransform_->GetWorldRotation().ToString()).c_str());
		ImGui::Text(("Scale " + InputTransform_->GetWorldScale().ToString()).c_str());
	}


	ImGui::Text(("x " + std::to_string(MouseRot_.ix())).c_str());
	ImGui::Text(("y " + std::to_string(MouseRot_.iy())).c_str());
	ImGui::Text(("z " + std::to_string(MouseRot_.iz())).c_str());
}
