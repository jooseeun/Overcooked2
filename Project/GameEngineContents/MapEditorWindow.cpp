#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "GamePlayLevel.h"

#include "CounterTop.h"

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
		//sprintf(Label, (AllUnSortActorName_[i]).c_str());

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
		//std::string Temp = UnSortActorList_[i]->GetNameCopy();
		//sprintf(Label, (Temp + "%d").c_str(), i);

		if (ImGui::Selectable(UnSortActorList_[i]->GetNameCopy().c_str(), SelectIndex == i))
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

		if (AllUnSortActorName_[SelectNameIndex] != "Collision")
		{
			GameEngineFBXRenderer* Renderer = Object->CreateComponent<GameEngineFBXRenderer>();
			Renderer->SetFBXMesh(AllUnSortActorName_[SelectNameIndex] + ".fbx", "Texture");
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
		}
		else
		{
			Object->SetName("Collision");
		}

		UnSortActorList_.push_back(Object);
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
		// 오브젝트 이름 입력
		//ImGui::Text("Name");
		//char Label[1024] = { 0 };
		//ImGui::InputText(Label, Label, IM_ARRAYSIZE(Label));
		//ObjectName_ = Label;

		//if (true == ImGui::Button("OK"))
		//{
		//    //for (int i = 0; i < UnSortActorList_.size(); ++i)
		//    //{
		//    //    UnSortActorList_[i]->SetName(ObjectName_);
		//    //    GameEngineFBXRenderer* Renderer = UnSortActorList_[i]->CreateComponent<GameEngineFBXRenderer>();
		//    //    Renderer->SetFBXMesh(ObjectName_ + ".fbx", "Texture");
		//    //}
		//}

		// Transform
		Position_ = UnSortActorList_[SelectIndex]->GetTransform().GetWorldPosition();
		ImGui::Text("Position");
		ImGui::DragFloat("Position.x", &Position_.x);
		ImGui::DragFloat("Position.y", &Position_.y);
		ImGui::DragFloat("Position.z", &Position_.z);

		if (true == ImGui::Button("Position Reset"))
		{
			Position_ = { 0.f, 0.f, 0.f };
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

	{
		static int Tile[2] = { 0, 0 };
		ImGui::DragInt2("TileXY", Tile);

		if (true == ImGui::Button("Tiled"))
		{
			Origins_[OriginIndex]->GetTransform().SetWorldRotation({ 0.f, 0.f });

			for (size_t Y = 0; Y < Tile[1]; ++Y)
			{
				for (size_t X = 0; X < Tile[0]; ++X)
				{
					GameEngineTextureRenderer* GridTile = Origins_[OriginIndex]->CreateComponent<GameEngineTextureRenderer>();
					GridTile->SetTexture("GridTile.png");
					GridTile->GetTransform().SetWorldMove({ X * 100.f, Y * 100.f });
					GridTile->GetTransform().SetWorldScale({ 100.f, 100.f });
				}
			}
		}
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
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();

			CurStaticMesh_->GetFBXMesh()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
			CurStaticMesh_->GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
			break;
		case 1:
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();

			CurStaticMesh_->GetFBXMesh()->SetFBXMesh("m_lorry_countertop_corner_01.fbx", "Texture");
			CurStaticMesh_->GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
			break;
		case 2:
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();

			CurStaticMesh_->GetFBXMesh()->SetFBXMesh("m_sk_countertop_no_edge_01.fbx", "Texture");
			CurStaticMesh_->GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
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