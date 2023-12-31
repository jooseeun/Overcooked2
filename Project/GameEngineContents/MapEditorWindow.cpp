#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "GamePlayLevel.h"
#include "GamePlayOriginObject.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"
#include "Cooker.h"
#include "Sink.h"
#include "PlateReturn.h"
#include "FoodBox.h"
#include "Rail.h"
#include "Dispenser.h"
#include "Cannon.h"
#include "Button.h"
#include "Oven.h"

#include "Equipment_Plate.h"
#include "Equipment_FireExtinguisher.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Pot.h"
#include "Equipment_Bowl.h"
#include "Equipment_Steamer.h"
#include "Tool_CuttingBoard.h"
#include "Mixer.h"

#include "Npc.h"
#include "Car.h"
#include "TrafficLight.h"
#include "Candle.h"
#include "Lift.h"
#include "Portal.h"
#include "IceBlock.h"
#include "IcePlatform.h"

#include "LoadingData.h"
#include "GlobalGameData.h"

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
	, IsCandleCheckBox_(false)
	, IsFoodBox_(false)
{
}

MapEditorWindow::~MapEditorWindow()
{
}

void MapEditorWindow::Initialize(GameEngineLevel* _Level)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Mesh");
	Dir.Move("Level");
	Dir.Move("1_1");
	Dir.Move("SortObject");
	Dir.Move("CounterTop");

	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_sk_countertop_01.FBX"));
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
				if (UnSortActorList_[i].lock()->GetMapObjType() == MapObjType::Candle)
				{
					std::weak_ptr<Candle> Object = std::dynamic_pointer_cast<Candle>(UnSortActorList_[i].lock());
					TmpData.Index_.x = static_cast<float>(Object.lock()->GetCandleTypeIndex());
				}

				GlobalIOManager::AddMapData(TmpData);
			}

			GlobalIOManager::Save(IOType::UnsortMap, LevelIndex_);
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
						if (nullptr != DataActors[j].lock()->GetMoveable())
						{
							Data.Index_.y = static_cast<float>(DataActors[j].lock()->GetMoveable()->GetToolInfoType());
						}
						else
						{
							Data.Index_.y = static_cast<float>(DataActors[j].lock()->GetStuff()->GetToolInfoType());
						}
					}
					std::weak_ptr<FoodBox> Food = std::dynamic_pointer_cast<FoodBox>(DataActors[j].lock());

					if (nullptr != Food.lock())
					{
						Data.Index_.x = static_cast<float>(Food.lock()->GetFoodType());
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
			/*if (0 < Origins_.size())
			{
				std::vector<std::weak_ptr<GamePlayOriginObject>>::iterator StartIter = Origins_.begin();

				for (StartIter = Origins_.begin(); StartIter != Origins_.end(); ++StartIter)
				{
					(*StartIter).lock()->Off();
				}
			}*/
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
				Prefabs_.push_back("FoodBox_Normal");
				Prefabs_.push_back("FoodBox_Winter");
				Prefabs_.push_back("Sink_Wizard");
				Prefabs_.push_back("Rail");
				Prefabs_.push_back("CounterTop_Winter");
				Prefabs_.push_back("Cannon");
				Prefabs_.push_back("Button");
				Prefabs_.push_back("Oven");
				Prefabs_.push_back("CounterMixer_Kevin");
				Prefabs_.push_back("CounterMixer_Winter");
				Prefabs_.push_back("Dispenser_Type1");
				Prefabs_.push_back("Dispenser_Type2");
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
					LoadingData::GetFunc("1-" + std::to_string(LevelIndex_ + 1))();
					LevelActor_.lock()->SetLevelMesh("1_1.FBX");
					GlobalGameData::SetCurStage("1-1");
					break;

				case 1:
					LoadingData::GetFunc("1-" + std::to_string(LevelIndex_ + 1))();
					LevelActor_.lock()->SetLevelMesh("1_2.FBX");
					GlobalGameData::SetCurStage("1-2");

					break;

				case 2:
					LoadingData::GetFunc("1-" + std::to_string(LevelIndex_ + 1))();
					LevelActor_.lock()->SetLevelMesh("1_3.FBX");
					GlobalGameData::SetCurStage("1-3");
					break;

				case 3:
					LoadingData::GetFunc("1-" + std::to_string(LevelIndex_ + 1))();
					LevelActor_.lock()->SetLevelMesh("1_4.FBX");
					GlobalGameData::SetCurStage("1-4");
					break;

				case 4:
					LoadingData::GetFunc("2-1")();
					LevelActor_.lock()->SetLevelMesh("2_1.FBX");
					GlobalGameData::SetCurStage("2-1");
					break;
				default:
					LevelActor_.lock()->SetLevelMesh("1_1.FBX");
					GlobalGameData::SetCurStage("1-1");
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
	auto CandleMoveType = magic_enum::enum_names<CandleType>();
	const size_t CandleSize = CandleMoveType.size();
	static bool IsCheckCandle[CandleSize] = { false };

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

	// 만들 수 있는 오브젝트 리스트
	ImGui::BeginChild("ActorNameGroup", ImVec2(210, 210), true);
	ImGui::Text("ActorNameList");
	ImGui::BeginChild("AllUnSortActorName", ImVec2(180, 180), true);

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
	ImGui::BeginChild("ActorGroup", ImVec2(210, 210), true);
	ImGui::Text("Created ActorList");
	ImGui::BeginChild("UnSortActorList", ImVec2(180, 180), true);

	auto RendererType = magic_enum::enum_names<MapObjType>();
	const size_t Size = RendererType.size();
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

	ImGui::BeginChild("MapObjType", ImVec2(210, 210), true);

	for (size_t i = 0; i < RendererType.size(); ++i)
	{
		if (i < static_cast<size_t>(MapObjType::Pigeon_Grounded))
		{
			continue;
		}

		MapObjType Type = static_cast<MapObjType>(i);

		if (MapObjType::Max != Type)
		{
			// 체크 상황 계속 확인중
			ImGui::Checkbox(RendererType[i].data(), &IsCheckType[i]);

			if (Type == MapObjType::Candle && true == IsCheckType[i])
			{
				IsCandleCheckBox_ = true;
			}
			else if (Type != MapObjType::Candle && true == IsCheckType[i])
			{
				IsCandleCheckBox_ = false;
			}
		}
	}

	for (size_t i = 0; i < RendererType.size(); i++)
	{
		if (false != IsCheckType[i])
		{
			ObjectTypeIndex = static_cast<MapObjType>(i);
		}
	}

	ImGui::EndChild();

	if (true == IsCandleCheckBox_)
	{
		ImGui::SameLine();
		ImGui::BeginChild("CandleType", ImVec2(210, 210), true);

		for (size_t i = 0; i < CandleMoveType.size(); ++i)
		{
			CandleType Type = static_cast<CandleType>(i);

			if (CandleType::Max != Type)
			{
				// 체크 상황 계속 확인중
				ImGui::Checkbox(CandleMoveType[i].data(), &IsCheckCandle[i]);
			}
			if (false != IsCheckCandle[i])
			{
				CandleTypeIndex = static_cast<int>(i);
			}
		}

		ImGui::EndChild();
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
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
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
			Object.lock()->SetCandleTypeIndex(CandleTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Lift:
		{
			std::weak_ptr<Lift> Object = CurLevel_->CreateActor<Lift>();
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, 0.f, 0.f });
			Object.lock()->SetMapObjectMesh(AllUnSortActorName_[SelectNameIndex], ObjectTypeIndex);
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
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
		case MapObjType::Collision_DeadZone:
		{
			std::weak_ptr<GamePlayFloor> Object = CurLevel_->CreateActor<GamePlayFloor>();
			Object.lock()->SetCollisionOrder(CollisionOrder::DeadZone);
			Object.lock()->GetTransform().SetWorldPosition({ 0.f, -200.f, 0.f });
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Portal_Blue:
		{
			std::weak_ptr<Portal> Object = CurLevel_->CreateActor<Portal>();
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetPortalMesh(MapObjType::Portal_Blue);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Portal_Purple:
		{
			std::weak_ptr<Portal> Object = CurLevel_->CreateActor<Portal>();
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetPortalMesh(MapObjType::Portal_Purple);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::IceBlock:
		{
			std::weak_ptr<IceBlock> Object = CurLevel_->CreateActor<IceBlock>();
			auto Type = magic_enum::enum_cast<IceBlockType>(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetIceBlockType(Type.value());
			Object.lock()->SetIceBlockMesh(Type.value());
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::IcePlatform:
		{
			std::weak_ptr<IcePlatform> Object = CurLevel_->CreateActor<IcePlatform>();
			Object.lock()->SetName(AllUnSortActorName_[SelectNameIndex]);
			Object.lock()->SetMapObjType(ObjectTypeIndex);
			UnSortActorList_.push_back(Object);
		}
		break;
		default:	// 클래스 따로 만들지 않은 애들
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
			SelectIndex = static_cast<int>(UnSortActorList_.size()) - 1;
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
		ImGui::Text("Position");
		ImGui::DragFloat3("Drag Position", Position_.Arr1D);
		ImGui::InputFloat3("Input Position", Position_.Arr1D);

		if (true == ImGui::Button("Position Reset"))
		{
			if ("Collision_Floor" == UnSortActorList_[SelectIndex].lock()->GetName().substr(0, 15))
			{
				Position_ = { 0.f, -49.f, 0.f };
			}
			else
			{
				Position_ = { 0.f, 0.f, 0.f };
			}
		}
		UnSortActorList_[SelectIndex].lock()->GetTransform().SetWorldPosition(Position_);

		Rotation_ = UnSortActorList_[SelectIndex].lock()->GetTransform().GetWorldRotation();
		ImGui::Text("Rotation");
		ImGui::DragFloat3("Drag Rotation", Rotation_.Arr1D);
		ImGui::InputFloat3("Input Rotation", Rotation_.Arr1D);

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
		ImGui::DragFloat3("Drag Collision Scale", CollisionScale_.Arr1D);
		ImGui::InputFloat3("Input Collision Scale", CollisionScale_.Arr1D);

		if (true == ImGui::Button("Collision Scale Reset"))
		{
			CollisionScale_ = { 50.f, 50.f, 50.f };
		}
		UnSortActorList_[SelectIndex].lock()->GetCollisionObject()->GetTransform().SetWorldScale(CollisionScale_);
	}
}

void MapEditorWindow::SortToolTab()
{
	ImGui::BeginChild("Origin List", ImVec2(150, 100), true);

	static int OriginIndex = 0;
	static int PrefabIndex = 0;
	static int ActorIndex = 0;

	auto ToolNames = magic_enum::enum_names<ToolInfo>();

	const size_t Size = ToolNames.size();
	static bool IsChecks_[Size] = { false };

	auto FoodNames = magic_enum::enum_names<IngredientType>();

	const size_t FoodSize = FoodNames.size();
	static bool IsFoods_[FoodSize] = { false };

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
				IsFoodBox_ = false;
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

		Origin.lock()->GetRenderer().lock()->SetFBXMesh("m_sk_countertop_01.fbx", "Texture");
		Origin.lock()->GetRenderer().lock()->GetTransform().SetWorldScale({ 100, 100, 100 });

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
				IsFoodBox_ = false;
				IsChecks_[j] = false;

				if (nullptr != SortActorList_[ActorIndex].lock()->GetStuff())
				{
					std::string_view CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType());

					if (ToolNames[j] == CurType.data())
					{
						IsChecks_[j] = true;
					}
					else if (nullptr != SortActorList_[ActorIndex].lock()->GetMoveable())
					{
						CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetMoveable()->GetToolInfoType());

						if (ToolNames[j] == CurType.data())
						{
							IsChecks_[j] = true;
						}
					}

					std::weak_ptr<FoodBox> Food = std::dynamic_pointer_cast<FoodBox>(SortActorList_[ActorIndex].lock());

					if (nullptr != Food.lock())
					{
						IsFoodBox_ = true;
					}
				}
			}
		}
	}

	ImGui::EndChild();
	ImGui::Text("");

	if (0 < SortActorList_.size())
	{
		if (nullptr != SortActorList_[ActorIndex].lock()->GetStuff() && (SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard || SortActorList_[ActorIndex].lock()->GetMoveable() != nullptr))
		{
			auto CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType());

			if (SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType() == ToolInfo::None)
			{
				CurType = magic_enum::enum_name(SortActorList_[ActorIndex].lock()->GetMoveable()->GetToolInfoType());
			}

			if (SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard || SortActorList_[ActorIndex].lock()->GetMoveable()->GetToolInfoType() != ToolInfo::None)
			{
				for (size_t i = 0; i < ToolNames.size(); ++i)
				{
					if (ToolNames[i] == CurType)
					{
						if (false == IsChecks_[i])
						{	
							if (SortActorList_[ActorIndex].lock()->GetStuff()->GetToolInfoType() == ToolInfo::CuttingBoard)
							{
								SortActorList_[ActorIndex].lock()->GetStuff()->Death();
								SortActorList_[ActorIndex].lock()->ReSetStuff();
							}
							else
							{
								SortActorList_[ActorIndex].lock()->GetMoveable_TakeOut()->Death();
							}
						}

						continue;
					}
					IsChecks_[i] = false;
				}
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
						SortActorList_[ActorIndex].lock()->SetMoveable(Plate);
					}
					break;
					case ToolInfo::FireExtinguisher:
					{
						std::shared_ptr<Equipment_FireExtinguisher> FireExtinguisher = CurLevel_->CreateActor<Equipment_FireExtinguisher>();
						SortActorList_[ActorIndex].lock()->SetMoveable(FireExtinguisher);
					}
					break;
					case ToolInfo::FryingPan:
					{
						std::shared_ptr<Equipment_FryingPan> FryingPan = CurLevel_->CreateActor<Equipment_FryingPan>();
						SortActorList_[ActorIndex].lock()->SetMoveable(FryingPan);
					}
					break;
					case ToolInfo::Pot:
					{
						std::shared_ptr<Equipment_Pot> Pot = CurLevel_->CreateActor<Equipment_Pot>();
						SortActorList_[ActorIndex].lock()->SetMoveable(Pot);
					}
					break;
					case ToolInfo::CuttingBoard:
					{
						std::shared_ptr<Tool_CuttingBoard> CuttingBoard = CurLevel_->CreateActor<Tool_CuttingBoard>();
						SortActorList_[ActorIndex].lock()->SetStuff(CuttingBoard);
					}
					break;
					case ToolInfo::Bowl:
					{
						std::shared_ptr<Equipment_Bowl> Bowl = CurLevel_->CreateActor<Equipment_Bowl>();
						SortActorList_[ActorIndex].lock()->SetMoveable(Bowl);
					}
					break;
					case ToolInfo::Steamer:
					{
						std::shared_ptr<Equipment_Steamer> Steamer = CurLevel_->CreateActor<Equipment_Steamer>();
						SortActorList_[ActorIndex].lock()->SetMoveable(Steamer);
					}
					break;
					}
				}
			}
		}

		for (size_t i = 0; i < ToolNames.size(); ++i)
		{
			ToolInfo Type = static_cast<ToolInfo>(i);

			if (ToolInfo::None != Type && ToolInfo::Max != Type && ToolInfo::Mixer != Type)
			{
				ImGui::Checkbox(ToolNames[i].data(), &IsChecks_[i]);
			}
		}
	}

	ImGui::Text("");

	if (true == IsFoodBox_)
	{
		for (size_t i = 1; i < FoodNames.size(); ++i)
		{
			ImGui::Checkbox(FoodNames[i].data(), &IsFoods_[i]);

			if (true == IsFoods_[i])
			{
				std::dynamic_pointer_cast<FoodBox>(SortActorList_[ActorIndex].lock())->SetFoodType(static_cast<IngredientType>(i - 1));
				/*		std::weak_ptr<FoodBox> Food = std::dynamic_pointer_cast<FoodBox>(SortActorList_[ActorIndex].lock());
						Food.lock()->SetFoodType(static_cast<IngredientType>(i - 1));*/
			}
		}
	}

	ImGui::Text("");

	static int Index[2] = { 0, 0 };
	ImGui::DragInt2("Drag Index", Index);
	ImGui::InputInt2("Input Index", Index);

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
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Sink>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Sink);

			std::weak_ptr<Sink> Object = std::dynamic_pointer_cast<Sink>(CurStaticMesh_.lock());
			Object.lock()->SetSinkMesh(SinkType::Normal);
		}
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
		case 9:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<FoodBox>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::FoodBox_Normal);

			std::weak_ptr<FoodBox> Object = std::dynamic_pointer_cast<FoodBox>(CurStaticMesh_.lock());
			Object.lock()->SetFoodBoxType(FoodBoxType::Normal);
			Object.lock()->SetFoodBoxMesh(FoodBoxType::Normal);
			Object.lock()->SetFoodType(IngredientType::Tomato);

			IsFoodBox_ = true;
		}
		break;
		case 10:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<FoodBox>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::FoodBox_Winter);
			std::weak_ptr<FoodBox> Object = std::dynamic_pointer_cast<FoodBox>(CurStaticMesh_.lock());
			Object.lock()->SetFoodBoxType(FoodBoxType::Winter);
			Object.lock()->SetFoodBoxMesh(FoodBoxType::Winter);
			Object.lock()->SetFoodType(IngredientType::Tomato);

			IsFoodBox_ = true;
		}
		break;
		case 11:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Sink>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Sink_Wizard);

			std::weak_ptr<Sink> Object = std::dynamic_pointer_cast<Sink>(CurStaticMesh_.lock());
			Object.lock()->SetSinkMesh(SinkType::Wizard);
		}
		break;
		case 12:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Rail>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Rail);
		}
		break;
		case 13:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurStaticMesh_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Winter);
			Object.lock()->SetConterTopMesh(CounterTopType::Winter);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_Winter);
		}
		break;
		/*case 14:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Cannon>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Cannon);
		}
		break;
		case 15:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Button>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Button);
		}
		break;*/
		case 16:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Oven>();
			CurStaticMesh_.lock()->SetStaticObjectType(MapObjType::Oven);
		}
		break;
		case 17:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Mixer>();
			std::weak_ptr<Mixer> Object = std::dynamic_pointer_cast<Mixer>(CurStaticMesh_.lock());

			Object.lock()->SetMixerType(MixerType::Mixer_Kevin);
			Object.lock()->SetMixerMesh(MixerType::Mixer_Kevin);

			Object.lock()->SetStaticObjectType(MapObjType::Mixer_Kevin);
		}
		break;
		case 18:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<CounterTop>();
			std::weak_ptr<Mixer> Object = std::dynamic_pointer_cast<Mixer>(CurStaticMesh_.lock());

			Object.lock()->SetMixerType(MixerType::Mixer_Winter);
			Object.lock()->SetMixerMesh(MixerType::Mixer_Winter);

			Object.lock()->SetStaticObjectType(MapObjType::Mixer_Winter);
		}
		break;
		case 19:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Dispenser>();
			std::weak_ptr<Dispenser> Object = std::dynamic_pointer_cast<Dispenser>(CurStaticMesh_.lock());

			Object.lock()->SetDispenserType(DispenserType::Type1);
			Object.lock()->SettingIngredientList(DispenserType::Type1);
			Object.lock()->SetStaticObjectType(MapObjType::Dispenser_Type1);
		}
		break;
		case 20:
		{
			CurStaticMesh_ = CurLevel_->CreateActor<Dispenser>();
			std::weak_ptr<Dispenser> Object = std::dynamic_pointer_cast<Dispenser>(CurStaticMesh_.lock());

			Object.lock()->SetDispenserType(DispenserType::Type2);
			Object.lock()->SettingIngredientList(DispenserType::Type2);
			Object.lock()->SetStaticObjectType(MapObjType::Dispenser_Type2);
		}
		break;
		}

		//기준 엑터의 자식으로 둔다.
		CurStaticMesh_.lock()->SetParent(Origins_[OriginIndex].lock());

		CurStaticMesh_.lock()->GetTransform().SetWorldPosition(Origins_[OriginIndex].lock()->GetTransform().GetWorldPosition());
		CurStaticMesh_.lock()->GetTransform().SetWorldMove({ Index[0] * (-INTERVAL), 0.f, Index[1] * INTERVAL});

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

		IsFoodBox_ = false;
	}

	ImGui::Text("");

	if (true == ImGui::Button("+ RotateY")
		&& 0 < SortActorList_.size()
		&& ActorIndex < SortActorList_.size())
	{
		SortActorList_[ActorIndex].lock()->GetTransform().SetAddWorldRotation({ 0.f, 90.f, 0.f });
	}

	if (true == ImGui::Button("- RotateY")
		&& 0 < SortActorList_.size()
		&& ActorIndex < SortActorList_.size())
	{
		SortActorList_[ActorIndex].lock()->GetTransform().SetAddWorldRotation({ 0.f, -90.f, 0.f });
	}

	if (true == ImGui::Button("RotateX")
		&& 0 < SortActorList_.size()
		&& ActorIndex < SortActorList_.size())
	{
		SortActorList_[ActorIndex].lock()->GetTransform().SetAddWorldRotation({ 90.f, 0.f, 0.f });
	}

	ImGui::EndTabItem();
}