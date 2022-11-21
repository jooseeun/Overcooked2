#include "PreCompile.h"
#include "OverCookedUIRenderer.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineBase/GameEngineRandom.h>

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

	//LINEARWRAP
	GetShaderResources().SetSampler("LINEARWRAP", "LINEARCLAMP");
	GetShaderResources().SetConstantBufferLink("AtlasData", AtlasDataInst);
	GetShaderResources().SetConstantBufferLink("PixelData", PixelDataInst);
	GetShaderResources().SetConstantBufferLink("UIData", UIDataInst);
}

void OverCookedUIRenderer::UpdateLeftToRight(float _Percentage)
{
	UIDataInst.UIMode = 3;
	PixelDataInst.Slice = { _Percentage,0.0f };
}

void OverCookedUIRenderer::UpdateLeftTime(float _Percentage)
{
	float Acc = 1.f;
	PixelDataInst.PlusColor = float4(Acc * (1 - _Percentage), Acc * _Percentage, 0, 0);
	PixelDataInst.MulColor = float4(1.0f, 1.0f, 1.0f, 0.5f);
}

void OverCookedUIRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	PushRendererToUICamera();

	SetTextureRendererSetting();

	std::shared_ptr<GameEngineCollision> Collision_ = GetActor()->CreateComponent<GameEngineCollision>();
	Collision_->SetDebugSetting(CollisionType::CT_AABB, { 1, 0, 0, 0.1f });
	Collision_->SetParent(std::dynamic_pointer_cast<GameEngineUpdateObject>(shared_from_this()));

	int a = 0;
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

void OverCookedUIRenderer::ResistDebug(std::string_view _Name)
{
	UIDebugGUI::Main_->AddTransform(_Name.data(), &GetTransform());
}

void OverCookedUIRenderer::SetTexture(std::shared_ptr<GameEngineTexture> _Texture)
{
	if (nullptr == _Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
		return;
	}

	CurTex = _Texture;
	GetShaderResources().SetTexture("Tex", _Texture);
	GetShaderResources().SetTexture("Tex2", _Texture);
}

void OverCookedUIRenderer::SetTexture(const std::string& _Name)
{
	CurTex = GetShaderResources().SetTexture("Tex", _Name);
	GetShaderResources().SetTexture("Tex2", _Name);
}

void OverCookedUIRenderer::SetMaskTexture(const std::string_view _Name)
{
	UIDataInst.UIMode = 1;
	GetShaderResources().SetTexture("Tex2", _Name.data());
}

void OverCookedUIRenderer::SetFrame(UINT _Index)
{
	AtlasDataInst.FrameData = CurTex->GetFrameData(_Index);
}

std::shared_ptr<GameEngineTexture> OverCookedUIRenderer::GetCurTexture()
{
	return CurTex;
}

void OverCookedUIRenderer::SetTexture(const std::string& _Name, UINT _Index)
{
	SetTexture(_Name);
	SetFrame(_Index);
}

void OverCookedUIRenderer::SetTexture(std::shared_ptr<GameEngineTexture> _Texture, UINT _Index)
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
	std::shared_ptr<GameEngineFolderTexture> FolderTexture = GameEngineFolderTexture::Find(_Text);

	SetTexture(FolderTexture->GetTexture(_Index));

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
}

void OverCookedUIRenderer::Update(float _Delta)
{
	if (IsPumping() == true)
	{
		if (Pump_IterTime_ >= 2.f)
		{
			StopPump();
		}
		Pump_IterTime_ += _Delta * PumpingSpeed_;
		float4 CurScale = {};
		if (Pump_IterTime_ < 1.f)
		{
			CurScale = float4::LerpLimit(PrevScale_, PrevScale_ * PumpRatio_, Pump_IterTime_);
		}
		else if (Pump_IterTime_ >= 1.f)
		{
			CurScale = float4::LerpLimit(PrevScale_ * PumpRatio_, PrevScale_, Pump_IterTime_ - 1.f);
		}
		GetTransform().SetLocalScale(CurScale);
	}
	if (IsDown_ == true)
	{
		DownIter_ += _Delta * DownSpeed_;
		UIDataInst.DownDelta.y = DownIter_;
		if (DownIter_ > 1.0f)
		{
			DownIter_ = -1000.f;
		}
	}

	UpdateTransition(_Delta);
}

void OverCookedUIRenderer::UpdateTransition(float _Delta)
{
	if (UIDataInst.UIMode != 2)
	{
		return;
	}
	if (IsFadeOut_ == true) //페이드아웃
	{
		AccTime_ -= _Delta * 23.f;
		if (AccTime_ < 0.25f)
		{
			AccTime_ = 0.25f;
		}

		TransitionRatio_ -= _Delta * AccTime_;
		float4 CurScale = CurTex->GetScale() * TransitionRatio_;
		GetTransform().SetLocalScale(CurScale);
		if (TransitionRatio_ < 0.01f)
		{
			IsFinishFadeOut_ = true;
			//Off();
		}
	}
	else // 페이드 인
	{
		AccTime_ += _Delta;

		float X = AccTime_ * AccTime_ * AccTime_;

		float Speed = pow(10.0f, X) - 1.f;

		TransitionRatio_ = Speed;
		float4 CurScale = CurTex->GetScale() * TransitionRatio_;
		GetTransform().SetLocalScale(CurScale);
		if (TransitionRatio_ > 20.0f)
		{
			IsFinishFadeIn_ = true;
		}
	}
}

void OverCookedUIRenderer::StopPump()
{
	IsPumping_ = false;
	GetTransform().SetLocalScale(PrevScale_);
	Pump_IterTime_ = 0.f;
}

bool OverCookedUIRenderer::IsPumping()
{
	return IsPumping_;
}

void OverCookedUIRenderer::StartDown(float _Speed)
{
	if (IsDown_ == true)
	{
		return;
	}
	DownIter_ = -1000.f;
	IsDown_ = true;
	DownSpeed_ = _Speed;
	DownIter_ = 100000.f;
	UIDataInst.DownDelta = { 1.f,0.f,0.f,0.f };
}

void OverCookedUIRenderer::SetSamplerWrap()
{
	//LINEARWRAP
	GetShaderResources().SetSampler("LINEARWRAP", "LINEARWRAP");
}

void OverCookedUIRenderer::SetSamplerPointClamp()
{
	GetShaderResources().SetSampler("LINEARWRAP", "POINTCLAMP");
}

void OverCookedUIRenderer::StartFadeOut(float _StartRatio)
{
	IsFadeOut_ = true;
	UIDataInst.UIMode = 2;
	TransitionRatio_ = _StartRatio;
	AccTime_ = 18.0f;
	//난수로 랜덤 IconGet
	std::string FileName;
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 100);
	if (RandomValue < 33)
	{
		FileName = "UI_Transitions_02.png";
	}
	else if (RandomValue >= 33 && RandomValue < 66)
	{
		FileName = "UI_Transitions_03.png";
	}
	else
	{
		FileName = "UI_Transitions_04.png";
	}
	SetTexture(FileName);

	float4 CurScale = CurTex->GetScale() * TransitionRatio_;
	GetTransform().SetLocalScale(CurScale);
}

void OverCookedUIRenderer::StartFadeIn()
{
	IsFadeOut_ = false;
	UIDataInst.UIMode = 2;
	TransitionRatio_ = 0.01f;
	AccTime_ = 0.05f;
	//난수로 랜덤 IconGet
	std::string FileName;
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 100);
	if (RandomValue < 33)
	{
		FileName = "UI_Transitions_02.png";
	}
	else if (RandomValue >= 33 && RandomValue < 66)
	{
		FileName = "UI_Transitions_03.png";
	}
	else
	{
		FileName = "UI_Transitions_04.png";
	}
	SetTexture(FileName);

	float4 CurScale = CurTex->GetScale() * TransitionRatio_;
	GetTransform().SetLocalScale(CurScale);
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

void OverCookedUIRenderer::StartPump(float _Ratio, float _Speed)
{
	//이미 펌핑중이면 들어오지 못하게
	if (IsPumping() == true)
	{
		return;
	}
	PrevScale_ = GetTransform().GetLocalScale();
	PumpingSpeed_ = _Speed;
	PumpRatio_ = _Ratio;
	IsPumping_ = true;
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