#include "PreCompile.h"
#include "UIDebugGUI.h"

#include <GameEngineCore/GameEngineCamera.h>

std::map<std::string, float> UIDebugGUI::DebugValue_float_;
std::map<std::string, int> UIDebugGUI::DebugValue_int_;
std::map<std::string, float4> UIDebugGUI::DebugValue_float4_;
std::map<std::string, std::string> UIDebugGUI::DebugValue_string_;
std::map<std::string, float*> UIDebugGUI::MutableValue_float_;
std::map<std::string, int*> UIDebugGUI::MutableValue_int_;
std::map<std::string, float4*> UIDebugGUI::MutableValue_float4_;
std::map<std::string, GameEngineTransform*> UIDebugGUI::Transform_;
std::map<std::string, std::function<void()>> UIDebugGUI::Function_;

std::shared_ptr<UIDebugGUI> UIDebugGUI::Main_ = nullptr;

UIDebugGUI::UIDebugGUI()
{
}

UIDebugGUI::~UIDebugGUI()
{
}

void UIDebugGUI::Initialize(GameEngineLevel* _Level)
{
}

void UIDebugGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	//DebugValue_int
	if (DebugValue_int_.empty() == false)
	{
		if (ImGui::TreeNodeEx("DebugValue int", 0) == true)
		{
			for (auto i : DebugValue_int_)
			{
				std::string Text = i.first + " : " + std::to_string((i.second));
				ImGui::Text(Text.c_str());
			}
			//������Ʈ�� ���ؼ�
			DebugValue_int_.clear();
			ImGui::TreePop();
		}
	}

	//DebugValue_float
	if (DebugValue_float_.empty() == false)
	{
		if (ImGui::TreeNodeEx("DebugValue Float", 0) == true)
		{
			for (auto i : DebugValue_float_)
			{
				std::string Text = i.first + " : " + std::to_string((i.second));
				ImGui::Text(Text.c_str());
			}
			//������Ʈ�� ���ؼ�
			DebugValue_float_.clear();
			ImGui::TreePop();
		}
	}

	//DebugValue_string
	if (DebugValue_string_.empty() == false)
	{
		if (ImGui::TreeNodeEx("DebugValue String", 0) == true)
		{
			for (auto i : DebugValue_string_)
			{
				std::string Text = i.first + " : " + (i.second);
				ImGui::Text(Text.c_str());
			}
			DebugValue_string_.clear();
			ImGui::TreePop();
		}
	}

	//DebugValue_float
	if (DebugValue_float4_.empty() == false)
	{
		if (ImGui::TreeNodeEx("DebugValue Float4", 0) == true)
		{
			for (auto i : DebugValue_float4_)
			{
				std::string Text = i.first + "\nX : " + std::to_string((i.second.x)) + "\nY : " + std::to_string((i.second.y)) + "\nZ : " + std::to_string((i.second.z));
				ImGui::Text(Text.c_str());
			}
			//������Ʈ�� ���ؼ�
			DebugValue_float4_.clear();
			ImGui::TreePop();
		}
	}

	//MutableValue_float
	if (MutableValue_float_.empty() == false)
	{
		if (ImGui::TreeNodeEx("MutableValue_float_", 0) == true)
		{
			for (auto i : MutableValue_float_)
			{
				ImGui::InputFloat(i.first.c_str(), i.second);
			}
			ImGui::TreePop();
		}
	}

	//MutableValue_int
	if (MutableValue_int_.empty() == false)
	{
		if (ImGui::TreeNodeEx("MutableValue_Int_", 0) == true)
		{
			for (auto i : MutableValue_int_)
			{
				ImGui::InputInt(i.first.c_str(), i.second);
			}
			ImGui::TreePop();
		}
	}

	//MutableValue_float4
	if (MutableValue_float4_.empty() == false)
	{
		if (ImGui::TreeNodeEx("MutableValue_float4_", 0) == true)
		{
			for (auto i : MutableValue_float4_)
			{
				ImGui::InputFloat4(i.first.c_str(), i.second->Arr1D);
			}
			ImGui::TreePop();
		}
	}

	//Transform
	if (Transform_.empty() == false)
	{
		if (ImGui::TreeNodeEx("Transform", 0) == true)
		{
			for (auto i : Transform_)
			{
				if (ImGui::TreeNodeEx(i.first.c_str(), 0) == true)
				{
					//���� ������
					float4 LocalPos = i.second->GetLocalPosition();
					ImGui::InputFloat4("LocalPos", LocalPos.Arr1D);
					i.second->SetLocalPosition(LocalPos);
					//���� ������
					float4 LocalScale = i.second->GetLocalScale();
					ImGui::InputFloat4("LocalScale", LocalScale.Arr1D);
					i.second->SetLocalScale(LocalScale);
					//���� �����̼�
					float4 LocalRot = i.second->GetLocalRotation();
					ImGui::InputFloat4("LocalRot", LocalRot.Arr1D);
					i.second->SetLocalRotation(LocalRot);

					//���� ������
					float4 WorldPos = i.second->GetWorldPosition();
					ImGui::InputFloat4("WorldPos", WorldPos.Arr1D);
					i.second->SetWorldPosition(WorldPos);
					//���� ������
					float4 WorldScale = i.second->GetWorldScale();
					ImGui::InputFloat4("WorldScale", WorldScale.Arr1D);
					i.second->SetWorldScale(WorldScale);
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}

	//Function
	if (Function_.empty() == false)
	{
		if (ImGui::TreeNodeEx("Function", 0) == true)
		{
			for (auto i : Function_)
			{
				if (ImGui::Button(i.first.c_str()) == true)
				{
					i.second();
				}
			}
			ImGui::TreePop();
		}
	}
}