#include "PreCompile.h"
#include "GraphicWindow.h"
#include "GamePlayLevel.h"

#include<GameEngineCore/GlobalOverlay.h>
#include<GameEngineCore/GlobalVignette.h>
#include<GameEngineCore/GlobalBloom.h>

std::shared_ptr<GraphicWindow> GraphicWindow::Main_ = nullptr;

std::shared_ptr<GlobalOverlay>  GraphicWindow::GlobalOverlay_ = nullptr;
std::shared_ptr<GlobalVignette> GraphicWindow::GlobalVignette_ = nullptr;
std::shared_ptr<GlobalBloom>	GraphicWindow::GlobalBloom_ = nullptr;

float GraphicWindow::BloomFilter1_[3] = { 0.2126f, 0.7152f, 0.0722f };
float GraphicWindow::BloomFilter2_[3] = { 0.0f, 0.0f, 0.0f };
float GraphicWindow::BloomFilter3_[3] = { 0.0f, 0.0f, 0.0f };
float GraphicWindow::BloomFilter4_[3] = { 0.0f, 0.0f, 0.0f };
float GraphicWindow::BloomFilter5_[3] = { 0.0f, 0.0f, 0.0f };
float GraphicWindow::BloomValue_ = 10;
float GraphicWindow::BrightMin_ = 0.8f;
float GraphicWindow::BrightMax_ = 1.0f;

ImVec4 GraphicWindow::OverlayColor_ = { 0.586f, 0.617f, 0.672f, 1.0f };

bool GraphicWindow::OverlayOnOff_ = true;
bool GraphicWindow::VignetteOnOff_ = true;
bool GraphicWindow::BloomOnOff_ = false;

GraphicWindow::GraphicWindow() 
{
}

GraphicWindow::~GraphicWindow() 
{
}

void GraphicWindow::Initialize(GameEngineLevel* _Level)
{
	//CurrentLevel_ = dynamic_cast<GamePlayLevel*>(_Level);
}

void GraphicWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	
	ConvertToImvec(GlobalOverlay_->GetOverlayColorData().OverlayColor, OverlayColor_);

	ImGuiColorEditFlags misc_flags = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);

	ImGui::Text("Overlay Color");
	ImGui::ColorEdit4("Overlay Color##2f", (float*)&OverlayColor_, ImGuiColorEditFlags_Float | misc_flags);


	ConvertToFloat4(GlobalOverlay_->GetOverlayColorData().OverlayColor, OverlayColor_);

	// 블룸 수치조절
	ImGui::DragFloat3("Bloom Filter1", BloomFilter1_, 0.01f, 0, 1);
	ImGui::DragFloat3("Bloom Filter2", BloomFilter2_, 0.01f, 0, 1);
	ImGui::DragFloat3("Bloom Filter3", BloomFilter3_, 0.01f, 0, 1);
	ImGui::DragFloat3("Bloom Filter4", BloomFilter4_, 0.01f, 0, 1);
	ImGui::DragFloat3("Bloom Filter5", BloomFilter5_, 0.01f, 0, 1);
	ImGui::DragFloat("Bloom Value", &BloomValue_, 2.0f, 0, 50);
	ImGui::DragFloat("Bloom Min", &BrightMin_, 0.01f, 0, 1);
	ImGui::DragFloat("Bloom Max", &BrightMax_, 0.01f, 0, 1);
	BloomSetting();

	ImGui::Checkbox("OverlayFlag", &OverlayOnOff_);
	ImGui::Checkbox("VignetteFlag", &VignetteOnOff_);
	ImGui::Checkbox("BloomFlag", &BloomOnOff_);

	if (OverlayOnOff_ == true)
	{
		GlobalOverlay_->On();
	}

	else
	{
		GlobalOverlay_->Off();
	}

	if (VignetteOnOff_ == true)
	{
		GlobalVignette_->On();
	}

	else
	{
		GlobalVignette_->Off();
	}

	if (BloomOnOff_ == true)
	{
		GlobalBloom_->On();
	}
	else
	{
		GlobalBloom_->Off();
	}
}

void GraphicWindow::BloomSetting()
{
	BloomOption* Tmp = &GlobalBloom_->GetOption();
	Tmp->BloomFilter[0] = float4(BloomFilter1_[0], BloomFilter1_[1], BloomFilter1_[2]);
	Tmp->BloomFilter[1] = float4(BloomFilter2_[0], BloomFilter2_[1], BloomFilter2_[2]);
	Tmp->BloomFilter[2] = float4(BloomFilter3_[0], BloomFilter3_[1], BloomFilter3_[2]);
	Tmp->BloomFilter[3] = float4(BloomFilter4_[0], BloomFilter4_[1], BloomFilter4_[2]);
	Tmp->BloomFilter[4] = float4(BloomFilter5_[0], BloomFilter5_[1], BloomFilter5_[2]);
	Tmp->BloomValue = BloomValue_;
	Tmp->BrightMin = BrightMin_;
	Tmp->BrightMax = BrightMax_;
}

