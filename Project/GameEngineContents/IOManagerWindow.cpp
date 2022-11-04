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
	if (true == ImGui::Button("Create"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("SaveFiles");
		GameEngineFile TmpFile = (Dir.GetFullPath() + "\\" + "Test.meta").c_str();
		TmpFile.Create();
	}

	if (true == ImGui::Button("Save"))
	{
		GlobalIOManager::Save(IOType::Tile);
	}

	if (true == ImGui::Button("Load"))
	{
		GlobalIOManager::Load(IOType::Tile);
	}

	if (true == ImGui::Button("Add"))
	{
		MapData TmpData = {};
		TmpData.MapObjType_ = MapObjType::Table;
		TmpData.Actor_ = nullptr;
		TmpData.Tile_ = float4(1, 2, 3);

		GlobalIOManager::AddTileData(TmpData);
	}

	//ImGui::Text(std::to_string(MapDataVector_.size()).c_str());

	int a = 0;
}
