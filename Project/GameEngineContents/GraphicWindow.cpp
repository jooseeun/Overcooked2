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

ImVec4 GraphicWindow::OverlayColor_ = { 0.586f, 0.617f, 0.672f, 1.0f };

bool GraphicWindow::OverlayOnOff_ = true;
bool GraphicWindow::VignetteOnOff_ = true;
bool GraphicWindow::BloomOnOff_ = true;

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
