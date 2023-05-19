#include "PreCompile.h"
#include "MapDataNameLoader.h"

MapDataNameLoader::MapDataNameLoader()
{
}

MapDataNameLoader::~MapDataNameLoader()
{
}

void MapDataNameLoader::Load(std::vector<std::string>& _Destvector, std::string _FileName)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("SaveFiles");

	GameEngineFile LoadFile = (Dir.GetFullPath() + "\\" + _FileName + ".txt").c_str();

	// 문자열 가져오기
	std::string LoadS = "";
	LoadS = LoadFile.GetStringFstream();

	// \n 제거
	for (size_t i = 0; i < LoadS.size(); i++)
	{
		if (LoadS[i] == '\n')
		{
			LoadS.erase(i, 1);
			--i;
		}
	}

	// ; 단위로 잘라서 벡터에 저장
	std::istringstream SS(LoadS);
	while (getline(SS, LoadS, ';'))
	{
		_Destvector.push_back(LoadS);
	}
}

