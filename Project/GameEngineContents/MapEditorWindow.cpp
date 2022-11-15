#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "GamePlayLevel.h"
#include "GamePlayOriginObject.h"
#include "GamePlayStuff.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"
#include "Cooker.h"
#include "Sink.h"
#include "PlateReturn.h"

#include "Equipment_Plate.h"
#include "Equipment_FireExtinguisher.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Pot.h"
#include "Tool_CuttingBoard.h"

#include "Npc.h"
#include "Car.h"
#include "TrafficLight.h"
#include "Candle.h"

namespace
{
	//static mesh 간 간격 상수화
	constexpr float INTERVAL = 122.f;
}


MapEditorWindow::MapEditorWindow()
	: CurLevel_(nullptr)
	, LevelActor_()
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
				TmpData.ObjName_ = UnSortActorList_[i].lock()->GetName();
				TmpData.Pos_ = UnSortActorList_[i].lock()->GetTransform().GetWorldPosition();
				TmpData.Scale_ = UnSortActorList_[i].lock()->GetCollisionObject()->GetTransform().GetWorldScale();
				TmpData.Rot_ = UnSortActorList_[i].lock()->GetTransform().GetWorldRotation();
				TmpData.MapObjType_ = UnSortActorList_[i].lock()->GetMapObjType();
				
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
				OriginData.Transform_ = &Origins_[i].lock()->GetTransform();
				OriginData.Pos_ = Origins_[i].lock()->GetTransform().GetWorldPosition();
				OriginData.Rot_ = Origins_[i].lock()->GetTransform().GetWorldRotation();
				OriginData.Scale_ = Origins_[i].lock()->GetTransform().GetWorldScale();

				InputVector.push_back(OriginData);

				std::vector<std::weak_ptr<GamePlayStaticObject>>& DataActors = Origins_[i].lock()->GetStaticMeshInfo();

				for (size_t j = 0; j < DataActors.size(); j++)
				{
					MapData Data = { };

					Data.MapObjType_ = DataActors[j].lock()->GetStaticObjectType();
					Data.Transform_ = &DataActors[j].lock()->GetTransform();
					Data.Pos_ = DataActors[j].lock()->GetTransform().GetWorldPosition();
					Data.Rot_ = DataActors[j].lock()->GetTransform().GetWorldRotation();
					Data.Scale_ = DataActors[j].lock()->GetTransform().GetWorldScale();
					Data.Index_.z = static_cast<float>(i);

					if (nullptr != DataActors[j].lock()->GetStuff())
					{
						Data.Index_.y = static_cast<float>(DataActors[j].lock()->GetStuff()->GetToolInfoType());
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
			// 비어있지않다면
			if (false == UnSortActorList_.empty())
			{
				return;
			}

			GlobalIOManager::Load(IOType::UnsortMap, LevelIndex_);
			UnSortActorList_ = DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), CurLevel_);
		}

		else if (true == IsSort_)
		{
			GlobalIOManager::Load(IOType::SortMap, LevelIndex_);
			DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), CurLevel_);

			for (size_t i = 0; i < Origins_.size(); i++)
			{
				if (nullptr != Origins_[i].lock())
				{
					Origins_[i].lock()->Death();
					Origins_[i].reset();
				}
			}

			Origins_ = DataParser_.GetOrigins();
			SortActorList_ = Origins_[0].lock()->GetStaticMeshInfo();

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
				std::vector<std::weak_ptr<GamePlayOriginObject>>::iterator StartIter = Origins_.begin();

				for (StartIter = Origins_.begin(); StartIter != Origins_.end(); ++StartIter)
				{
					(*StartIter).lock()->Off();
				}
			}
		}

		//정렬된 오브젝트 배치
		if (true == ImGui::BeginTabItem("Sort"))
		{
			if (0 == Origins_.size())
			{
				std::weak_ptr<GamePlayOriginObject> Origin = CurLevel_->CreateActor<GamePlayOriginObject>();

				Origin.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });

				Origin.lock()->GetRenderer().lock()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
				Origin.lock()->GetRenderer().lock()->GetTransform().SetWorldScale({ 100, 100, 100 });

				Origins_.push_back(Origin);
			}

			else
			{
				std::weak_ptr<GamePlayOriginObject> Origin = Origins_.front();
				Origin.lock()->On();
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
				Prefabs_.push_back("Sink");
				Prefabs_.push_back("CounterTop_Wizard");
				//Prefabs_.push_back("Wizard_Sink");
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

				if (nullptr != LevelActor_.lock())
				{
					LevelActor_.lock()->Death();
					LevelActor_.reset();
				}

				LevelActor_ = CurLevel_->CreateActor<LevelActor>();

				switch (LevelIndex_)
				{
				case 0:
					LevelActor_.lock()->SetLevelMesh("1_1.FBX");
					break;

				case 1:
					LevelActor_.lock()->SetLevelMesh("1_2.FBX");
					break;

				case 2:
					LevelActor_.lock()->SetLevelMesh("1_3.FBX");
					break;

				case 3:
					LevelActor_.lock()->SetLevelMesh("1_4.FBX");
					break;

				default:
					LevelActor_.lock()->SetLevelMesh("1_1.FBX");
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
	static int SelectIndex = 0;
	static int CandleTypeIndex = 0;

	if (true == ImGui::Button("Clear")
		&& false == UnSortActorList_.empty())
	{
		for (size_t i = 0; i < UnSortActorList_.size(); i++)
		{
			UnSortActorList_[i].lock()->Death();
		}

		SelectIndex = 0;
		UnSortActorList_.clear();
	}

	// 만들 수 있는 오브젝트 리스트ds
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


	auto RendererType = magic_enum::enum_names<MapObjType>();
	const int Size = RendererType.size();
	static bool IsCheckType[Size] = { false };
	static MapObjType ObjectTypeIndex = MapObjType::Max;

	for (int i = 0; i < UnSortActorList_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		std::string Name = UnSortActorList_[i].lock()->GetNameCopy().c_str() + std::to_string(i);
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
 		//	for (size_t j = 0; j < RendererType.size(); j++)
			//{
			//	if (false != IsCheckType[j] && i != j)
			//	{
			//		IsCheckType[j] = false;
			//		break;
			//	}
			//}
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
			std::weak_ptr<Npc> Object = CurLevel_->CreateActor<Npc>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object.lock()->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
			break;
		case MapObjType::Car:
		{
			std::weak_ptr<Car> Object = CurLevel_->CreateActor<Car>();
			Object.lock()->GetTransform().SetWorldPosition({0.f, 0.f, 0.f});
			Object.lock()->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			UnSortActorList_.push_back(Object);
		}
			break;
		case MapObjType::TrafficLight:
		{
			std::weak_ptr<TrafficLight> Object = CurLevel_->CreateActor<TrafficLight>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object.lock()->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
			break;
		case MapObjType::Candle:
		{
			std::weak_ptr<Candle> Object = CurLevel_->CreateActor<Candle>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object.lock()->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
		//	Object.lock()->SetCandleTypeIndex(C);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Collision_Wall:
		{
			std::weak_ptr<GamePlayMapObject> Object = CurLevel_->CreateActor<GamePlayMapObject>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Collision_Floor:
		{
			std::weak_ptr<GamePlayFloor> Object = CurLevel_->CreateActor<GamePlayFloor>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, -49.f, 0.f });
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		default:
		{
			std::weak_ptr<GamePlayMapObject> Object = CurLevel_->CreateActor<GamePlayMapObject>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object.lock()->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
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
		UnSortActorList_[SelectIndex].lock()->Death();
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
		Position_ = UnSortActorList_[SelectIndex].lock()->GetTransform().GetWorldPosition();
		float4 RendererPos = UnSortActorList_[SelectIndex].lock()->GetFBXMesh()->GetTransform().GetLocalPosition();
		ImGui::Text("Position");
		ImGui::DragFloat("Position.x", &Position_.x);
		ImGui::DragFloat("Position.y", &Position_.y);
		ImGui::DragFloat("Position.z", &Position_.z);
		ImGui::DragFloat("RendererPosition.x", &RendererPos.x);
		ImGui::DragFloat("RendererPosition.y", &RendererPos.y);
		ImGui::DragFloat("RendererPosition.z", &RendererPos.z);
		ImGui::InputFloat4("Position", Position_.Arr1D);
		ImGui::InputFloat4("RendererPosition", RendererPos.Arr1D);

		if (true == ImGui::Button("Position Reset"))
		{
			if ("Collision_Floor" == UnSortActorList_[SelectIndex].lock()->GetName().substr(0, 15))
			{
				Position_ = { 0.f, -49.f, 0.f };
			}
			else
			{
				Position_ = { 0.f, 0.f, 0.f };
				RendererPos = { 0.f, 0.f, 0.f };
			}
		}
		UnSortActorList_[SelectIndex].lock()->GetTransform().SetWorldPosition(Position_);
		UnSortActorList_[SelectIndex].lock()->GetFBXMesh()->GetTransform().SetLocalPosition(RendererPos);

		Rotation_ = UnSortActorList_[SelectIndex].lock()->GetTransform().GetWorldRotation();
		ImGui::Text("Rotation");
		ImGui::DragFloat("Rotation.x", &Rotation_.x);
		ImGui::DragFloat("Rotation.y", &Rotation_.y);
		ImGui::DragFloat("Rotation.z", &Rotation_.z);

		ImGui::InputFloat4("Rotation_", Rotation_.Arr1D);

		if (true == ImGui::Button("Rotation Reset"))
		{
			Rotation_ = { 0.f, 0.f, 0.f };
		}
		UnSortActorList_[SelectIndex].lock()->GetTransform().SetWorldRotation(Rotation_);

		// Actor 크기는 1 1 1로 고정
		// 콜리전 기본 크기는 50 50 50
		CollisionScale_ = UnSortActorList_[SelectIndex].lock()->GetCollisionObject()->GetTransform().GetWorldScale();
		float4 Scale = UnSortActorList_[SelectIndex].lock()->GetTransform().GetWorldScale();
		ImGui::Text("Collision Scale");
		ImGui::DragFloat("Collision Scale.x", &CollisionScale_.x);
		ImGui::DragFloat("Collision Scale.y", &CollisionScale_.y);
		ImGui::DragFloat("Collision Scale.z", &CollisionScale_.z);

		ImGui::InputFloat4("Collision Scale", CollisionScale_.Arr1D);
		ImGui::InputFloat4("Scale", Scale.Arr1D);

		if (true == ImGui::Button("Collision Scale Reset"))
		{
			CollisionScale_ = { 1.f, 1.f, 1.f };
		}
		UnSortActorList_[SelectIndex].lock()->GetCollisionObject()->GetTransform().SetWorldScale(CollisionScale_);
		UnSortActorList_[SelectIndex].lock()->GetTransform().SetWorldScale(Scale);
	}

}

void MapEditorWindow::SortToolTab()
{
	ImGui::BeginChild("Origin List", ImVec2(150, 100), true);

	static int OriginIndex = 0;
	static int PrefabIndex = 0;
	static int ActorIndex = 0;

	auto ToolNames = magic_enum::enum_names<ToolInfo>();

	const int Size = ToolNames.size();
	static bool IsChecks_[Size] = { false };

	for (int i = 0; i < Origins_.size(); ++i)
	{
		char Label[1024] = { '\0' };
		std::string Name = "Origin(" + std::to_string(i) + ")";

		if (ImGui::Selectable(Name.c_str(), OriginIndex == i))
		{
			OriginIndex = i;
			ActorIndex = 0;

			SortActorList_.clear();

			SortActorList_ = Origins_[OriginIndex].lock()->GetStaticMeshInfo();

			for (size_t j = 0; j < ToolNames.size(); ++j)
			{
				IsChecks_[j] = false;

				if (0 == SortActorList_.size())
				{
					continue;
				}

				if (nullptr != SortActorList_[ActorIndex].lock()->GetStuff())
				{
					std::string_view CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType());

					if (ToolNames[j] == CurType.data())
					{
						IsChecks_[j] = true;
					}
				}
			}
		}
	}

	ImGui::EndChild();
	ImGui::SameLine();

	//기준 엑터 트랜스폼
	{
		float4 Pos = Origins_[OriginIndex].lock()->GetTransform().GetWorldPosition();

		float Float3[3] = { Pos.x, Pos.y, Pos.z };
		ImGui::DragFloat3("Position", Float3);
		Origins_[OriginIndex].lock()->GetTransform().SetWorldPosition({ Float3[0], Float3[1], Float3[2] });
	}

	if (ImGui::Button("Origin Create"))
	{
		std::weak_ptr<GamePlayOriginObject> Origin = CurLevel_->CreateActor<GamePlayOriginObject>();

		Origin.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });

		Origin.lock()->GetRenderer().lock()->GetTransform().SetWorldScale({ 100, 100, 100 });
		Origin.lock()->GetRenderer().lock()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");

		Origins_.push_back(Origin);
	}

	ImGui::Text("");

	ImGui::BeginChild("PrefabList", ImVec2(150, 100), true);

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

				if (nullptr != SortActorList_[ActorIndex].lock()->GetStuff())
				{
					std::string_view CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType());

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
		if (nullptr != SortActorList_[ActorIndex].lock()->GetStuff())
		{
			auto CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType());

			for (size_t i = 0; i < ToolNames.size(); ++i)
			{
				if (ToolNames[i] == CurType) 
				{
					if (false == IsChecks_[i])
					{
						SortActorList_[ActorIndex].lock()->GetStuff()->Death();
						SortActorList_[ActorIndex].lock()->SetStuff(nullptr);
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
						SortActorList_[ActorIndex].lock()->SetStuff(Plate);
					}
					break;
					case ToolInfo::FireExtinguisher:
					{
						std::shared_ptr<Equipment_FireExtinguisher> FireExtinguisher = CurLevel_->CreateActor<Equipment_FireExtinguisher>();
						SortActorList_[ActorIndex].lock()->SetStuff(FireExtinguisher);
					}
					break;
					case ToolInfo::FryingPan:
					{
						std::shared_ptr<Equipment_FryingPan> FryingPan = CurLevel_->CreateActor<Equipment_FryingPan>();
						SortActorList_[ActorIndex].lock()->SetStuff(FryingPan);
					}
					break;
					case ToolInfo::Pot:
					{
						std::shared_ptr<Equipment_Pot> Pot = CurLevel_->CreateActor<Equipment_Pot>();
						SortActorList_[ActorIndex].lock()->SetStuff(Pot);
					}
					break;
					case ToolInfo::CuttingBoard:
					{
						std::shared_ptr<Tool_CuttingBoard> CuttingBoard = CurLevel_->CreateActor<Tool_CuttingBoard>();
						SortActorList_[ActorIndex].lock()->SetStuff(CuttingBoard);
					}
					break;
					}

					float4 ToolPos = SortActorList_[ActorIndex].lock()->GetToolPos();
					SortActorList_[ActorIndex].lock()->GetStuff()->GetTransform().SetWorldPosition(ToolPos);
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
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Normal);
			Object.lock()->SetConterTopMesh(CounterTopType::Normal);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop);
		}
		break;
		case 1:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Corner);
			Object.lock()->SetConterTopMesh(CounterTopType::Corner);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_Corner);
		}
		break;
		case 2:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::NoEdge);
			Object.lock()->SetConterTopMesh(CounterTopType::NoEdge);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_NoEdge);
		}
		break;
		case 3:
			CurStaticMesh_ = CurLevel_->CreateActor<TrashCan>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::TrashCan);
			break;
		case 4:
			CurStaticMesh_ = CurLevel_->CreateActor<Servicehatch>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Servicehatch);
			break;
		case 5:
			CurStaticMesh_ = CurLevel_->CreateActor<PlateReturn>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::PlateReturn);
			break;
		case 6:
			CurStaticMesh_ = CurLevel_->CreateActor<Cooker>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Cooker);
			break;
		case 7:
			CurStaticMesh_ = CurLevel_->CreateActor<Sink>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Sink);
			break;
		case 8:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Wizard);
			Object.lock()->SetConterTopMesh(CounterTopType::Wizard);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_WiZard);
		}
		break;
		}

		//기준 엑터의 자식으로 둔다.
		CurStaticMesh_.lock()->SetParent(Origins_[OriginIndex].lock());

		CurStaticMesh_.lock()->GetTransform().SetWorldPosition(Origins_[OriginIndex].lock()->GetTransform().GetWorldPosition());
		CurStaticMesh_.lock()->GetTransform().SetWorldMove({ Index[0] * (-INTERVAL), 0.f, Index[1] * INTERVAL });

		SortActorList_.push_back(CurStaticMesh_);
		Origins_[OriginIndex].lock()->GetStaticMeshInfo().push_back(CurStaticMesh_);

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
		SortActorList_[ActorIndex].lock()->Death();
		SortActorList_.erase(SortActorList_.begin() + ActorIndex);

		std::vector<std::weak_ptr<GamePlayStaticObject>>& DataVector = Origins_[OriginIndex].lock()->GetStaticMeshInfo();

		for (size_t i = 0; i < DataVector.size(); ++i)
		{
			if (DataVector[i].lock()->IsDeath()
				|| nullptr == DataVector[i].lock())
			{
				DataVector.erase(DataVector.begin() + i);
				break;
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
		SortActorList_[ActorIndex].lock()->GetTransform().SetAddWorldRotation({0.f, 90.f, 0.f});
	}

	ImGui::EndTabItem();
}
