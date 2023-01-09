#include "PreCompile.h"
#include "Dispenser.h"
#include "FoodHeader.h"
#include "GlobalGameData.h"
#include "FoodBox.h"

Dispenser::Dispenser() 
{
}

Dispenser::~Dispenser() 
{
}

void Dispenser::SettingIngredientList(DispenserType _Type)
{
	GetStuff()->CastThis<Tool_Dispenser>()->SettingIngredientList(_Type);
}

void Dispenser::Start()
{
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("m_city_dispenser_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldMove({0.f, 0.f, -50.f});

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	SetStuff(GetLevel()->CreateActor<Tool_Dispenser>());
}

//void Dispenser::Update(float _DeltaTime)
//{
//
//}


Tool_Dispenser::Tool_Dispenser()
	: FirstTimeCheck_(false)
	, Index_(false)
	, Delay_(0)
{
}

Tool_Dispenser::~Tool_Dispenser()
{
}
void Tool_Dispenser::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::Dispenser);
}

void Tool_Dispenser::SettingIngredientList(DispenserType _Type)
{
	switch (_Type)
	{
		case DispenserType::Type1:
		{
			IngredientList_.push_back(IngredientType::Seaweed);
			IngredientList_.push_back(IngredientType::Rice);

		}
		break;
		case DispenserType::Type2:
		{
			IngredientList_.push_back(IngredientType::Prawn);
			IngredientList_.push_back(IngredientType::Fish);
		}
		break;
	}
	for (size_t i = 0; i < IngredientList_.size(); i++)
	{
		if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
		{
			Tool_FoodBox::Queue_FillFood(IngredientList_[i]);
			Tool_FoodBox::Queue_FillFood(IngredientList_[i]);
		}
	}
}


void Tool_Dispenser::Update(float _Delta)
{
	if (FirstTimeCheck_ == false)
	{
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalPosition({ -50, 0, -50 });
		Collision->GetTransform().SetWorldScale({ 100, 50, 50 });
		Collision->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
			std::bind(&Tool_Dispenser::GetFrontStaticObject, this, std::placeholders::_1, std::placeholders::_2));
		Collision->Off();
		Collision->Death();
		Collision = nullptr;

		FirstTimeCheck_ = true;
	}

	if (Front_StaticObject_.lock() != nullptr)
	{
		if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
		{
			if (GlobalGameData::IsGameStart() == true)
			{
				Delay_ += _Delta;
			}
			
			if (Front_StaticObject_.lock()->GetMoveable() == nullptr && Delay_ > 3.f)
			{
				Delay_ = 0;
				//	Front_StaticObject_.lock()->SetMoveable(GetLevel()->CreateActor<Food_Ingredients_Fish>()); //µð¹ö±ë¿ë

				++Index_;
				if (Index_ >= IngredientList_.size())
				{
					Index_ = 0;
				}
				std::shared_ptr<GamePlayFood> Food = Tool_FoodBox::Queue_GetFood(IngredientList_[Index_]);

				Front_StaticObject_.lock()->SetPlayerState(nullptr, PlayerCurStateType::HoldDown, Food);

				//if (nullptr != ServerInitManager::Net && (ServerInitManager::Net->GetIsHost()))
				//{
				//	std::shared_ptr<ObjectInteractUpdatePacket> Packet = std::make_shared<ObjectInteractUpdatePacket>();
				//	Packet->ObjectID = Front_StaticObject_.lock()->GetNetID();
				//	Packet->PlayerNum = Food->GetNetID();

				//	ServerInitManager::Net->SendPacket(Packet);
				//}

				//Front_StaticObject_.lock()->SetPlayerState(nullptr, PlayerCurStateType::HoldDown , Food);
			}
		}
	}
}

CollisionReturn Tool_Dispenser::GetFrontStaticObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (GetParent() == _Other->GetParent())
	{
		return CollisionReturn::ContinueCheck;
	}
	std::weak_ptr<GamePlayStaticObject> Object = _Other->GetParent()->CastThis<GamePlayStaticObject>();

	if (Object.lock() != nullptr)
	{
		Front_StaticObject_ = Object.lock();
		return CollisionReturn::Break;
	}
	return CollisionReturn::ContinueCheck;
}