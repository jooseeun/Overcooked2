#include "PreCompile.h"
#include "TitleVan.h"
#include "MouseInputWindow.h"

TitleVan::TitleVan()
	: Renderer_(nullptr)
{
}

TitleVan::~TitleVan()
{
}

void TitleVan::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("m_van_01.FBX", "Texture");
	Renderer_->GetTransform().SetLocalScale({ 50,50,50 });

	Sign_ = GetLevel()->CreateActor<VanSign>();
	IsSignUp_ = true;
}

void TitleVan::Update(float _DeltaTime)
{
	if (true == IsSignUp_)
	{
		Sign_->GetTransform().SetWorldMove(float4::UP * 80.f * _DeltaTime);

		if (300.f <= Sign_->GetTransform().GetWorldPosition().y)
		{
			IsSignUp_ = false; 
			Sign_->Off();
		}
	}
}


VanSign::VanSign()
	: SignRenderer_(nullptr)
{
}

VanSign::~VanSign()
{
}

void VanSign::Start()
{
	SignRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	SignRenderer_->SetFBXMesh("Sign.FBX", "Texture");
	SignRenderer_->GetTransform().SetWorldPosition({ 208.f, 99.f, 109.f });
	SignRenderer_->GetTransform().SetWorldRotation({ 0.f, 10.5f, 0.f });
	SignRenderer_->GetTransform().SetWorldScale({ 2.2f,2.5f,2.5f });
}

void VanSign::Update(float _DeltaTime)
{
}
