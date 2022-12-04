#include "PreCompile.h"
#include "TitleVan.h"


TitleVan::TitleVan() 
	:Van_(nullptr)
{
}

TitleVan::~TitleVan() 
{
}

void TitleVan::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	std::shared_ptr<GameEngineFBXStaticRenderer> Test = CreateComponent<GameEngineFBXStaticRenderer>();
	Test->SetFBXMesh("m_van_01.FBX", "Texture");
	Test->GetTransform().SetLocalScale({ 10,10,10 });
}

void TitleVan::Update(float _DeltaTime)
{


}