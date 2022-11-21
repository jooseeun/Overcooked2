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
	, PipeLine(nullptr)
	, Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, InputLayOut(nullptr)
{
	SetMesh("rect");
}

GameEngineRenderUnit::GameEngineRenderUnit(const GameEngineRenderUnit& _Render)
{
	ParentRenderer = _Render.ParentRenderer;
	Mesh = _Render.Mesh;
	PipeLine = _Render.PipeLine;
	InputLayOut = _Render.InputLayOut;
	Topology = _Render.Topology;

	if (nullptr == PipeLine)
	{
		return;
	}
	ShaderResources.ResourcesCheck(PipeLine);
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

	if (nullptr == InputLayOut && nullptr != PipeLine)
	{
		// 파이프라인의 버텍스 쉐이더와
		// 매쉬의 버텍스 정보가 다 모여있으므로
		// 인풋 레이아웃을 만들수가 있다.
		InputLayOut = GameEngineInputLayOut::Create(Mesh->GetLayOutDesc(), PipeLine->GetVertexShader());
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

	if (nullptr == InputLayOut && nullptr != PipeLine)
	{
		InputLayOut = GameEngineInputLayOut::Create(Mesh->GetLayOutDesc(), PipeLine->GetVertexShader());
	}
}

void GameEngineRenderUnit::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineMaterial::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("존재하지 않는 파이프라인을 세팅하려고 했습니다.");
		return;
	}

	if (nullptr == InputLayOut && nullptr != Mesh)
	{
		InputLayOut = GameEngineInputLayOut::Create(Mesh->GetLayOutDesc(), PipeLine->GetVertexShader());
	}

	ShaderResources.ResourcesCheck(PipeLine);

}

void GameEngineRenderUnit::SetRenderer(std::shared_ptr<GameEngineRenderer> _Renderer)
{
	ParentRenderer = _Renderer;

	EngineShaderResourcesSetting(ParentRenderer.lock());
}


std::shared_ptr<GameEngineMaterial> GameEngineRenderUnit::GetPipeLine()
{
	return PipeLine;
}

std::shared_ptr < GameEngineMaterial> GameEngineRenderUnit::GetClonePipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	PipeLine = ClonePipeLine(PipeLine);
	return PipeLine;
}


std::shared_ptr < GameEngineMaterial> GameEngineRenderUnit::ClonePipeLine(std::shared_ptr<GameEngineMaterial> _Rendering)
{
	// 이름없는 녀석으로 만든다.
	std::shared_ptr < GameEngineMaterial> Clone = GameEngineMaterial::Create();
	Clone->Copy(_Rendering);
	return Clone;
}




void GameEngineRenderUnit::Render(float _DeltaTime)
{
	if (nullptr == PipeLine)
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

	//if (false == IsInstancing(GetPipeLine()))
	//{

	Mesh->Setting();

	InputLayOut->Setting();

	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology);
	PipeLine->Setting();
	ShaderResources.AllResourcesSetting();
	Mesh->Render();

	ShaderResources.AllResourcesReset();
	//}
	//else
	//{
	//	 InstancingDataSetting(GetPipeLine());
	//	 Camera->PushInstancingIndex(PipeLine);
	//}
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


bool GameEngineRenderer::IsInstancing(std::shared_ptr<GameEngineMaterial> _Rendering)
{
	std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator InstancingIter = Camera.lock()->InstancingMap.find(_Rendering.get());

	if (InstancingIter == Camera.lock()->InstancingMap.end())
	{
		return false;
	}

	return true == IsInstancing_ && GameEngineInstancing::MinInstancingCount <= InstancingIter->second.Count;
}

// 우리 엔진에서 인스턴싱을 한다면 무조건 숫자하나만 인스턴싱을 했으니까. 이건 ok
void GameEngineRenderer::InstancingDataSetting(std::shared_ptr<GameEngineMaterial> _Line)
{
	// 몇번째 순서인지 알려주고 있어요
	// 이녀석을 통해서 
	int InstancingIndex = Camera.lock()->PushInstancingIndex(_Line);

	GameEngineInstancing* Instancing = Camera.lock()->GetInstancing(_Line);

	if (nullptr == Instancing)
	{
		MsgBoxAssert("인스턴싱이 켜져있지만 인스턴싱 정보는 없습니다.");
	}

	if (true == Instancing->ShaderResources.IsStructuredBuffer("AllInstancingTransformData"))
	{
		GameEngineStructuredBufferSetter* Setter = Instancing->ShaderResources.GetStructuredBuffer("AllInstancingTransformData");

		Setter->Push(GetTransform().GetTransformData(), InstancingIndex);

		

		//Setter->Res

		// GetTransform().GetTransformData()
	}
}


//void GameEngineRenderer::Render(float _DeltaTime)
//{
//	//// 랜더링
//	////GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Rect");
//	////GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Rect");
//
//	//GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Box");
//	//GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Box");
//	//
//	//std::vector<POINT> DrawVertex;
//	//DrawVertex.resize(Index->Indexs.size());
//
//	//std::vector<float4> CopyBuffer;
//	//CopyBuffer.resize(Index->Indexs.size());
//
//
//	//for (size_t i = 0; i < Index->Indexs.size(); i++)
//	//{
//	//	int TriIndex = Index->Indexs[i];
//
//	//	// 0 번째 순서의 점이 됩니다.
//	//	// 최초에 원본 매쉬의 점을 복사합니다.
//	//	CopyBuffer[i] = Vertex->Vertexs[TriIndex];
//
//	//	auto& tran = GetTransform();
//
//	//	// 버텍스쉐이더
//	//	CopyBuffer[i] = CopyBuffer[i] * GetTransform().GetWorldViewProjection();
//
//
//	//	// 레스터라이저
//	//	//// 기록해놨던 z값으로 나뉘는것
//	//	CopyBuffer[i] = CopyBuffer[i] / CopyBuffer[i].w;
//
//
//	//	DrawVertex[i] = CopyBuffer[i].GetConvertWindowPOINT();
//	//}
//	//
//	//for (size_t i = 0; i < DrawVertex.size(); i += 3)
//	//{
//	//	Polygon(GameEngineWindow::GetHDC(), &DrawVertex[i], 3);
//	//}
//}

void GameEngineRenderer::ChangeCamera(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()), _Order);
}
