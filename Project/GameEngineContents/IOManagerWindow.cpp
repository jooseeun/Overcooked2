#include "PreCompile.h"
#include "IOManagerWindow.h"

IOManagerWindow::IOManagerWindow()
	: IsOrganize_(false)
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
		GlobalIOManager::Save(IOType::Mesh);
	}

	if (true == ImGui::Button("Load"))
	{
		GlobalIOManager::Load(IOType::Mesh);
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
			TmpData.MapObjType_ = MapObjType::TrashCan;
			TmpData.Transform_ = &GEngine::GetCurrentLevel()->CreateActor<GameEngineActor>()->GetTransform();
			TmpData.Transform_->SetWorldPosition({ 0, 1, 2 });
			TmpData.Transform_->SetWorldRotation({ 3, 4, 5 });
			TmpData.Transform_->SetWorldScale({ 6, 7, 8 });
			TmpData.Index_ = float4(1, 2, 3);

			GlobalIOManager::AddMapData(TmpData);
		}

		{
			MeshData TmpData = {};
			TmpData.PreviewMeshName_ = "Test1";
			SubSetMeshData TmpSub = { "Test\\Data\\www\\Test1", "Mat22" };
			TmpData.PreviewMeshInfo_.push_back(TmpSub);

			GlobalIOManager::SetMeshData(TmpData);
		}

		{
			MeshData TmpData = {};
			TmpData.PreviewMeshName_ = "Test2";

			TmpData.PreviewMeshInfo_.push_back({ "Test\\Da2ta\\ggg\\Test2", "Mat44" });

			SubSetMeshData TmpSub = { "Test\\Data\\www\\Test1", "Mat22" };
			TmpData.PreviewMeshInfo_.push_back(TmpSub);

			GlobalIOManager::SetMeshData(TmpData);
		}
	}

	if (IsOrganize_)
	{
		if (true == ImGui::Button("Off"))
		{
			IsOrganize_ = false;
			GEngine::GetCurrentLevel()->GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		}

		if (true == ImGui::Button("X"))
		{
			GEngine::GetCurrentLevel()->GetMainCameraActorTransform().SetWorldRotation({ 0, 90, 0 });
		}
		if (true == ImGui::Button("Y"))
		{
			GEngine::GetCurrentLevel()->GetMainCameraActorTransform().SetWorldRotation({ 90, 0, 0 });
		}
		if (true == ImGui::Button("Z"))
		{
			GEngine::GetCurrentLevel()->GetMainCameraActorTransform().SetWorldRotation({0, 0, 0});
		}
	}
	else
	{
		if (true == ImGui::Button("On"))
		{
			IsOrganize_ = true;
			GEngine::GetCurrentLevel()->GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		}
	}


	int a = 0;
}
