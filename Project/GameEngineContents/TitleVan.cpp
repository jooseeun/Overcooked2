#include "PreCompile.h"
#include "TitleVan.h"


TitleVan::TitleVan() 
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
	Test->GetTransform().SetLocalScale({ 100,100,100 });
}

void TitleVan::Update(float _DeltaTime)
{


}