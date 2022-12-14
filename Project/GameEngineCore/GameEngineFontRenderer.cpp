#include "PreCompile.h"
#include "GameEngineFontRenderer.h"
#include "GameEngineBlend.h"
#include "GameEngineCamera.h"

std::shared_ptr<GameEngineRenderTarget> GameEngineFontRenderer::FontTarget = nullptr;

GameEngineFontRenderer::GameEngineFontRenderer()
	: Font(nullptr)
	, FontSize(20.0f)
	, Color(float4::WHITE)
	, ScreenPostion(float4::ZERO)
	, IsAffectTransform(false)
	, LR()
	, TB()
{
}

GameEngineFontRenderer::~GameEngineFontRenderer()
{
}

void GameEngineFontRenderer::SetText(const std::string& _Text, const std::string& _Font)
{
	Text = _Text;
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::Start()
{
	if (nullptr == FontTarget)
	{
		FontTarget = GameEngineRenderTarget::Create("FontTarget");
		FontTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), float4::ZERO);
	}

	PushRendererToMainCamera();

	FontUnit = std::make_shared<GameEngineRenderUnit>();
	FontUnit->RenderFunction = std::bind(&GameEngineFontRenderer::FontDraw, this, std::placeholders::_1);
	FontUnit->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	FontUnit->PushCamera();
}

void GameEngineFontRenderer::Render(float _DeltaTime)
{
}

bool GameEngineFontRenderer::FontDraw(float _DeltaTime)
{
	if (nullptr == Font)
	{
		return false;
	}

	float4 Pos = ScreenPostion;
	if (Mode == FontPositionMode::WORLD)
	{
		Pos = GetTransform().GetWorldPosition();

		Pos *= Camera->GetViewMatrix();
		Pos *= Camera->GetProjectionMatrix();

		float4x4 ViewPort;

		float4 Size = GameEngineWindow::GetInst()->GetScale();
		ViewPort.ViewPort(Size.x, Size.y, 0.0f, 0.0f, 0.0f, 1.0f);

		Pos *= ViewPort;
	}

	FontTarget->Clear();
	FontTarget->Setting();

	if (true == IsAffectTransform)
	{
		float4 WorldPos = GetTransform().GetWorldPosition();
		Pos = float4(WorldPos.x, -WorldPos.y, WorldPos.z) + GameEngineWindow::GetScale().Half();
	}
	Font->FontDraw(Text, FontSize, Pos, Color, static_cast<int>(LR) | static_cast<int>(TB));
	GameEngineMaterial::AllShaderReset();
	Camera->GetCameraRenderTarget()->Merge(FontTarget);
	return false;
}
