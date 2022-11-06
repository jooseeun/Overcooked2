#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "GamePlayLevel.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"


MapEditorWindow::MapEditorWindow()
	: CurLevel_(nullptr)
	, ObjectName_("Actor_")
{

}

MapEditorWindow::~MapEditorWindow()
{

}

void MapEditorWindow::Initialize(GameEngineLevel* _Level)
{

}

void MapEditorWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowLevelSelectTable();

	ImGui::SameLine();
	ImGui::Checkbox("UnSort", &IsUnSort_);
	ImGui::SameLine();
	ImGui::Checkbox("Sort", &IsSort_);

	if (true == ImGui::Button("MapData Save"))
	{
		if (true == IsUnSort_
			&& true == IsSort_)
		{
			return;
		}

		if (true == IsUnSort_)
		{
			//std::vector<MapData>& DataVector = GlobalIOManager::GetMapDataVector();

			//MapData Data = {};

			//Data.MapObjType_ = MapObjType::Collision_Wall;
			//Data.Transform_ = nullptr;
			//Data.Pos_ = float4{ 100, 100, 100 };
			//Data.Rot_ = float4{ 0, 0, 0 };
			//Data.Scale_ = float4{ 1, 1, 1 };
			//Data.Tile_ = float4{ 1, 1, 1 };

			//DataVector.push_back(Data);

			//GlobalIOManager::Save(IOType::Map);
			//GlobalIOManager::Clear();
		}

		else if (true == IsSort_)
		{
			/*GlobalIOManager::GetMapDataVector();
			GlobalIOManager::Save(IOType::Mesh);
			GlobalIOManager::Clear();*/
		}
	}

	ImGui::SameLine();

	if (true == ImGui::Button("MapData Load"))
	{
		GlobalIOManager::Load(IOType::Mesh);
	}

	ImGui::Text("");

	if (true == ImGui::BeginTabBar("ToolTab"))
	{
		//정렬되지 않은 오브젝트 배치
		if (true == ImGui::BeginTabItem("UnSort"))
		{
			UnSortToolTab();

			//Sort 탭을 잘못 눌렀을 때 생성된 기준 엑터들 숨기기
			if (0 < Origins_.size())
			{
				std::vector<GamePlayMapObject*>::iterator StartIter = Origins_.begin();

				for (StartIter = Origins_.begin(); StartIter != Origins_.end(); ++StartIter)
				{
					(*StartIter)->Off();
				}
			}

			if (true == AllUnSortActorName_.empty())
			{
				AllUnSortActorName_.push_back("Chef");
				AllUnSortActorName_.push_back("NPC_Beard_Green_01");
				AllUnSortActorName_.push_back("Collision_Wall");
				AllUnSortActorName_.push_back("Collision_Floor");
				//	AllUnSortActorName_.push_back("m_sk_countertop_01");
			}
		}

		//정렬된 오브젝트 배치
		if (true == ImGui::BeginTabItem("Sort"))
		{
			if (0 == Origins_.size())
			{
				GamePlayMapObject* Origin = CurLevel_->CreateActor<GamePlayMapObject>();

				Origin->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });

				Origin->GetFBXMesh()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
				Origin->GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

				Origins_.push_back(Origin);
			}

			else
			{
				GamePlayMapObject* Origin = Origins_.front();
				Origin->On();
			}

			SortToolTab();

			if (0 == Prefabs_.size())
			{
				Prefabs_.push_back("CounterTop");
				Prefabs_.push_back("CounterTop_Corner");
				Prefabs_.push_back("CounterTop_NoEdge");
				Prefabs_.push_back("Bin");
				Prefabs_.push_back("Servicehatch");
			}
		}

		ImGui::EndTabBar();
	}
}

void MapEditorWindow::ShowLevelSelectTable()
{
	ImGui::BeginChild("LevelList", ImVec2(150, 200), true);

	static int SelectIndex = 0;

	std::vector<GameEngineLevel*> AllLevels = GameEngineCore::GetAllLevelVector();

	std::vector<GamePlayLevel*> AllStages;

	for (size_t i = 0; i < AllLevels.size(); i++)
	{
		GamePlayLevel* Stage = dynamic_cast<GamePlayLevel*>(AllLevels[i]);

		if (nullptr == Stage)
		{
			continue;
		}

		AllStages.push_back(Stage);
	}

	for (int i = 0; i < AllStages.size(); ++i)
	{
		if (nullptr != AllStages[i])
		{
			char Label[1024] = { '\0' };
			std::string Temp = AllStages[i]->GetNameCopy();

			//sprintf(Label, Temp.c_str());

			if (ImGui::Selectable(Temp.c_str(), SelectIndex == i))
			{
				SelectIndex = i;

				if (nullptr != LevelActor_)
				{
					LevelActor_->Death();
					LevelActor_ = nullptr;
				}

				LevelActor_ = CurLevel_->CreateActor<LevelActor>();

				switch (SelectIndex)
				{
				case 0:
					LevelActor_->SetLevelMesh("1_1.FBX");
					break;

				case 1:
					LevelActor_->SetLevelMesh("1_2.FBX");
					break;

				case 2:
					LevelActor_->SetLevelMesh("1_3.FBX");
					break;

				case 3:
					LevelActor_->SetLevelMesh("1_4.FBX");
					break;

				default:
					LevelActor_->SetLevelMesh("1_1.FBX");
					break;
				}
			}
		}
	}

	ImGui::EndChild();
	ImGui::SameLine();
}

void MapEditorWindow::UnSortToolTab()
{
	// 만들 수 있는 오브젝트 리스트
	ImGui::BeginChild("ActorNameGroup", ImVec2(180, 250), true);
	ImGui::Text("ActorNameList");
	ImGui::BeginChild("AllUnSortActorName", ImVec2(150, 200), true);

	static int SelectNameIndex = 0;

	for (int i = 0; i < AllUnSortActorName_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		if (ImGui::Selectable((AllUnSortActorName_[i]).c_str(), SelectNameIndex == i))
		{
			SelectNameIndex = i;
		}
	}

	ImGui::EndChild();
	ImGui::EndChild();
	ImGui::SameLine();

	// 현재 생성된 오브젝트 리스트
	ImGui::BeginChild("ActorGroup", ImVec2(180, 250), true);
	ImGui::Text("Created ActorList");
	ImGui::BeginChild("UnSortActorList", ImVec2(150, 200), true);

	static int SelectIndex = 0;

	for (int i = 0; i < UnSortActorList_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		std::string Name = UnSortActorList_[i]->GetNameCopy().c_str() + std::to_string(i);
		if (ImGui::Selectable(Name.c_str(), SelectIndex == i))
		{
			SelectIndex = i;
		}
	}

	ImGui::EndChild();
	ImGui::EndChild();
	ImGui::EndTabItem();
	//

	// 오브젝트 생성 
	if (true == ImGui::Button("Create"))
	{
		GamePlayMapObject* Object = CurLevel_->CreateActor<GamePlayMapObject>();
		Object->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
		Object->GetTransform().SetLocalScale({ 1.f, 1.f, 1.f });
		Object->SetName("UnNamed");

		if (AllUnSortActorName_[SelectNameIndex] == "Collision_Wall")
		{
			Object->SetName("Collision_Wall");
		}
		else if (AllUnSortActorName_[SelectNameIndex] == "Collision_Floor")
		{
			Object->SetName("Collision_Floor");
			Object->GetTransform().SetWorldPosition({ 0.f, -0.9f, 0.f });
		}
		else
		{
			GameEngineFBXStaticRenderer* Renderer = Object->CreateComponent<GameEngineFBXStaticRenderer>();
			Renderer->SetFBXMesh(AllUnSortActorName_[SelectNameIndex] + ".fbx", "Texture");
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
		}

		{
			MapData TmpData = {};

			if (AllUnSortActorName_[SelectNameIndex] == "Collision_Wall")
			{
				TmpData.MapObjType_ = MapObjType::Collision;
			}
			else
			{
				TmpData.MapObjType_ = MapObjType::Npc_Static;
			}
			TmpData.Transform_ = &Object->GetTransform();

			GlobalIOManager::AddMapData(TmpData);
		}

		UnSortActorList_.push_back(Object);

		GlobalIOManager::GetMapDataVector;
	}

	ImGui::SameLine();

	// 오브젝트 삭제
	if (true == ImGui::Button("Delete")
		&& false == UnSortActorList_.empty())
	{
		UnSortActorList_[SelectIndex]->Death();
		UnSortActorList_.erase(UnSortActorList_.begin() + SelectIndex);

		if (UnSortActorList_.size() <= SelectIndex)
		{
			SelectIndex = (int)UnSortActorList_.size() - 1;
			if (SelectIndex <= -1)
			{
				SelectIndex = 0;
			}
		}
	}

	if (false == UnSortActorList_.empty())
	{
		// Transform
		Position_ = UnSortActorList_[SelectIndex]->GetTransform().GetWorldPosition();
		ImGui::Text("Position");
		ImGui::DragFloat("Position.x", &Position_.x);
		ImGui::DragFloat("Position.y", &Position_.y);
		ImGui::DragFloat("Position.z", &Position_.z);

		if (true == ImGui::Button("Position Reset"))
		{
			if ("Collision_Floor" == UnSortActorList_[SelectIndex]->GetName().substr(0, 15))
			{
				Position_ = { 0.f, -0.9f, 0.f };
			}
			else
			{
				Position_ = { 0.f, 0.f, 0.f };
			}
		}
		UnSortActorList_[SelectIndex]->GetTransform().SetWorldPosition(Position_);

		Rotation_ = UnSortActorList_[SelectIndex]->GetTransform().GetWorldRotation();
		ImGui::Text("Rotation");
		ImGui::DragFloat("Rotation.x", &Rotation_.x);
		ImGui::DragFloat("Rotation.y", &Rotation_.y);
		ImGui::DragFloat("Rotation.z", &Rotation_.z);

		if (true == ImGui::Button("Rotation Reset"))
		{
			Rotation_ = { 0.f, 0.f, 0.f };
		}
		UnSortActorList_[SelectIndex]->GetTransform().SetWorldRotation(Rotation_);

		Scale_ = UnSortActorList_[SelectIndex]->GetTransform().GetWorldScale();
		ImGui::Text("Scale");
		ImGui::DragFloat("Scale.x", &Scale_.x);
		ImGui::DragFloat("Scale.y", &Scale_.y);
		ImGui::DragFloat("Scale.z", &Scale_.z);

		if (true == ImGui::Button("Scale Reset"))
		{
			Scale_ = { 1.f, 1.f, 1.f };
		}
		UnSortActorList_[SelectIndex]->GetTransform().SetWorldScale(Scale_);
	}
}

void MapEditorWindow::SortToolTab()
{
	ImGui::BeginChild("Origin List", ImVec2(150, 100), true);

	static int OriginIndex = 0;

	for (int i = 0; i < Origins_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		std::string Name = "Origin(" + std::to_string(i) + ")";

		if (ImGui::Selectable(Name.c_str(), OriginIndex == i))
		{
			OriginIndex = i;
		}
	}

	ImGui::EndChild();
	ImGui::SameLine();

	//기준 엑터 트랜스폼
	{
		float4 Pos = Origins_[OriginIndex]->GetTransform().GetWorldPosition();

		float Float3[3] = { Pos.x, Pos.y, Pos.z };
		ImGui::DragFloat3("Position", Float3);
		Origins_[OriginIndex]->GetTransform().SetWorldPosition({ Float3[0], Float3[1], Float3[2] });
	}

	if (ImGui::Button("Origin Create"))
	{
		GamePlayMapObject* Origin = CurLevel_->CreateActor<GamePlayMapObject>();

		Origin->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });

		Origin->GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
		Origin->GetFBXMesh()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");

		Origins_.push_back(Origin);
	}

	ImGui::Text("");

	ImGui::BeginChild("PrefabList", ImVec2(150, 100), true);

	static int SelectIndex = 0;

	for (int i = 0; i < Prefabs_.size(); ++i)
	{
		char Label[1024] = { '\0' };

		if (ImGui::Selectable(Prefabs_[i].c_str(), SelectIndex == i))
		{
			SelectIndex = i;
		}
	}

	ImGui::EndChild();
	ImGui::SameLine();

	ImGui::BeginChild("SortActorList", ImVec2(150, 100), true);

	static int ActorIndex = 0;

	for (int i = 0; i < SortActorList_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		std::string Name = "Actor(" + std::to_string(i) + ")";

		if (ImGui::Selectable(Name.c_str(), ActorIndex == i))
		{
			ActorIndex = i;
		}
	}

	ImGui::EndChild();
	ImGui::Text("");

	static int Index[2] = { 0, 0 };
	ImGui::DragInt2("Index", Index);

	if (true == ImGui::Button("Create"))
	{
		switch (SelectIndex)
		{
		case 0:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			CounterTop* Object = dynamic_cast<CounterTop*>(CurStaticMesh_);

			Object->SetCounterTopType(CounterTopType::Normal);
			Object->SetConterTopMesh(CounterTopType::Normal);
		}
		break;
		case 1:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			CounterTop* Object = dynamic_cast<CounterTop*>(CurStaticMesh_);

			Object->SetCounterTopType(CounterTopType::Corner);
			Object->SetConterTopMesh(CounterTopType::Corner);
		}
		break;
		case 2:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			CounterTop* Object = dynamic_cast<CounterTop*>(CurStaticMesh_);

			Object->SetCounterTopType(CounterTopType::NoEdge);
			Object->SetConterTopMesh(CounterTopType::NoEdge);
		}
		break;
		case 3:
			CurStaticMesh_ = CurLevel_->CreateActor<TrashCan>();
			break;
		case 4:
			CurStaticMesh_ = CurLevel_->CreateActor<Servicehatch>();
			break;
		}

		//기준 엑터의 자식으로 둔다.
		CurStaticMesh_->SetParent(Origins_[OriginIndex]);

		CurStaticMesh_->GetTransform().SetWorldPosition(Origins_[OriginIndex]->GetTransform().GetWorldPosition());
		CurStaticMesh_->GetTransform().SetWorldMove({ Index[0] * (-122.f), 0.f, Index[1] * 122.f });

		SortActorList_.push_back(CurStaticMesh_);
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Delete")
		&& 0 < SortActorList_.size()
		&& ActorIndex < SortActorList_.size())
	{
		SortActorList_[ActorIndex]->Death();
		SortActorList_.erase(SortActorList_.begin() + ActorIndex);
	}

	ImGui::Text("");

	if (true == ImGui::Button("Rotate")
		&& 0 < SortActorList_.size()
		&& ActorIndex < SortActorList_.size())
	{
		SortActorList_[ActorIndex]->GetTransform().SetAddWorldRotation({ 0.f, 90.f, 0.f });
	}

	ImGui::EndTabItem();
}


//세이브할 때 사용
// 
//void SortSave()
//{
//	for (size_t i = 0; i < Origins_.size(); i++)
//	{
//		//기준 엑터(타일의 부모)가 몇 개인지
//		//엑터 수만큼 타일맵 정보 저장
//		std::vector<std::vector<class GamePlayStaticObject*>> TileMap_;
//		//그 다음 쓰기
//	}
//}
// 
//std::list<GamePlayStaticObject*> StaticMeshList = Origins_[OriginIndex]->GetConvertChilds<GamePlayStaticObject>();