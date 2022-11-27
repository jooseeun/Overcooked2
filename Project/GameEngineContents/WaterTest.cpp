#include "PreCompile.h"
#include "WaterTest.h"

WaterTest::WaterTest() 
{
}

WaterTest::~WaterTest() 
{
}

void WaterTest::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetWorldScale({ 800, 800, 1 });
	Renderer_->SetMaterial("JBMWater");
	Renderer_->SetMesh("FullRect");
	Renderer_->SetTexture("water.png");
	Renderer_->SetRenderingOrder(999);
}

void WaterTest::Update(float _Delta)
{
	Renderer_->RenderOptionInst.UV.x += _Delta * 0.1f;
}
