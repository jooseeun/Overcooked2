#include "PreCompile.h"
#include "GameEngineMaterial.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineBlend.h"


GameEngineMaterial::GameEngineMaterial() 
	: // InputLayOut(nullptr)
	// , VertexBuffer(nullptr)
	VertexShader(nullptr)
	// , IndexBuffer(nullptr)
	, Rasterizer(nullptr)
	, PixelShader(nullptr)
	, DepthStencil(nullptr)
	, Blend(nullptr)
{

	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
	Blend = GameEngineBlend::Find("AlphaBlend");
	DepthStencil = GameEngineDepthStencil::Find("EngineBaseDepth");
}

GameEngineMaterial::~GameEngineMaterial() 
{
}

//
//void GameEngineMaterial::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
//{
//	InputLayOut = GameEngineInputLayOut::Find(_Name);
//
//	if (nullptr == InputLayOut)
//	{
//		MsgBoxAssert("존재하지 않는 인풋레이아웃을 세팅하려고 했습니다.");
//		return;
//	}
//}

void GameEngineMaterial::AllShaderReset()
{
	GameEngineDevice::GetContext()->VSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->DSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->HSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->PSSetShader(nullptr, nullptr, 0);
}

std::shared_ptr < GameEngineMaterial> GameEngineMaterial::Create()
{
	return CreateResUnName();
}

std::shared_ptr < GameEngineMaterial> GameEngineMaterial::Create(const std::string& _Name)
{
	return CreateResName(_Name);
}

void GameEngineMaterial::SetVertexShader(const std::string& _Name)
{
	VertexShader = GameEngineVertexShader::Find(_Name);

	if (nullptr == VertexShader)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}

	//// 인풋레이아웃이 만들어지지 않았는데.
	//if (nullptr == InputLayOut && nullptr != VertexBuffer)
	//{
	//	InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	//}
}

void GameEngineMaterial::SetVertexShader(std::shared_ptr < GameEngineVertexShader> _Shader)
{
	VertexShader = _Shader;

	// 인풋레이아웃이 만들어지지 않았는데.
	// 인스턴싱때 문제될수 있다.
	//if (nullptr == InputLayOut && nullptr != VertexBuffer)
	//{
	//	InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	//}

}


void GameEngineMaterial::SetRasterizer(const std::string& _Name)
{
	Rasterizer = GameEngineRasterizer::Find(_Name);

	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("존재하지 않는 레스터라이저 세팅를 세팅하려고 했습니다.");
		return;
	}

}


void GameEngineMaterial::SetPixelShader(const std::string& _Name)
{
	PixelShader = GameEnginePixelShader::Find(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고 했습니다.");
		return;
	}

}



void GameEngineMaterial::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil = GameEngineDepthStencil::Find(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("존재하지 않는 깊이스텐실를 세팅하려고 했습니다.");
		return;
	}

}


void GameEngineMaterial::SetOutputMergerBlend(const std::string& _Name)
{
	Blend = GameEngineBlend::Find(_Name);

	if (nullptr == Blend)
	{
		MsgBoxAssert("존재하지 않는 블랜더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::Setting()
{
	VertexShaderSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();
}

void GameEngineMaterial::SettingInstancing()
{
	InstancingVertexShaderSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();
}

void GameEngineMaterial::InstancingDataCollect()
{
	// InstancingDraw();
}

// 실직적으로 세팅의 순서는 그다지 중요하지 않다.

void GameEngineMaterial::InputAssembler1InstancingVertexBufferSetting(std::shared_ptr < GameEngineInstancingBuffer> _Buffer)
{
	
}

void GameEngineMaterial::VertexShaderSetting() 
{
	VertexShader->Setting();
}

void GameEngineMaterial::InstancingVertexShaderSetting()
{
	VertexShader->GetInstancingShader()->Setting();
}

void GameEngineMaterial::RasterizerSetting() 
{
	Rasterizer->Setting();
}

void GameEngineMaterial::PixelShaderSetting() 
{
	PixelShader->Setting();
}

void GameEngineMaterial::OutputMergerBlendSetting() 
{
	Blend->Setting();
}

void GameEngineMaterial::OutputMergerDepthStencilSetting() 
{
	DepthStencil->Setting();
}


//void GameEngineMaterial::Draw(GameEngineMesh* _Mesh)
//{
//	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
//}

void GameEngineMaterial::InstancingDraw(int _RenderingCount)
{
	//[in] IndexCountPerInstance 유형 : UINT
	//각 인스턴스에 대해 인덱스 버퍼에서 읽은 인덱스 수입니다.
	//

	//[in] InstanceCount 유형 : UINT
	//그릴 인스턴스 수입니다.

	//[in] StartIndexLocation
	//유형 : UINT GPU가 인덱스 버퍼에서 읽은 첫 번째 인덱스의 위치입니다.

	//[in] BaseVertexLocation 유형 : 지능
	//정점 버퍼에서 정점을 읽기 전에 각 인덱스에 추가된 값입니다.

	//[in] StartInstanceLocation 유형 : UINT
	//정점 버퍼에서 인스턴스별 데이터를 읽기 전에 각 인덱스에 추가된 값입니다.

	// 그냥 4가 들어간다.
	// GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer->GetIndexCount(), _RenderingCount, 0, 0, 0);
}

void GameEngineMaterial::Copy(std::shared_ptr<GameEngineMaterial> _Original)
{
	// InputLayOut			= _Original->InputLayOut;
	// VertexBuffer			= _Original->VertexBuffer;
	VertexShader			= _Original->VertexShader;
	// IndexBuffer			= _Original->IndexBuffer;
	// Topology				= _Original->Topology;
	Rasterizer				= _Original->Rasterizer;
	PixelShader			= _Original->PixelShader;
	DepthStencil			= _Original->DepthStencil;
	Blend					= _Original->Blend;
}

void GameEngineMaterial::SetWireFrame()
{
	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer_Wire");

}

void GameEngineMaterial::SetFillSolid()
{
	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");

}
