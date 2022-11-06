#include "PreCompile.h"
#include "IOManagerWindow.h"
#include "GlobalIOManager.h"

IOManagerWindow::IOManagerWindow()
{
}

IOManagerWindow::~IOManagerWindow()
{
}

void IOManagerWindow::Initialize(GameEngineLevel* _Level)
{
}

void IOManagerWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::Button("Save"))
	{
		GlobalIOManager::Save(IOType::UnsortMap);
	}

	if (true == ImGui::Button("Load"))
	{
		GlobalIOManager::Load(IOType::UnsortMap);
	}

	if (true == ImGui::Button("Add"))
	{
		{
			MapData TmpData = {};
			TmpData.ObjName_ = "TestFbx";
			TmpData.MapObjType_ = MapObjType::CounterTop;
			TmpData.Transform_ = &GEngine::GetCurrentLevel()->CreateActor<GameEngineActor>()->GetTransform();
			TmpData.Transform_->SetWorldPosition({ 0, 1, 2 });
			TmpData.Transform_->SetWorldRotation({ 3, 4, 5 });
			TmpData.Transform_->SetWorldScale({ 6, 7, 8 });
			TmpData.Index_ = float4(1, 2, 3);

			GlobalIOManager::AddMapData(TmpData);
		}

		{
			MapData TmpData = {};
			TmpData.ObjName_ = "TestTestFBX";
			TmpData.MapObjType_ = MapObjType::Bin;
			TmpData.Transform_ = &GEngine::GetCurrentLevel()->CreateActor<GameEngineActor>()->GetTransform();
			TmpData.Transform_->SetWorldPosition({ 0, 1, 2 });
			TmpData.Transform_->SetWorldRotation({ 3, 4, 5 });
			TmpData.Transform_->SetWorldScale({ 6, 7, 8 });
			TmpData.Index_ = float4(1, 2, 3);

			GlobalIOManager::AddMapData(TmpData);
		}

		{
			MeshData TmpData = {};
			TmpData.MeshName_ = "Test1";
			TmpData.Path_ = "Test\\Data\\www\\Test1";
			TmpData.MaterialName_ = "Mat22";

			GlobalIOManager::AddMeshData(TmpData);
		}

		{
			MeshData TmpData = {};
			TmpData.MeshName_ = "Test2";
			TmpData.Path_ = "Test\\Da2ta\\ggg\\Test2";
			TmpData.MaterialName_ = "Mat44";

			GlobalIOManager::AddMeshData(TmpData);
		}
	}


	int a = 0;
}
