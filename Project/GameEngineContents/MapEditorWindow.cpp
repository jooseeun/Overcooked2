#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "GamePlayLevel.h"
#include "GamePlayOriginObject.h"
#include "GamePlayStuff.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"
#include "Cooker.h"
#include "PlateReturn.h"

#include "Equipment_Plate.h"
#include "Equipment_FireExtinguisher.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Pot.h"
#include "Tool_CuttingBoard.h"

#include "Npc.h"
#include "Car.h"
#include "TrafficLight.h"

namespace
{
	//static mesh 간 간격 상수화
	constexpr float INTERVAL = 122.f;
}


MapEditorWindow::MapEditorWindow()
	: CurLevel_(nullptr)
	, LevelActor_(nullptr)
	, ObjectName_("Actor_")
	, DataParser_{}
	, IsUnSort_(false)
	, IsSort_(false)
	, LevelIndex_(0)
	, IsUnSortLoad_(false)
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
			// 저장
			if (false == GlobalIOManager::GetMapDataVector().empty())
			{
				GlobalIOManager::Clear();
			}

			MapData TmpData = {};
			for (size_t i = 0; i < UnSortActorList_.size(); i++)
			{
				TmpData.ObjName_ = UnSortActorList_[i]->GetName();
				TmpData.Pos_ = UnSortActorList_[i]->GetTransform().GetWorldPosition();
				TmpData.Scale_ = UnSortActorList_[i]->GetCollisionObject()->GetTransform().GetWorldScale();
				TmpData.Rot_ = UnSortActorList_[i]->GetTransform().GetWorldRotation();
				TmpData.MapObjType_ = UnSortActorList_[i]->GetMapObjType();
				
				GlobalIOManager::AddMapData(TmpData);
			}

			GlobalIOManager::Save(IOType::UnsortMap);
			GlobalIOManager::Clear();

		}

		else if (true == IsSort_)
		{
			std::vector<MapData>& InputVector = GlobalIOManager::GetMapDataVector();
			GlobalIOManager::Clear();

			for (size_t i = 0; i < Origins_.size(); ++i)
			{
				MapData OriginData = { };

				OriginData.MapObjType_ = MapObjType::Origin;
				OriginData.Transform_ = &Origins_[i]->GetTransform();
				OriginData.Pos_ = Origins_[i]->GetTransform().GetWorldPosition();
				OriginData.Rot_ = Origins_[i]->GetTransform().GetWorldRotation();
				OriginData.Scale_ = Origins_[i]->GetTransform().GetWorldScale();

				InputVector.push_back(OriginData);

				std::vector<std::shared_ptr<GamePlayStaticObject>>& DataActors = Origins_[i]->GetStaticMeshInfo();

				for (size_t j = 0; j < DataActors.size(); j++)
				{
					MapData Data = { };

					Data.MapObjType_ = DataActors[j]->GetStaticObjectType();
					Data.Transform_ = &DataActors[j]->GetTransform();
					Data.Pos_ = DataActors[j]->GetTransform().GetWorldPosition();
					Data.Rot_ = DataActors[j]->GetTransform().GetWorldRotation();
					Data.Scale_ = DataActors[j]->GetTransform().GetWorldScale();
					Data.Index_.z = static_cast<float>(i);

					if (nullptr != DataActors[j]->GetStuff())
					{
						Data.Index_.y = static_cast<float>(DataActors[j]->GetStuff()->GetToolInfoType());
					}

					InputVector.push_back(Data);
				}
			}

			GlobalIOManager::Save(IOType::SortMap, LevelIndex_);
			GlobalIOManager::Clear();

			GameEngineDebug::OutPutString(LevelIndex_ + "번째 정렬된 맵 데이터 파일을 저장했습니다.");
		}
	}

	ImGui::SameLine();

	if (true == ImGui::Button("MapData Load"))
	{
		if (true == IsUnSort_)
		{

			GlobalIOManager::Load(IOType::UnsortMap, LevelIndex_);
			DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), CurLevel_);

			std::vector<MapData>& Vector = GlobalIOManager::GetMapDataVector();
			for (size_t i = 0; i < Vector.size(); i++)
			{
				switch (Vector[i].MapObjType_)
				{
				case MapObjType::Npc:
				{
					std::shared_ptr<Npc> Object = CurLevel_->CreateActor<Npc>();
					Object->GetTransform().SetWorldPosition(Vector[i].Pos_);
					Object->GetCollisionObject()->GetTransform().SetWorldScale(Vector[i].Scale_);
					Object->GetTransform().SetWorldRotation(Vector[i].Rot_);
					Object->SetMapObjectMesh(Vector[i].ObjName_, Vector[i].MapObjType_);
					Object->SetMapObjType(Vector[i].MapObjType_);
					Object->SetName(Vector[i].ObjName_);
					UnSortActorList_.push_back(Object);
				}
				break;
				case MapObjType::Car:
				{
					std::shared_ptr<Car> Object = CurLevel_->CreateActor<Car>();
					Object->GetTransform().SetWorldPosition(Vector[i].Pos_);
					Object->GetCollisionObject()->GetTransform().SetWorldScale(Vector[i].Scale_);
					Object->GetTransform().SetWorldRotation(Vector[i].Rot_);
					Object->SetMapObjectMesh(Vector[i].ObjName_, Vector[i].MapObjType_);
					Object->SetMapObjType(Vector[i].MapObjType_);
					Object->SetName(Vector[i].ObjName_);
					UnSortActorList_.push_back(Object);
				}
				break;
				case MapObjType::TrafficLight:
				{
					std::shared_ptr<TrafficLight> Object = CurLevel_->CreateActor<TrafficLight>();
					Object->GetTransform().SetWorldPosition(Vector[i].Pos_);
					Object->GetCollisionObject()->GetTransform().SetWorldScale(Vector[i].Scale_);
					Object->GetTransform().SetWorldRotation(Vector[i].Rot_);
					Object->SetMapObjectMesh(Vector[i].ObjName_, Vector[i].MapObjType_);
					Object->SetMapObjType(Vector[i].MapObjType_);
					Object->SetName(Vector[i].ObjName_);
					UnSortActorList_.push_back(Object);
				}
				break;
				case MapObjType::Collision_Wall:
				{
					std::shared_ptr<GamePlayMapObject> Object = CurLevel_->CreateActor<GamePlayMapObject>();
					Object->GetTransform().SetWorldPosition(Vector[i].Pos_);
					Object->GetCollisionObject()->GetTransform().SetWorldScale(Vector[i].Scale_);
					Object->GetTransform().SetWorldRotation(Vector[i].Rot_);
					Object->SetMapObjType(Vector[i].MapObjType_);
					Object->SetName(Vector[i].ObjName_);
					UnSortActorList_.push_back(Object);
				}
				break;
				case MapObjType::Collision_Floor:
				{
					std::shared_ptr<GamePlayFloor> Object = CurLevel_->CreateActor<GamePlayFloor>();
					Object->GetTransform().SetWorldPosition(Vector[i].Pos_);
					Object->GetCollisionObject()->GetTransform().SetWorldScale(Vector[i].Scale_);
					Object->GetTransform().SetWorldRotation(Vector[i].Rot_);
					Object->SetMapObjType(Vector[i].MapObjType_);
					Object->SetName(Vector[i].ObjName_);
					UnSortActorList_.push_back(Object);
				}
				break;
				default:
				{
					std::shared_ptr<GamePlayMapObject> Object = CurLevel_->CreateActor<GamePlayMapObject>();
					Object->GetTransform().SetWorldPosition(Vector[i].Pos_);
					Object->GetCollisionObject()->GetTransform().SetWorldScale(Vector[i].Scale_);
					Object->GetTransform().SetWorldRotation(Vector[i].Rot_);
					Object->SetMapObjectMesh(Vector[i].ObjName_, Vector[i].MapObjType_);
					Object->SetMapObjType(Vector[i].MapObjType_);
					Object->SetName(Vector[i].ObjName_);
					UnSortActorList_.push_back(Object);
				}
				break;
				}
			}
		}

		else if (true == IsSort_)
		{
			GlobalIOManager::Load(IOType::SortMap, LevelIndex_);

			SortActorList_ = DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), CurLevel_);

			for (size_t i = 0; i < Origins_.size(); i++)
			{
				if (nullptr != Origins_[i])
				{
					Origins_[i]->Death();
					Origins_[i] = nullptr;
				}
			}

			Origins_ = DataParser_.GetOrigins();

			GameEngineDebug::OutPutString(LevelIndex_ + "번째 정렬된 맵 데이터 파일을 불러왔습니다.");
		}
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
				std::vector<std::shared_ptr<GamePlayOriginObject>>::iterator StartIter = Origins_.begin();

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
				std::shared_ptr<GamePlayOriginObject> Origin = CurLevel_->CreateActor<GamePlayOriginObject>();

				Origin->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });

				Origin->GetRenderer()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
				Origin->GetRenderer()->GetTransform().SetWorldScale({ 100, 100, 100 });

				Origins_.push_back(Origin);
			}

			else
			{
				std::shared_ptr<GamePlayOriginObject> Origin = Origins_.front();
				Origin->On();
			}

			SortToolTab();

			if (0 == Prefabs_.size())
			{
				Prefabs_.push_back("CounterTop");
				Prefabs_.push_back("CounterTop_Corner");
				Prefabs_.push_back("CounterTop_NoEdge");
				Prefabs_.push_back("TrashCan");
				Prefabs_.push_back("Servicehatch");
				Prefabs_.push_back("PlateReturn");
				Prefabs_.push_back("Cooker");
			}
		}

		ImGui::EndTabBar();
	}
}

void MapEditorWindow::ShowLevelSelectTable()
{
	ImGui::BeginChild("LevelList", ImVec2(150, 200), true);

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

			if (ImGui::Selectable(Temp.c_str(), LevelIndex_ == i))
			{
				LevelIndex_ = i;

				if (nullptr != LevelActor_)
				{
					LevelActor_->Death();
					LevelActor_ = nullptr;
				}

				LevelActor_ = CurLevel_->CreateActor<LevelActor>();

				switch (LevelIndex_)
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
	ImGui::BeginChild("ActorNameGroup", ImVec2(250, 250), true);
	ImGui::Text("ActorNameList");
	ImGui::BeginChild("AllUnSortActorName", ImVec2(230, 230), true);

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
	ImGui::BeginChild("ActorGroup", ImVec2(250, 250), true);
	ImGui::Text("Created ActorList");
	ImGui::BeginChild("UnSortActorList", ImVec2(230, 230), true);

	static int SelectIndex = 0;

	auto RendererType = magic_enum::enum_names<MapObjType>();
	const int Size = RendererType.size();
	static bool IsCheckType[Size] = { false };
	static MapObjType ObjectTypeIndex = MapObjType::Max;

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

	for (size_t i = 0; i < RendererType.size(); ++i)
	{
		if (i <= 10)
		{
			continue;
		}
		MapObjType Type = static_cast<MapObjType>(i);

		if (MapObjType::Max != Type)
		{
			// 체크 상황 계속 확인중
			ImGui::Checkbox(RendererType[i].data(), &IsCheckType[i]);
		}
	}

	for (size_t i = 0; i < RendererType.size(); i++)
	{
		if (false != IsCheckType[i])
		{
			// 체크박스 중 true인 애가 있다 -> 타입 지정
			ObjectTypeIndex = static_cast<MapObjType>(i);
		}
	}

	// 오브젝트 생성 
	if (true == ImGui::Button("Create"))
	{
		switch (ObjectTypeIndex)
		{
		case MapObjType::Npc:
		{
			std::shared_ptr<Npc> Object = CurLevel_->CreateActor<Npc>();
			Object->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
			break;
		case MapObjType::Car:
		{
			std::shared_ptr<Car> Object = CurLevel_->CreateActor<Car>();
			Object->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
			UnSortActorList_.push_back(Object);
		}
			break;
		case MapObjType::TrafficLight:
		{
			std::shared_ptr<TrafficLight> Object = CurLevel_->CreateActor<TrafficLight>();
			Object->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
			break;
		case MapObjType::Collision_Wall:
		{
			std::shared_ptr<GamePlayMapObject> Object = CurLevel_->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Collision_Floor:
		{
			std::shared_ptr<GamePlayFloor> Object = CurLevel_->CreateActor<GamePlayFloor>();
			Object->GetTransform().SetWorldPosition({ 0.f, -49.f, 0.f });
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		default:
		{
			std::shared_ptr<GamePlayMapObject> Object = CurLevel_->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
			break;
		}
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

	// Transform
	if (false == UnSortActorList_.empty())
	{
		Position_ = UnSortActorList_[SelectIndex]->GetTransform().GetWorldPosition();
		float4 RendererPos = UnSortActorList_[SelectIndex]->GetFBXMesh()->GetTransform().GetLocalPosition();
		ImGui::Text("Position");
		ImGui::DragFloat("Position.x", &Position_.x);
		ImGui::DragFloat("Position.y", &Position_.y);
		ImGui::DragFloat("Position.z", &Position_.z);

		ImGui::InputFloat4("Position", Position_.Arr1D);

		if (true == ImGui::Button("Position Reset"))
		{
			if ("Collision_Floor" == UnSortActorList_[SelectIndex]->GetName().substr(0, 15))
			{
				Position_ = { 0.f, -49.f, 0.f };
			}
			else
			{
				Position_ = { 0.f, 0.f, 0.f };
				RendererPos = { 0.f, 0.f, 0.f };
			}
		}
		UnSortActorList_[SelectIndex]->GetTransform().SetWorldPosition(Position_);
		UnSortActorList_[SelectIndex]->GetFBXMesh()->GetTransform().SetLocalPosition(RendererPos);

		Rotation_ = UnSortActorList_[SelectIndex]->GetTransform().GetWorldRotation();
		ImGui::Text("Rotation");
		ImGui::DragFloat("Rotation.x", &Rotation_.x);
		ImGui::DragFloat("Rotation.y", &Rotation_.y);
		ImGui::DragFloat("Rotation.z", &Rotation_.z);

		ImGui::InputFloat4("Rotation_", Rotation_.Arr1D);

		if (true == ImGui::Button("Rotation Reset"))
		{
			Rotation_ = { 0.f, 0.f, 0.f };
		}
		UnSortActorList_[SelectIndex]->GetTransform().SetWorldRotation(Rotation_);

		// Actor 크기는 1 1 1로 고정
		// 콜리전 기본 크기는 50 50 50
		CollisionScale_ = UnSortActorList_[SelectIndex]->GetCollisionObject()->GetTransform().GetWorldScale();
		ImGui::Text("Collision Scale");
		ImGui::DragFloat("Collision Scale.x", &CollisionScale_.x);
		ImGui::DragFloat("Collision Scale.y", &CollisionScale_.y);
		ImGui::DragFloat("Collision Scale.z", &CollisionScale_.z);

		ImGui::InputFloat4("Collision Scale", CollisionScale_.Arr1D);

		if (true == ImGui::Button("Collision Scale Reset"))
		{
			CollisionScale_ = { 1.f, 1.f, 1.f };
		}
		UnSortActorList_[SelectIndex]->GetCollisionObject()->GetTransform().SetWorldScale(CollisionScale_);
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
		std::shared_ptr<GamePlayOriginObject> Origin = CurLevel_->CreateActor<GamePlayOriginObject>();

		Origin->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });

		Origin->GetRenderer()->GetTransform().SetWorldScale({ 100, 100, 100 });
		Origin->GetRenderer()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");

		Origins_.push_back(Origin);
	}

	ImGui::Text("");

	ImGui::BeginChild("PrefabList", ImVec2(150, 100), true);

	static int PrefabIndex = 0;

	for (int i = 0; i < Prefabs_.size(); ++i)
	{
		char Label[1024] = { '\0' };

		if (ImGui::Selectable(Prefabs_[i].c_str(), PrefabIndex == i))
		{
			PrefabIndex = i;
		}
	}

	ImGui::EndChild();
	ImGui::SameLine();

	ImGui::BeginChild("SortActorList", ImVec2(150, 100), true);

	static int ActorIndex = 0;

	auto ToolNames = magic_enum::enum_names<ToolInfo>();

	const int Size = ToolNames.size();
	static bool IsChecks_[Size] = { false };

	for (int i = 0; i < SortActorList_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		std::string Name = "Actor(" + std::to_string(i) + ")";

		if (ImGui::Selectable(Name.c_str(), ActorIndex == i))
		{
			ActorIndex = i;

			for (size_t j = 0; j < ToolNames.size(); ++j)
			{
				IsChecks_[j] = false;

				if (nullptr != SortActorList_[ActorIndex]->GetStuff())
				{
					std::string_view CurType = magic_enum::enum_name(SortActorList_[ActorIndex]->GetStuff()->GetToolInfoType());

					if (ToolNames[j] == CurType.data())
					{
						IsChecks_[j] = true;
					}
				}
			}
		}
	}

	ImGui::EndChild();
	ImGui::Text("");

	if (0 < SortActorList_.size())
	{
		if (nullptr != SortActorList_[ActorIndex]->GetStuff())
		{
			auto CurType = magic_enum::enum_name(SortActorList_[ActorIndex]->GetStuff()->GetToolInfoType());

			for (size_t i = 0; i < ToolNames.size(); ++i)
			{
				if (ToolNames[i] == CurType) 
				{
					if (false == IsChecks_[i])
					{
						SortActorList_[ActorIndex]->GetStuff()->Death();
						SortActorList_[ActorIndex]->SetStuff(nullptr);
					}

					continue;
				}

				IsChecks_[i] = false;
			}
		}

		else
		{
			for (size_t i = 0; i < ToolNames.size(); ++i)
			{
				if (true == IsChecks_[i])
				{
					ToolInfo ToolType = static_cast<ToolInfo>(i);

					switch (ToolType)
					{
					case ToolInfo::Plate:
					{
						//부모로 둔다
						std::shared_ptr<Equipment_Plate> Plate = CurLevel_->CreateActor<Equipment_Plate>();
						SortActorList_[ActorIndex]->SetStuff(Plate);

						//SortActorList_[ActorIndex]->GetStuff()->SetToolInfoType(ToolInfo::Plate);
					}
					break;
					case ToolInfo::FireExtinguisher:
					{
						std::shared_ptr<Equipment_FireExtinguisher> FireExtinguisher = CurLevel_->CreateActor<Equipment_FireExtinguisher>();
						SortActorList_[ActorIndex]->SetStuff(FireExtinguisher);

						//SortActorList_[ActorIndex]->GetStuff()->SetToolInfoType(ToolInfo::FireExtinguisher);
					}
					break;
					case ToolInfo::FryingPan:
					{
						std::shared_ptr<Equipment_FryingPan> FryingPan = CurLevel_->CreateActor<Equipment_FryingPan>();
						SortActorList_[ActorIndex]->SetStuff(FryingPan);

						//SortActorList_[ActorIndex]->GetStuff()->SetToolInfoType(ToolInfo::FryingPan);
					}
					break;
					case ToolInfo::Pot:
					{
						std::shared_ptr<Equipment_Pot> Pot = CurLevel_->CreateActor<Equipment_Pot>();
						SortActorList_[ActorIndex]->SetStuff(Pot);

						//SortActorList_[ActorIndex]->GetStuff()->SetToolInfoType(ToolInfo::Pot);
					}
					break;
					case ToolInfo::CuttingBoard:
					{
						std::shared_ptr<Tool_CuttingBoard> CuttingBoard = CurLevel_->CreateActor<Tool_CuttingBoard>();
						SortActorList_[ActorIndex]->SetStuff(CuttingBoard);

						//SortActorList_[ActorIndex]->GetStuff()->SetToolInfoType(ToolInfo::CuttingBoard);
					}
					break;
					}

					float4 ToolPos = SortActorList_[ActorIndex]->GetToolPos();
					SortActorList_[ActorIndex]->GetStuff()->GetTransform().SetWorldPosition(ToolPos);
				}
			}
		}

		for (size_t i = 0; i < ToolNames.size(); ++i)
		{
			ToolInfo Type = static_cast<ToolInfo>(i);

			if (ToolInfo::None != Type && ToolInfo::Max != Type)
			{
				ImGui::Checkbox(ToolNames[i].data(), &IsChecks_[i]);
			}
		}
	}

	ImGui::Text("");

	static int Index[2] = { 0, 0 };
	ImGui::DragInt2("Index", Index);

	if (true == ImGui::Button("Create"))
	{
		switch (PrefabIndex)
		{
		case 0:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_);

			Object->SetCounterTopType(CounterTopType::Normal);
			Object->SetConterTopMesh(CounterTopType::Normal);

			Object->SetStaticObjectType(MapObjType::CounterTop);
		}
		break;
		case 1:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_);

			Object->SetCounterTopType(CounterTopType::Corner);
			Object->SetConterTopMesh(CounterTopType::Corner);

			Object->SetStaticObjectType(MapObjType::CounterTop_Corner);
		}
		break;
		case 2:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_);

			Object->SetCounterTopType(CounterTopType::NoEdge);
			Object->SetConterTopMesh(CounterTopType::NoEdge);

			Object->SetStaticObjectType(MapObjType::CounterTop_NoEdge);
		}
		break;
		case 3:
			CurStaticMesh_ = CurLevel_->CreateActor<TrashCan>();
			CurStaticMesh_->SetStaticObjectType(MapObjType::TrashCan);
			break;
		case 4:
			CurStaticMesh_ = CurLevel_->CreateActor<Servicehatch>();
			CurStaticMesh_->SetStaticObjectType(MapObjType::Servicehatch);
			break;
		case 5:
			CurStaticMesh_ = CurLevel_->CreateActor<PlateReturn>();
			CurStaticMesh_->SetStaticObjectType(MapObjType::PlateReturn);
			break;
		case 6:
			CurStaticMesh_ = CurLevel_->CreateActor<Cooker>();
			CurStaticMesh_->SetStaticObjectType(MapObjType::Cooker);
			break;
		}

		//기준 엑터의 자식으로 둔다.
		CurStaticMesh_->SetParent(Origins_[OriginIndex]);

		CurStaticMesh_->GetTransform().SetWorldPosition(Origins_[OriginIndex]->GetTransform().GetWorldPosition());
		CurStaticMesh_->GetTransform().SetWorldMove({ Index[0] * (-INTERVAL), 0.f, Index[1] * INTERVAL });

		SortActorList_.push_back(CurStaticMesh_);
		Origins_[OriginIndex]->GetStaticMeshInfo().push_back(CurStaticMesh_);

		ActorIndex = static_cast<int>(SortActorList_.size() - 1);

		for (size_t j = 0; j < ToolNames.size(); ++j)
		{
			IsChecks_[j] = false;
		}
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Delete")
		&& 0 < SortActorList_.size()
		&& ActorIndex < SortActorList_.size())
	{
		SortActorList_[ActorIndex]->Death();
		SortActorList_.erase(SortActorList_.begin() + ActorIndex);

		std::vector<std::shared_ptr<GamePlayStaticObject>>& DataVector = Origins_[OriginIndex]->GetStaticMeshInfo();

		for (size_t i = 0; i < DataVector.size(); ++i)
		{
			if (DataVector[i]->IsDeath()
				|| nullptr == DataVector[i])
			{
				DataVector.erase(DataVector.begin() + i);
			}
		}

		if (SortActorList_.size() <= ActorIndex)
		{
			--ActorIndex;

			if (0 > ActorIndex)
			{
				ActorIndex = 0;
			}
		}
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



