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
	{
		Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer_->GetTransform().SetWorldScale({ 800, 800, 1 });
		Renderer_->SetMaterial("Swirl");
		Renderer_->SetMesh("FullRect");
		Renderer_->SetTexture("Icy_Water.png");
		Renderer_->SetRenderingOrder(999);
		Renderer_->Off();
	}

	{
		Renderer2_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer2_->GetTransform().SetWorldScale({ 800, 800, 1 });
		Renderer2_->SetMaterial("JBMWater");
		Renderer2_->SetMesh("FullRect");
		Renderer2_->SetTexture("water2.png");
		Renderer2_->SetRenderingOrder(999);
		Renderer2_->Off();
	}

	{
		Renderer3_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer3_->GetTransform().SetWorldScale({ 800, 800, 1 });
		Renderer3_->SetMaterial("JBMWater");
		Renderer3_->SetMesh("FullRect");
		Renderer3_->SetTexture("water3.png");
		Renderer3_->SetRenderingOrder(999);
		Renderer3_->Off();
	}
}

void WaterTest::Update(float _Delta)
{

	//Renderer_->GetPixelData().Time = _Delta;
	if (GameEngineInput::GetInst()->IsDownKey("Test1"))
	{
		if (Renderer_->IsUpdate())
		{
			Renderer_->Off();
		}
		else
		{
			Renderer_->On();
		}
	}

	if (GameEngineInput::GetInst()->IsDownKey("Test2"))
	{
		if (Renderer2_->IsUpdate())
		{
			Renderer2_->Off();
		}
		else
		{
			Renderer2_->On();
		}
	}

	if (GameEngineInput::GetInst()->IsDownKey("Test3"))
	{
		if (Renderer3_->IsUpdate())
		{
			Renderer3_->Off();
		}
		else
		{
			Renderer3_->On();
		}
	}

	Renderer3_->RenderOptionInst.UV.y -= _Delta * 0.01f;
	Renderer3_->RenderOptionInst.Random += _Delta;

	Renderer2_->RenderOptionInst.UV.y -= _Delta * 0.01f;
	Renderer2_->RenderOptionInst.Random += _Delta;

	Renderer_->RenderOptionInst.Random += _Delta;
}
