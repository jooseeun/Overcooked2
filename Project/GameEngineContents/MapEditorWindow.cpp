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
		}

		//정렬된 오브젝트 배치
		if (true == ImGui::BeginTabItem("Sort"))
		{
			if (nullptr == Origin_)
			{
				Origin_ = CurLevel_->CreateActor<GamePlayMapObject>();

				Origin_->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
				Origin_->GetTransform().SetWorldScale({ 100, 100, 100 });
				Origin_->GetFBXMesh()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
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

			sprintf(Label, Temp.c_str());

			if (ImGui::Selectable(Label, SelectIndex == i))
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
		sprintf(Label, (AllUnSortActorName_[i]).c_str());

		if (ImGui::Selectable(Label, SelectNameIndex == i))
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
		std::string Temp = UnSortActorList_[i]->GetNameCopy();
		sprintf(Label, (Temp + "%d").c_str(), i);

		if (ImGui::Selectable(Label, SelectIndex == i))
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
	if (true == ImGui::Button("CreateOrigin")
		&& nullptr == Origin_)
	{
		Origin_ = CurLevel_->CreateActor<GamePlayMapObject>();

		Origin_->GetTransform().SetWorldPosition({ 0, 1.f, 0 });
		Origin_->GetTransform().SetWorldScale({ 100, 100, 100 });
	}

	if (nullptr != Origin_)
	{
		float4 Pos = Origin_->GetTransform().GetWorldPosition();

		ImGui::Text("Position", &Pos.x, &Pos.y, &Pos.z);
		ImGui::DragFloat("x", &Pos.x);
		ImGui::DragFloat("y", &Pos.y);
		ImGui::DragFloat("z", &Pos.z);

		Origin_->GetTransform().SetWorldPosition(Pos);

		ImGui::Text("");

		static int TileX = 0;
		static int TileY = 0;

		ImGui::Text("TileScale", &TileX, &TileY);
		ImGui::DragInt("TileX", &TileX);
		ImGui::DragInt("TileY", &TileY);


		ImGui::BeginChild("PrefabList", ImVec2(150, 100), true);

		static int SelectIndex = 0;

		for (int i = 0; i < Prefabs_.size(); ++i)
		{
			char Label[1024] = { '\0' };
			std::string Temp = Prefabs_[i];

			sprintf(Label, Temp.c_str());

			if (ImGui::Selectable(Label, SelectIndex == i))
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
			std::string Temp = "Actor_";

			sprintf(Label, (Temp + "%d").c_str(), i);

			if (ImGui::Selectable(Label, ActorIndex == i))
			{
				ActorIndex = i;
			}
		}

		ImGui::EndChild();

		ImGui::Text("");

		if (true == ImGui::Button("Tiled"))
		{
			Origin_->GetTransform().SetWorldRotation({ 0.f, 0.f });

			for (size_t Y = 0; Y < TileY; ++Y)
			{
				for (size_t X = 0; X < TileX; ++X)
				{
					GameEngineTextureRenderer* GridTile = Origin_->CreateComponent<GameEngineTextureRenderer>();
					GridTile->SetTexture("GridTile.png");
					GridTile->GetTransform().SetWorldMove({ X * 100.f, Y * 100.f });
					GridTile->GetTransform().SetWorldScale({ 100.f, 100.f });
				}
			}

			ImGui::Text("");
		}

		static int IndexX = 0;
		static int IndexY = 0;

		ImGui::Text("Index", &IndexX, &IndexY);
		ImGui::DragInt("IndexX", &IndexX);
		ImGui::DragInt("IndexY", &IndexY);

		if (true == ImGui::Button("Create"))
		{
			if (true)
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
				default:
					break;
				}
			}

			CurStaticMesh_->GetTransform().SetWorldPosition(Origin_->GetTransform().GetWorldPosition());
			CurStaticMesh_->GetTransform().SetWorldMove({ IndexX * (-122.f), 0.f, IndexY * 120.f });

			SortActorList_.push_back(CurStaticMesh_);
		}

		ImGui::Text("");

		if (true == ImGui::Button("Rotate"))
		{
			SortActorList_[ActorIndex]->GetTransform().SetAddWorldRotation({ 0.f, 90.f, 0.f });
		}
	}	

	ImGui::EndTabItem();
}