#include "PreCompile.h"
#include "GameEngineDepthStencil.h"


std::shared_ptr<GameEngineDepthStencil> GameEngineDepthStencil::Create(const std::string& _Name, const D3D11_DEPTH_STENCIL_DESC& _Desc)
{
	std::shared_ptr<GameEngineDepthStencil> NewRes = CreateResName(_Name);
	NewRes->Create(_Desc);
	return NewRes;
}

GameEngineDepthStencil::GameEngineDepthStencil() 
	: State(nullptr)
	, Desc()
{
}

GameEngineDepthStencil::~GameEngineDepthStencil() 
{
	if (nullptr != State)
	{
		State->Release();
	}
}

void GameEngineDepthStencil::Setting() 
{
	GameEngineDevice::GetContext()->OMSetDepthStencilState(State, 0);
}

void GameEngineDepthStencil::Create(const D3D11_DEPTH_STENCIL_DESC& _Desc)
{
	Desc = _Desc;

	if (S_OK != GameEngineDevice::GetDevice()->CreateDepthStencilState(&Desc, &State))
	{
		MsgBoxAssert("뎁스 버퍼 생성에 실패했습니다.");
	}
}