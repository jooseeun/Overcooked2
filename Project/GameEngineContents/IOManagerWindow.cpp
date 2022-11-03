#include "PreCompile.h"
#include "IOManagerWindow.h"

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
		Save(IOType::Tile);
	}

	if (true == ImGui::Button("Load"))
	{
		Load(IOType::Tile);
	}

	if (true == ImGui::Button("Add"))
	{
		MapData TmpData = {};
		TmpData.MapObjType_ = MapObjType::Table;
		TmpData.Pos_ = float4(1, 2, 3) * (MapDataVector_.size() + 1);
		TmpData.Rot_ = float4(1, 2, 3) * (MapDataVector_.size() + 1);
		TmpData.Scale_ = float4(1, 2, 3) * (MapDataVector_.size() + 1);
		TmpData.Tile_ = float4(1, 2, 3) * (MapDataVector_.size() + 1);

		AddTileData(TmpData);
	}

	ImGui::Text(std::to_string(MapDataVector_.size()).c_str());

	int a = 0;
}

void IOManagerWindow::AddTileData(MapData _Data)
{
	MapDataVector_.push_back(_Data);
}

void IOManagerWindow::Save(IOType _Type)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	GameEngineFile SaveFile = (Dir.GetFullPath() + "\\" + "Test.meta").c_str();
	//GameEngineFile SaveFile = (Dir.GetFullPath() + "\\" + static_cast<char>(_Type) + ".meta").c_str();
	SaveFile.Open(OpenMode::Write);

	int VectorSize = static_cast<int>(MapDataVector_.size());
	SaveFile.Write(&VectorSize, sizeof(int));

	for (size_t i = 0; i < VectorSize; i++)
	{
		SaveFile.Write(&MapDataVector_[i].MapObjType_, sizeof(MapObjType));
		SaveFile.Write(&MapDataVector_[i].Pos_, sizeof(float4));
		SaveFile.Write(&MapDataVector_[i].Rot_, sizeof(float4));
		SaveFile.Write(&MapDataVector_[i].Scale_, sizeof(float4));
		SaveFile.Write(&MapDataVector_[i].Tile_, sizeof(float4));
	}
}

void IOManagerWindow::Load(IOType _Type)
{
	MapDataVector_.clear();

	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	GameEngineFile LoadFile = (Dir.GetFullPath() + "\\" + "Test.meta").c_str();
	//GameEngineFile LoadFile = (Dir.GetFullPath() + "\\" + static_cast<char>(_Type) + ".meta").c_str();
	LoadFile.Open(OpenMode::Read);

	int VectorSize = 0;
	LoadFile.Read(&VectorSize, sizeof(int), sizeof(int));

	for (size_t i = 0; i < VectorSize; i++)
	{
		MapData TmpData = {};
		LoadFile.Read(TmpData.MapObjType_);
		LoadFile.Read(TmpData.Pos_);
		LoadFile.Read(TmpData.Rot_);
		LoadFile.Read(TmpData.Scale_);
		LoadFile.Read(TmpData.Tile_);

		MapDataVector_.push_back(TmpData);
	}
}
