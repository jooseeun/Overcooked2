#include "PreCompile.h"
#include "GlobalIOManager.h"
#include <GameEngineBase/magic_enum.hpp>

std::vector<MapData> GlobalIOManager::MapDataVector_;
MeshData GlobalIOManager::MeshData_;

GlobalIOManager::GlobalIOManager()
{
}

GlobalIOManager::~GlobalIOManager()
{
}

void GlobalIOManager::SetMeshData(MeshData _Data)
{
	MeshData_ = _Data;
}

void GlobalIOManager::AddMapData(MapData _Data)
{
	MapDataVector_.push_back(_Data);
}

bool GlobalIOManager::Save(IOType _Type, std::string _AddName)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	auto IOTypeName = magic_enum::enum_name(_Type);
	GameEngineFile SaveFile = (Dir.GetFullPath() + "\\" + static_cast<std::string>(IOTypeName) + "Data" + _AddName + ".txt").c_str();
	SaveFile.Open(OpenMode::Write);

	std::string SaveString = "";

	if (_Type == IOType::UnsortMap || _Type == IOType::SortMap) // 맵 세이브
	{
		for (size_t i = 0; i < MapDataVector_.size(); i++)
		{
			SaveString += "{ \n";
			SaveString += "Name:" + MapDataVector_[i].ObjName_ + ";\n";

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

			SaveString += "Index:" + MapDataVector_[i].Index_.ToDataString() + ";\n";
			SaveString += "}\n\n";
		}
	}
	else if (_Type == IOType::Mesh) // 메쉬 세이브
	{
		SaveString += "{ \n";
		SaveString += "MeshName:" + MeshData_.PreviewMeshName_ + ";\n";

		size_t count_ = MeshData_.PreviewMeshInfo_.size();
		SaveString += "MeshInfoCount:" + std::to_string(count_) + ";\n";
		for (size_t j = 0; j < count_; j++)
		{
			SaveString += "Path:" + MeshData_.PreviewMeshInfo_[j].DifTexturePath_ + ";\n";
			SaveString += "Mat:" + MeshData_.PreviewMeshInfo_[j].DifTextureName_ + ";\n";
		}
		SaveString += "}\n\n";
	}

	SaveFile.WriteString(SaveString);
	return true;
}

bool GlobalIOManager::Load(IOType _Type, std::string _AddName)
{
	Clear();

	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	bool FindFile = 0;
	auto IOTypeName = magic_enum::enum_name(_Type);
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();
	for (int i = 0; i < AllFile.size(); ++i)
	{
		std::string FileName = AllFile[i].GetFileName();
		std::string FbxName = static_cast<std::string>(IOTypeName) + "Data" + _AddName + ".txt";
		if (FileName.find(FbxName) != std::string::npos)
		{
			FindFile = true;
		}
	}

	if (false == FindFile)
	{
		return false;
	}

	GameEngineFile LoadFile = (Dir.GetFullPath() + "\\" + static_cast<std::string>(IOTypeName) + "Data" + _AddName + ".txt").c_str();
	LoadFile.Open(OpenMode::Read);

	std::string LoadS = "";
	LoadS = LoadFile.GetString();

	// \n, 공백, 중괄호 제거
	for (size_t i = 0; i < LoadS.size(); i++)
	{
		if (LoadS[i] == ' ' || LoadS[i] == '\n' || LoadS[i] == '{' || LoadS[i] == '}')
		{
			LoadS.erase(i, 1);
			--i;
		}
	}

	// ; 단위로 문자를 잘라서 벡터에 저장
	std::vector<std::string> TmpVector;
	std::istringstream ss(LoadS);
	while (getline(ss, LoadS, ';'))
	{
		TmpVector.push_back(LoadS);
	}

	// 저장한 문자열을 값으로 변경
	if (_Type == IOType::UnsortMap || _Type == IOType::SortMap) // 맵 로드
	{
		int DataValues = 6;
		for (int i = 0; i < TmpVector.size() / DataValues; i++)
		{
			MapData TmpData = {};

			{ // name
				int CurIndex_ = (DataValues * i) + 0;
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					TmpData.ObjName_ = TmpVector[CurIndex_];
				}
			}
			{ // type
				int CurIndex_ = (DataValues * i) + 1;
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
				int CurIndex_ = (DataValues * i) + 2;
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
					TmpData.Pos_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
				}
			}
			{ // rot
				int CurIndex_ = (DataValues * i) + 3;
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
					TmpData.Rot_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
				}
			}
			{ // scale
				int CurIndex_ = (DataValues * i) + 4;
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
					TmpData.Scale_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
				}
			}
			{ // Tile
				int CurIndex_ = (DataValues * i) + 5;
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					std::vector<std::string> TmpDataVector = GameEngineString::Split(TmpVector[CurIndex_], ',');
					TmpData.Index_ = { std::stof(TmpDataVector[0]), std::stof(TmpDataVector[1]), std::stof(TmpDataVector[2]) };
				}
			}

			MapDataVector_.push_back(TmpData);
		}
	}
	else if (_Type == IOType::Mesh)  // 메쉬 로드
	{
		MeshData TmpData = {};

		{ // Mesh
			int CurIndex_ = 0;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				TmpData.PreviewMeshName_ = TmpVector[CurIndex_];
			}
		}

		int TmpCount = 0;
		{ // count
			int CurIndex_ = 1;
			size_t FindIndex = TmpVector[CurIndex_].find(":");
			if (std::string::npos != FindIndex)
			{
				TmpVector[CurIndex_].erase(0, FindIndex + 1);
				TmpCount = std::stoi(TmpVector[CurIndex_]);
			}
		}

		// info
		for (int j = 0; j < TmpCount; j++)
		{
			SubSetMeshData TmpInfo;
			{
				int CurIndex_ = 2 + (2 * j);
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					TmpInfo.DifTexturePath_ = TmpVector[CurIndex_];
				}
			}

			{
				int CurIndex_ = 3 + (2 * j);
				size_t FindIndex = TmpVector[CurIndex_].find(":");
				if (std::string::npos != FindIndex)
				{
					TmpVector[CurIndex_].erase(0, FindIndex + 1);
					TmpInfo.DifTextureName_ = TmpVector[CurIndex_];
				}
			}

			TmpData.PreviewMeshInfo_.push_back(TmpInfo);
		}

		MeshData_ = TmpData;
	}

	MapDataVector_;
	MeshData_;
	int a = 0;

	return true;
}

void GlobalIOManager::Clear()
{
	MapDataVector_.clear();
	MeshData_ = {};
}
