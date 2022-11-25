#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineCamera.h"
#include "GameEngineInstancing.h"


#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineMesh.h"

#include "GameEngineInputLayOut.h"


//////////////////////////////////////////////////////// GameEngineRenderUnit 

GameEngineRenderUnit::GameEngineRenderUnit() 
	: ParentRenderer()
	, Material(nullptr)
	, Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, InputLayOut(nullptr)
	, IsOn(true)
{
	SetMesh("rect");
}

GameEngineRenderUnit::GameEngineRenderUnit(const GameEngineRenderUnit& _Render)
{
	ParentRenderer = _Render.ParentRenderer;
	Mesh = _Render.Mesh;
	Material = _Render.Material;
	InputLayOut = _Render.InputLayOut;
	Topology = _Render.Topology;

	if (nullptr == Material)
	{
		return;
	}
	ShaderResources.ResourcesCheck(Material);
}

void GameEngineRenderUnit::EngineShaderResourcesSetting(std::shared_ptr<GameEngineRenderer> _Renderer)
{
	if (nullptr == _Renderer)
	{
		return;
	}

	ParentRenderer = _Renderer;

	//// 랜더러 쪽으로 빠져야 한다.
	if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	{
		ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &ParentRenderer.lock()->GetTransformData(), sizeof(TransformData));
	}

	if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	{
		ShaderResources.SetConstantBufferLink("RENDEROPTION", &ParentRenderer.lock()->RenderOptionInst, sizeof(RenderOption));
	}
}

void GameEngineRenderUnit::SetMesh(const std::string& _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
		return;
	}

	if (nullptr == InputLayOut && nullptr != Material)
	{
		InputLayOut = GameEngineInputLayOut::Create(Mesh->GetLayOutDesc(), Material->GetVertexShader());
	}
}

void GameEngineRenderUnit::SetMesh(std::shared_ptr<GameEngineMesh> _Mesh)
{
	if (nullptr == _Mesh)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
		return;
	}

	Mesh = _Mesh;

	if (nullptr == InputLayOut && nullptr != Material)
	{
		InputLayOut = GameEngineInputLayOut::Create(Mesh->GetLayOutDesc(), Material->GetVertexShader());
	}
}

void GameEngineRenderUnit::SetMaterial(const std::string& _Name)
{
	Material = GameEngineMaterial::Find(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 마테리얼을 세팅하려고 했습니다.");
		return;
	}

	if (nullptr == InputLayOut && nullptr != Mesh)
	{
		InputLayOut = GameEngineInputLayOut::Create(Mesh->GetLayOutDesc(), Material->GetVertexShader());
	}

	ShaderResources.ResourcesCheck(Material);
}

void GameEngineRenderUnit::SetRenderer(std::shared_ptr<GameEngineRenderer> _Renderer)
{
	ParentRenderer = _Renderer;

	EngineShaderResourcesSetting(ParentRenderer.lock());
}

std::shared_ptr<GameEngineMesh> GameEngineRenderUnit::GetMesh()
{
	return Mesh;
}

std::shared_ptr<GameEngineMaterial> GameEngineRenderUnit::GetMaterial()
{
	return Material;
}

std::shared_ptr < GameEngineMaterial> GameEngineRenderUnit::GetCloneMaterial()
{
	if (false == Material->IsOriginal())
	{
		return Material;
	}

	Material = CloneMaterial(Material);
	return Material;
}


std::shared_ptr < GameEngineMaterial> GameEngineRenderUnit::CloneMaterial(std::shared_ptr<GameEngineMaterial> _Rendering)
{
	// 이름없는 녀석으로 만든다.
	std::shared_ptr < GameEngineMaterial> Clone = GameEngineMaterial::Create();
	Clone->Copy(_Rendering);
	return Clone;
}

void GameEngineRenderUnit::Render(float _DeltaTime)
{
	if (false == IsOn)
	{
		return;
	}

	if (nullptr == Material)
	{
		MsgBoxAssert("마테리얼이 세팅되지 않으면 랜더링을 할수 없습니다.");
	}

	if (nullptr == Mesh)
	{
		MsgBoxAssert("매쉬가 없으므로 랜더링을 할수 없습니다.");
	}

	if (nullptr == InputLayOut)
	{
		MsgBoxAssert("인풋 레이아웃이 없으므로 랜더링을 할수 없습니다.");
	}


	Mesh->Setting();

	InputLayOut->Setting();

	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology);
	Material->Setting();
	ShaderResources.AllResourcesSetting();
	Mesh->Render();

	ShaderResources.AllResourcesReset();
}

void GameEngineRenderUnit::RenderInstancing(float _DeltaTime, size_t _RanderingCount, std::shared_ptr<GameEngineInstancingBuffer> _Buffer)
{
	if (nullptr == Material)
	{
		MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할수 없습니다.");
	}

	if (nullptr == Mesh)
	{
		MsgBoxAssert("매쉬가 없으므로 랜더링을 할수 없습니다.");
	}

	if (nullptr == InputLayOut)
	{
		MsgBoxAssert("인풋 레이아웃이 없으므로 랜더링을 할수 없습니다.");
	}


	Mesh->SettingInstancing(_Buffer);
	InputLayOut->Setting();
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology);
	Material->SettingInstancing();
	ShaderResources.AllResourcesSetting();

	Mesh->RenderInstancing(_RanderingCount);
	ShaderResources.AllResourcesReset();
}

//////////////////////////////////////////////////////// GameEngineRenderer

GameEngineRenderer::GameEngineRenderer()
	: CameraOrder(CAMERAORDER::MAINCAMERA)
	, RenderingOrder(0)
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start() 
{
	PushRendererToMainCamera();
}

void GameEngineRenderer::PushRendererToMainCamera()
{
	GetActor()->GetLevel()->PushRendererToMainCamera(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
}

void GameEngineRenderer::SetRenderingOrder(int _Order)
{
	Camera.lock()->ChangeRenderingOrder(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()), _Order);
}

void GameEngineRenderer::PushRendererToUICamera()
{
	GetActor()->GetLevel()->PushRendererToUICamera(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
}

void GameEngineRenderer::ChangeCamera(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()), _Order);
}
