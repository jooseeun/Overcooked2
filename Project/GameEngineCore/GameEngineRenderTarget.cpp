#include "PreCompile.h"
#include "GameEngineRenderTarget.h"

ID3D11RenderTargetView* GameEngineRenderTarget::PrevRenderTargetViews = nullptr;
ID3D11DepthStencilView* GameEngineRenderTarget::PrevDepthStencilView = nullptr;

GameEngineRenderTarget::GameEngineRenderTarget() 
	: DepthStencilView(nullptr)
	, DepthTexture(nullptr)
{
	MergeUnit = std::make_shared<GameEngineRenderUnit>();

	MergeUnit->SetMesh("FullRect");
	MergeUnit->SetMaterial("TargetMerge");
}

GameEngineRenderTarget::~GameEngineRenderTarget() 
{
	//for (GameEnginePostEffect* Effect : Effects)
	//{
	//	delete Effect;
	//}

	Effects.clear();
}

void GameEngineRenderTarget::GetPrevRenderTarget()
{
	GameEngineDevice::GetContext()->OMGetRenderTargets(1, &PrevRenderTargetViews, &PrevDepthStencilView);
}

void GameEngineRenderTarget::SetPrevRenderTarget()
{
	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &PrevRenderTargetViews, PrevDepthStencilView);
	if (nullptr != PrevRenderTargetViews)
	{
		PrevRenderTargetViews->Release();
	}

	if (nullptr != PrevDepthStencilView)
	{
		PrevDepthStencilView->Release();
	}
}

std::shared_ptr < GameEngineRenderTarget> GameEngineRenderTarget::Create(const std::string& _Name)
{
	return CreateResName(_Name);
}

std::shared_ptr < GameEngineRenderTarget> GameEngineRenderTarget::Create()
{
	return CreateResUnName();
}

std::shared_ptr<GameEngineTexture> GameEngineRenderTarget::GetRenderTargetTexture(size_t _Index)
{
	if (RenderTargets.size() <= _Index)
	{
		MsgBoxAssert("랜더타겟 인덱스를 오버했습니다. 존재하지 않는 랜더타겟을 사용하려고 했습니다.");
		return nullptr;
	}

	return RenderTargets[_Index];
}

void GameEngineRenderTarget::Copy(std::shared_ptr<GameEngineRenderTarget> _Other, int _Index )
{
	Clear();

	MergeUnit->ShaderResources.SetTexture("Tex", _Other->GetRenderTargetTexture(_Index));

	Effect(MergeUnit);
}

void GameEngineRenderTarget::Merge(std::shared_ptr<GameEngineRenderTarget> _Other, int _Index)
{
	MergeUnit->ShaderResources.SetTexture("Tex", _Other->GetRenderTargetTexture(_Index));

	Effect(MergeUnit);
}

void GameEngineRenderTarget::Effect(std::shared_ptr<GameEngineRenderUnit> _RenderSet)
{
	Setting();
	_RenderSet->Render(GameEngineTime::GetDeltaTime());
}

void GameEngineRenderTarget::CreateRenderTargetTexture(ID3D11Texture2D* _Texture, float4 _Color)
{
	std::shared_ptr<GameEngineTexture> NewTexture = GameEngineTexture::Create(_Texture);
	CreateRenderTargetTexture(NewTexture, _Color);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(float4 _Size, float4 _Color)
{
	CreateRenderTargetTexture(_Size, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, _Color);
}

void GameEngineRenderTarget::SettingDepthTexture(std::shared_ptr<GameEngineTexture> _Texture)
{
	DepthTexture = _Texture;
	DepthStencilView = DepthTexture->CreateDepthStencilView();
}

void GameEngineRenderTarget::CreateRenderTargetTexture(float4 _Size, DXGI_FORMAT _Format, float4 _Color)
{
	D3D11_TEXTURE2D_DESC NewData = {0};
	NewData.ArraySize = 1; // 한번에 10장짜리도 만들수 있어요
	NewData.Width = _Size.uix();
	NewData.Height = _Size.uiy();
	NewData.Format = _Format;
	NewData.SampleDesc.Count = 1;
	NewData.SampleDesc.Quality = 0;
	NewData.MipLevels = 1;
	NewData.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	//                  여기에다가 랜더링을 할수도 있고               이걸 쉐이더에서 사용할수도 있다는 겁니다.
	NewData.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

	CreateRenderTargetTexture(NewData, _Color);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(std::shared_ptr < GameEngineTexture> _Texture, float4 _Color)
{
	RenderTargets.push_back(_Texture);
	RenderTargetViews.push_back(_Texture->CreateRenderTargetView());
	ShaderResourceViews.push_back(_Texture->CreateShaderResourceView());
	ClearColors.push_back(_Color);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(D3D11_TEXTURE2D_DESC _Data, float4 _Color)
{
	std::shared_ptr<GameEngineTexture> NewTexture = GameEngineTexture::Create(_Data);
	CreateRenderTargetTexture(NewTexture, _Color);
}

void GameEngineRenderTarget::Clear(bool _IsDepthClear)
{
	for (size_t i = 0; i < RenderTargetViews.size(); i++)
	{
		GameEngineDevice::GetContext()->ClearRenderTargetView(RenderTargetViews[i], ClearColors[i].Arr1D);
	}

	if (false == _IsDepthClear)
	{
		return;
	}

	if (nullptr != DepthStencilView)
	{
		GameEngineDevice::GetContext()->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void GameEngineRenderTarget::CreateDepthTexture(int _Index) 
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };
	Desc.ArraySize = 1;
	Desc.Width = RenderTargets[_Index]->GetScale().uix();
	Desc.Height = RenderTargets[_Index]->GetScale().uiy();
	//             24비트 float + 8비트 unsigned int
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	// 할수 있다면 쓰겠다는것
	Desc.MipLevels = 1;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	// cpu에서는 접근 못함
	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	DepthTexture = GameEngineTexture::Create(Desc);

	DepthStencilView = DepthTexture->CreateDepthStencilView();
}

void GameEngineRenderTarget::Setting()
{
	// int* NewInt = new int[10];

	// GameEngineRenderTarget** NewInt = new GameEngineRenderTarget*[10]

	if (0 == RenderTargetViews.size())
	{
		MsgBoxAssert("랜더타겟뷰가 존재하지 않는 랜더타겟을 세팅하려고 했습니다.");
	}

	GameEngineDevice::GetContext()->OMSetRenderTargets(static_cast<UINT>(RenderTargetViews.size()), &RenderTargetViews[0], DepthStencilView);
}


void GameEngineRenderTarget::EffectProcess()
{
	// Setting();

	for (std::shared_ptr<GameEnginePostEffect>& Effect : Effects)
	{
		if (false == Effect->IsUpdate())
		{
			continue;
		}

		Effect->Effect(shared_from_this());
	}
}