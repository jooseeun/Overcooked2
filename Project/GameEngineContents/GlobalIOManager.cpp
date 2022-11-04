#include "PreCompile.h"
#include "GlobalIOManager.h"

GlobalIOManager* GlobalIOManager::Inst_ = nullptr;
std::vector<MapData> GlobalIOManager::MapDataVector_;

GlobalIOManager::GlobalIOManager()
{
	Inst_ = this;
}

GlobalIOManager::~GlobalIOManager()
{
}

void GlobalIOManager::AddTileData(MapData _Data)
{
	MapDataVector_.push_back(_Data);
}

void GlobalIOManager::Save(IOType _Type)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	GameEngineFile SaveFile = (Dir.GetFullPath() + "\\" + "Test.meta").c_str();
	//GameEngineFile SaveFile = (Dir.GetFullPath() + "\\" + static_cast<char>(_Type) + ".meta").c_str();
	SaveFile.Open(OpenMode::Write);

	int VectorSize = static_cast<int>(MapDataVector_.size());
	SaveFile.Write(std::to_string(VectorSize));
	for (size_t i = 0; i < VectorSize; i++)
	{
		SaveFile.Write("Type: " + (char)(&MapDataVector_[i].MapObjType_));
		SaveFile.Write("Pos: " + MapDataVector_[i].Actor_->GetTransform().GetWorldPosition().ToString());
		SaveFile.Write("Rot: " + MapDataVector_[i].Actor_->GetTransform().GetWorldRotation().ToString());
		SaveFile.Write("Scale: " + MapDataVector_[i].Actor_->GetTransform().GetWorldScale().ToString());
		SaveFile.Write("Tile: " + MapDataVector_[i].Tile_.ToString());
		SaveFile.Write("End");
	}
}

void GlobalIOManager::Load(IOType _Type)
{
	Clear();

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
		{
			std::string TmpS;
			LoadFile.Read(TmpS);
			TmpData.MapObjType_ = MapObjType::Max;
		}
		{
			std::string TmpS;
			LoadFile.Read(TmpS);
		}
		LoadFile.Read(TmpData.Actor_);
		LoadFile.Read(TmpData.Tile_);

		MapDataVector_.push_back(TmpData);
	}
}

void GlobalIOManager::Clear()
{
	MapDataVector_.clear();
}
