#include "PreCompile.h"
#include "OverCookedUIRenderer.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineFolderTexture.h>

#include "UIDebugGUI.h"

OverCookedUIRenderer::OverCookedUIRenderer()
	: CurAni(nullptr)
	, CurTex(nullptr)
	, PivotMode(PIVOTMODE::CUSTOM)
	, ScaleMode(SCALEMODE::CUSTOM)
	, ScaleRatio(1.0f)
{
}

OverCookedUIRenderer::~OverCookedUIRenderer()
{
}

void OverCookedUIRenderer::SetTextureRendererSetting()
{
	SetPipeLine("UI");

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
	AtlasDataInst.PivotPos = float4::ZERO;

	GetShaderResources().SetConstantBufferLink("AtlasData", AtlasDataInst);
	GetShaderResources().SetConstantBufferLink("PixelData", PixelDataInst);
}

void OverCookedUIRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	PushRendererToUICamera();

	SetTextureRendererSetting();
}

void OverCookedUIRenderer::SetSamplingModePoint()
{
	GetShaderResources().SetSampler("Smp", "EngineSamplerPoint");
}

void OverCookedUIRenderer::SetSamplingModeLiner()
{
	GetShaderResources().SetSampler("Smp", "EngineSamplerLinear");
}

void OverCookedUIRenderer::SetPivot()
{
	SetPivot(PivotMode);
}

void OverCookedUIRenderer::SetPivot(PIVOTMODE _Mode)
{
	switch (_Mode)
	{
	case PIVOTMODE::CENTER:
		AtlasDataInst.PivotPos = float4::ZERO;
		break;
	case PIVOTMODE::BOT:
		AtlasDataInst.PivotPos = float4(0.0f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::TOP:
		AtlasDataInst.PivotPos = float4(0.0f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFT:
		AtlasDataInst.PivotPos = float4(0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHT:
		AtlasDataInst.PivotPos = float4(-0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTTOP:
		AtlasDataInst.PivotPos = float4(0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTTOP:
		AtlasDataInst.PivotPos = float4(-0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTBOT:
		AtlasDataInst.PivotPos = float4(0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTBOT:
		AtlasDataInst.PivotPos = float4(-0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::CUSTOM:
		break;
	default:
		break;
	}

	PivotMode = _Mode;
}

void OverCookedUIRenderer::SetPivotToVector(const float4& _Value)
{
	GetTransform().SetLocalPosition(_Value);
}

void OverCookedUIRenderer::ResistDebug()
{
	UIDebugGUI::Main_->AddTransform(GetNameCopy(), &GetTransform());
}

void OverCookedUIRenderer::SetTexture(GameEngineTexture* _Texture)
{
	if (nullptr == _Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
		return;
	}

	CurTex = _Texture;
	GetShaderResources().SetTexture("Tex", _Texture);
}

void OverCookedUIRenderer::SetTexture(const std::string& _Name)
{
	CurTex = GetShaderResources().SetTexture("Tex", _Name);
}

void OverCookedUIRenderer::SetFrame(UINT _Index)
{
	AtlasDataInst.FrameData = CurTex->GetFrameData(_Index);
}

GameEngineTexture* OverCookedUIRenderer::GetCurTexture()
{
	return CurTex;
}

void OverCookedUIRenderer::SetTexture(const std::string& _Name, UINT _Index)
{
	SetTexture(_Name);
	SetFrame(_Index);
}

void OverCookedUIRenderer::SetTexture(GameEngineTexture* _Texture, UINT _Index)
{
	if (nullptr == _Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
		return;
	}

	SetTexture(_Texture);
	SetFrame(_Index);
}

void OverCookedUIRenderer::SetFolderTextureToIndex(const std::string& _Text, UINT _Index)
{
	GameEngineFolderTexture* FolderTexture = GameEngineFolderTexture::Find(_Text);

	SetTexture(FolderTexture->GetTexture(_Index));

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
}

void OverCookedUIRenderer::Update(float _Delta)
{
}

void OverCookedUIRenderer::ScaleToCutTexture(int _Index)
{
	float4 Scale = CurTex->GetCutScale(_Index);

	// 이거는 봐야합니다.
	if (0 > GetTransform().GetLocalScale().x)
	{
		Scale.x = -Scale.x;
	}

	if (0 > GetTransform().GetLocalScale().y)
	{
		Scale.y = -Scale.y;
	}

	GetTransform().SetLocalScale(Scale * ScaleRatio);
}

void OverCookedUIRenderer::ScaleToTexture()
{
	float4 Scale = CurTex->GetScale();

	// 이거는 봐야합니다.
	if (0 > GetTransform().GetLocalScale().x)
	{
		Scale.x = -Scale.x;
	}

	if (0 > GetTransform().GetLocalScale().y)
	{
		Scale.y = -Scale.y;
	}

	GetTransform().SetLocalScale(Scale * ScaleRatio);
}