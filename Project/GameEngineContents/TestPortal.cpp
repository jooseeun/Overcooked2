#include "PreCompile.h"
#include "TestPortal.h"

TestPortal::TestPortal() 
{
}

TestPortal::~TestPortal() 
{
}



void TestPortal::Start()
{

	//std::shared_ptr<GameEngineFBXStaticRenderer> Test_;
	Test_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Test_->SetFBXMesh("ms_pfx_Teleport_1.FBX", "Texture");

	Test_->GetTransform().SetLocalScale({ 100,100,100 });
	Test_->GetTransform().SetWorldPosition({-5000, -900, 0});

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> Unit_ = Test_->GetAllRenderUnit();

	Unit_[0][0]->GetCloneMaterial()->SetOutputMergerBlend("AddBlend");

	//Test_->SetFBXMesh("ms_pfx_Teleport_1.FBX");


	//Mesh_->GetFbxRenderUnit()[0].GetP;


}



void TestPortal::Update(float _Delta)
{
	//std::vector<std::vector<GameEngineRenderUnit>> Unit_ = Test_->GetAllRenderUnit();


	//Unit_[0][0].GetMaterial()->SetOutputMergerBlend("AddBlend");
	//Unit_[0][0].GetMaterial()->OutputMergerBlendSetting();

}

