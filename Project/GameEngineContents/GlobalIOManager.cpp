#include "PreCompile.h"
#include "GlobalIOManager.h"
#include <GameEngineBase/magic_enum.hpp>

std::vector<MapData> GlobalIOManager::MapDataVector_;

GlobalIOManager::GlobalIOManager()
{
}

GlobalIOManager::~GlobalIOManager()
{
}

void GlobalIOManager::AddMapData(MapData _Data)
{
	MapDataVector_.push_back(_Data);
}

void GlobalIOManager::Save(IOType _Type)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	auto IOTypeName = magic_enum::enum_name(_Type);
	GameEngineFile SaveFile = (Dir.GetFullPath() + "\\" + static_cast<std::string>(IOTypeName) + "Data.txt").c_str();
	SaveFile.Open(OpenMode::Write);

	std::string SaveString = "";

	for (size_t i = 0; i < MapDataVector_.size(); i++)
	{
		auto ObjTypeName = magic_enum::enum_name(MapDataVector_[i].MapObjType_);
		SaveString += "Type:" + static_cast<std::string>(ObjTypeName) + ";\n";

		if (nullptr != MapDataVector_[i].Transform_)
		{
			SaveString += "Pos:" + MapDataVector_[i].Transform_->GetWorldPosition().ToDataString() + ";\n";
			SaveString += "Rot:" + MapDataVector_[i].Transform_->GetWorldRotation().ToDataString() + ";\n";
			SaveString += "Scale:" + MapDataVector_[i].Transform_->GetWorldScale().ToDataString() + ";\n";
		}
		else
		{
			SaveString += "Pos:" + MapDataVector_[i].Pos_.ToDataString() + ";\n";
			SaveString += "Rot:" + MapDataVector_[i].Rot_.ToDataString() + ";\n";
			SaveString += "Scale:" + MapDataVector_[i].Scale_.ToDataString() + ";\n";
		}

		SaveString += "Tile:" + MapDataVector_[i].Tile_.ToDataString() + ";\n\n";
	}

	SaveFile.WriteString(SaveString);
}

void GlobalIOManager::Load(IOType _Type)
{
	Clear();

	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	auto IOTypeName = magic_enum::enum_name(_Type);
	GameEngineFile LoadFile = (Dir.GetFullPath() + "\\" + static_cast<std::string>(IOTypeName) + "Data.txt").c_str();
	LoadFile.Open(OpenMode::Read);

	std::string LoadS = "";
	LoadS = LoadFile.GetString();

	// \n 제거
	while (std::string::npos != LoadS.find("\n"))
	{
		size_t StartIndex = LoadS.find("\n");
		LoadS.erase(StartIndex, 1);
	}

	// ; 단위로 문자를 잘라서 벡터에 저장
	std::vector<std::string> TmpVector;
	std::istringstream ss(LoadS);
	while (getline(ss, LoadS, ';'))
	{
		TmpVector.push_back(LoadS);
	}

	// 저장한 문자열을 값으로 변경
	int DataValues = 5;
	for (int i = 0; i < TmpVector.size() / DataValues; i++)
	{
		MapData TmpData = {};

		{ // type
			int CurIndex_ = (DataValues * i) + 0;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				auto ObjType = magic_enum::enum_cast<MapObjType>(TmpVector[CurIndex_]);
				if (ObjType.has_value())
				{
					TmpData.MapObjType_ = ObjType.value();
				}
			}
		}
		{ // pos
			int CurIndex_ = (DataValues * i) + 1;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
				TmpData.Pos_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2])};
			}
		}
		{ // rot
			int CurIndex_ = (DataValues * i) + 2;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
				TmpData.Rot_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
			}
		}
		{ // scale
			int CurIndex_ = (DataValues * i) + 3;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
				TmpData.Scale_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
			}
		}
		{ // Tile
			int CurIndex_ = (DataValues * i) + 4;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
				TmpData.Tile_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
			}
		}

		MapDataVector_.push_back(TmpData);
	}

	int a = 0;
}

void GlobalIOManager::Clear()
{
	MapDataVector_.clear();
}
