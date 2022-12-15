#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();
	Unit = CreateRenderUnit();
}

void GameEngineDefaultRenderer::SetMesh(const std::string& _Name)
{
	Unit->SetMesh(_Name);
}

void GameEngineDefaultRenderer::SetMaterial(const std::string& _Name)
{
	Unit->SetMaterial(_Name);
	Unit->PushCamera();
}

void GameEngineDefaultRenderer::Render(float _DeltaTime) 
{
	Unit->Render(_DeltaTime);
}

