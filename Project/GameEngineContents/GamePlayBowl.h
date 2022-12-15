#pragma once
#include "GamePlayEquipment.h"
#include "GamePlayFood.h"
#include "Enums.h"
#include "FoodThumbnail.h"
#include "InGameUIActor.h"
#include "GlobalGameData.h"
#include "GamePlayTool.h"

enum class ObjectBowlType
{
	None,
	Bowl,
	Pod,
	Plate,
	FryingPan,
	Steamer
};

enum class NoneFoodType
{
	None,
	Seaweed_Prawn,              // ���� + �� �� ��� ���
	Seaweed_Prawn_Rice,
	Seaweed_Prawn_Rice_Cucumber,
	Prawn_Rice,					// ���� + ��
	Prawn_Cucumber,				// ���� + ����
	Prawn_Rice_Cucumber,		// ���� + �� + ����
	Prawn_Rice_Cucumber_Fish,		// ���� + �� + ���� + ȸ
	Prawn_Rice_Fish,

	Seaweed_Cucumber,			// �� + ����
	Seaweed_Fish,				// �� + ȸ
	Seaweed_Fish_Cucumber,		// �� + ȸ + ����
	Seaweed_Rice,				// �� + ��
	Seaweed,

	Rice_Cucumber,				// �� + ����
	Rice_Fish,					// �� + ȸ
	Rice_Cucumber_Fish,			// �� + ���� + ȸ
	Rice,

	Cucumber_Fish,				// ���� + ȸ
	Cucumber,


	Bread_Meat_Cheese_Lettuce,
	Bread,

	Meat_Cheese,
	Meat_Lettuce,
	Meat_Cheese_Lettuce,
	Meat,

	Lettuce_Cheese,
	Lettuce_Tomato,
	Lettuce,

	Cheese,

	Tomato,

};

struct CombinFood
{
	void Start(int _Index, std::shared_ptr<GameEngineUpdateObject> _Object, const float4& _Pos = float4::ZERO)
	{
		RendererPos_ = _Pos;
		Moveable_ = _Object->CastThis<GamePlayMoveable>();
		for (size_t i = 0; i < _Index; i++)
		{
			Food_Current_.push_back(IngredientType::None);
		}
		RefreshThumbnailAndRenderer();

		if (Static_NoneType_.empty())
		{
			Static_NoneType_[NoneFoodType::Seaweed_Prawn].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice_Cucumber].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice_Cucumber].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice_Cucumber].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Prawn_Rice_Cucumber].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Prawn_Rice].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Prawn_Rice].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Prawn_Cucumber].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Prawn_Cucumber].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber_Fish].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber_Fish].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber_Fish].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Cucumber_Fish].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Fish].push_back(IngredientType::Prawn);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Fish].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Prawn_Rice_Fish].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Seaweed_Cucumber].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Cucumber].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Seaweed_Fish].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Fish].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Seaweed_Fish_Cucumber].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Seaweed_Fish_Cucumber].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Fish_Cucumber].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Seaweed_Rice].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Seaweed_Rice].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Seaweed].push_back(IngredientType::Seaweed);
			Static_NoneType_[NoneFoodType::Rice_Cucumber].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Rice_Cucumber].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Rice_Fish].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Rice_Fish].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Rice_Cucumber_Fish].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Rice_Cucumber_Fish].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Rice_Cucumber_Fish].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Rice].push_back(IngredientType::Rice);
			Static_NoneType_[NoneFoodType::Cucumber_Fish].push_back(IngredientType::Cucumber);
			Static_NoneType_[NoneFoodType::Cucumber_Fish].push_back(IngredientType::Fish);
			Static_NoneType_[NoneFoodType::Cucumber].push_back(IngredientType::Cucumber);

			Static_NoneType_[NoneFoodType::Bread_Meat_Cheese_Lettuce].push_back(IngredientType::Bread);
			Static_NoneType_[NoneFoodType::Bread_Meat_Cheese_Lettuce].push_back(IngredientType::Cheese);
			Static_NoneType_[NoneFoodType::Bread_Meat_Cheese_Lettuce].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Bread_Meat_Cheese_Lettuce].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Bread].push_back(IngredientType::Bread);
			Static_NoneType_[NoneFoodType::Meat_Cheese].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Meat_Cheese].push_back(IngredientType::Cheese);
			Static_NoneType_[NoneFoodType::Meat_Lettuce].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Meat_Lettuce].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Meat_Cheese_Lettuce].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Meat_Cheese_Lettuce].push_back(IngredientType::Cheese);
			Static_NoneType_[NoneFoodType::Meat_Cheese_Lettuce].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Meat].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Lettuce_Cheese].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Lettuce_Cheese].push_back(IngredientType::Cheese);
			Static_NoneType_[NoneFoodType::Lettuce_Tomato].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Lettuce_Tomato].push_back(IngredientType::Tomato);
			Static_NoneType_[NoneFoodType::Lettuce].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Cheese].push_back(IngredientType::Cheese);
			Static_NoneType_[NoneFoodType::Tomato].push_back(IngredientType::Tomato);
		}
	}

	bool AddFood(IngredientType _Type)
	{
		const StageData& StageData_ = GlobalGameData::GetCurStageRef();
		FoodData Data;
		for (size_t i = 0; i < StageData_.StageRecipe.size(); i++)
		{
			Data = GlobalGameData::GetFoodData(StageData_.StageRecipe[i]);
			for (size_t j = 0; j < Data.Ingredient.size(); j++)
			{
				if (Data.Ingredient[j] == _Type)
				{
					for (size_t i = 0; i < Food_Current_.size(); i++)
					{
						if (Food_Current_[i] == IngredientType::None)
						{
							Food_Current_[i] = _Type;
							RefreshThumbnailAndRenderer();
							return true;
						}
					}
					return false;
				}
			}
		}
		return false;
	}
	void PushFood(IngredientType _Type)
	{
		Food_Current_.push_back(_Type);
		RefreshThumbnailAndRenderer();
	}

	void RefreshThumbnailAndRenderer()
	{	
		for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
		{
			Food_Thumbnail_[i].lock()->Death();
			Food_Thumbnail_[i].lock()->Off();
		}
		Food_Thumbnail_.clear();
		for (size_t i = 0; i < Food_Current_.size(); i++)
		{
			Food_Thumbnail_.push_back(Moveable_.lock()->GetLevel()->CreateActor<FoodThumbnail>());
			Food_Thumbnail_[i].lock()->LinkObject(Moveable_.lock(), float4::ZERO);
		}
		RefreshThumbnail();
		RefreshFoodRenderer();
	}
	void RefreshFoodRenderer()
	{
		if (Renderer_ != nullptr)
		{
			Renderer_->Death();
			Renderer_->Off();
		}
		Renderer_ = Moveable_.lock()->CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer_->GetTransform().SetWorldScale({ 100,100,100 });
		switch (GetFoodType())
		{
		case FoodType::CucumberSushi:
			Renderer_->SetFBXMesh("m_recipe_sushi_03.FBX", "Texture");
			break;
		case FoodType::FishSushi:
			Renderer_->SetFBXMesh("m_recipe_sushi_01 #133833.FBX", "Texture");
			break;
		case FoodType::FishandCucumberSushi:
			Renderer_->SetFBXMesh("m_recipe_sushi_04.FBX", "Texture");
			break;
		case FoodType::FishSushimi:
		{
			Renderer_->SetFBXMesh("Sushi_Roll_Salmon.FBX", "Texture");
			Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
		}
			break;
		case FoodType::PrawnSushimi:
		{
			Renderer_->SetFBXMesh("Prawn_Sushimi.FBX", "Texture");
			Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
			//Renderer_->GetTransform().SetLocalRotation({ 0,-90,0 });
		}
			break;
		case FoodType::PlainBurger:
			Renderer_->SetFBXMesh("m_recipe_plainburger_01.FBX", "Texture");
			break;
		case FoodType::CheeseBurger:
			Renderer_->SetFBXMesh("m_recipe_cheeseburger_01.FBX", "Texture");
			break;
		case FoodType::CheeseBurgerLettuceTomato:
			Renderer_->SetFBXMesh("m_recipe_lettuce_tomato_burger_01.FBX", "Texture");
			break;
		case FoodType::PrawnDumpling:
			break;
		case FoodType::SteamedFish:
			break;
		case FoodType::MeatDumpling:
			break;
		case FoodType::CarrotDumpling:
			break;
		default:
			switch (GetNoneFoodClass())
			{
			case NoneFoodType::None:
				break;
			case NoneFoodType::Seaweed_Prawn:
			case NoneFoodType::Seaweed_Prawn_Rice:
			case NoneFoodType::Seaweed_Prawn_Rice_Cucumber:
			{
				Renderer_->SetFBXMesh("m_plated_sushi_wrong_01.FBX", "Texture");
			}
				break;
			case NoneFoodType::Prawn_Rice:
			case NoneFoodType::Prawn_Cucumber:
			{
				Renderer_->SetFBXMesh("m_plated_sushi_wrong_02.FBX", "Texture");
			}
				break;
			case NoneFoodType::Prawn_Rice_Cucumber:
			{
				Renderer_->SetFBXMesh("m_plated_sushi_wrong_04.FBX", "Texture");
			}
				break;
			case NoneFoodType::Prawn_Rice_Cucumber_Fish:
			{
				Renderer_->SetFBXMesh("m_plated_sushi_wrong_04.FBX", "Texture");
			}
			break;
			case NoneFoodType::Prawn_Rice_Fish:
			{
				Renderer_->SetFBXMesh("m_plated_sushi_wrong_05.FBX", "Texture");
			}
			break;
			case NoneFoodType::Seaweed_Cucumber:			
				Renderer_->SetFBXMesh("m_plated_seaweed_cucumber_01.FBX", "Texture");
				break;
			case NoneFoodType::Seaweed_Fish:
				Renderer_->SetFBXMesh("m_plated_seaweed_fish_01.FBX", "Texture");
				break;
			case NoneFoodType::Seaweed_Fish_Cucumber:
				Renderer_->SetFBXMesh("m_plated_seaweed_fish_cucumber_01.FBX", "Texture");
				break;
			case NoneFoodType::Seaweed_Rice:
				Renderer_->SetFBXMesh("m_plated_seaweed_rice_01.FBX", "Texture");
				break;
			case NoneFoodType::Seaweed:
				Renderer_->SetFBXMesh("t_ingredients_seaweed_plated.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Rice_Cucumber:
				Renderer_->SetFBXMesh("m_plated_rice_cucumber_01.FBX", "Texture");
				break;
			case NoneFoodType::Rice_Fish:
				Renderer_->SetFBXMesh("m_plated_rice_fish_01.FBX", "Texture");
				break;
			case NoneFoodType::Rice_Cucumber_Fish:
				Renderer_->SetFBXMesh("m_plated_rice_fish_cucumber_01.FBX", "Texture");
				break;
			case NoneFoodType::Rice:
				Renderer_->SetFBXMesh("t_ingredients_rice_plated.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Cucumber_Fish:
				break;
			case NoneFoodType::Cucumber:
				Renderer_->SetFBXMesh("m_plated_sushi_cucumber_01.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;


			case NoneFoodType::Bread_Meat_Cheese_Lettuce:
				break;
			case NoneFoodType::Bread:
				break;
			case NoneFoodType::Meat_Cheese:
				break;
			case NoneFoodType::Meat_Lettuce:
				break;
			case NoneFoodType::Meat_Cheese_Lettuce:
				break;
			case NoneFoodType::Meat:
				break;
			case NoneFoodType::Lettuce_Cheese:
				break;
			case NoneFoodType::Lettuce_Tomato:
				break;
			case NoneFoodType::Lettuce:
				break;
			case NoneFoodType::Cheese:
				break;
			case NoneFoodType::Tomato:
				break;
			default:
				break;
			}
			break;
		}
		Renderer_->GetTransform().SetLocalPosition(RendererPos_);
	}

	NoneFoodType GetNoneFoodClass()
	{
		for (std::pair<const NoneFoodType, std::vector<IngredientType>>& map : Static_NoneType_)
		{
			std::vector<IngredientType> Food_Current = Food_Current_;
			bool IsThat = false;
			int Index = 0;
			if (Food_Current.size() != map.second.size())
			{
				continue;
			}

			for (auto vector : map.second)
			{
				IsThat = false;
				for (size_t i = 0; i < Food_Current_.size(); i++)
				{
					if (Food_Current_[i] == IngredientType::None)
					{
						continue;
					}
					if (vector == Food_Current_[i])
					{
						Index++;
						IsThat = true;
						Food_Current[i] = IngredientType::None;
						break;
					}

				}

				if (IsThat == false)
				{
					break;
				}

			}

			for (size_t i = 0; i < Food_Current.size(); i++)
			{
				if (Food_Current[i] != IngredientType::None)
				{
					continue;
				}
			}

			if (Index == map.second.size() && IsThat == true)
			{
				return map.first;
			}
		}
		return NoneFoodType::None;
	}

	FoodType GetFoodType()
	{
		const StageData& StageData_ = GlobalGameData::GetCurStageRef();
		std::vector<IngredientType> Data;
		for (size_t i = 0; i < StageData_.StageRecipe.size(); i++)
		{
			Data = GlobalGameData::GetFoodData(StageData_.StageRecipe[i]).Ingredient;
			std::vector<IngredientType> Food_Current = Food_Current_;
			bool IsThat = false;
			int Index = 0;
			for (size_t j = 0; j < Data.size(); j++)
			{
				IsThat = false;
				for (size_t k = 0; k < Food_Current.size(); k++)
				{
					if (Food_Current[k] == IngredientType::None)
					{
						continue;
					}
					if (Data[j] == Food_Current[k])
					{
						Index++;
						IsThat = true;
						Data[j] = IngredientType::None;
						Food_Current[k] = IngredientType::None;
						break;
					}
				}
			
				if (IsThat == false)
				{
					break;
				}
			}
			
			if (Index == Data.size() && IsThat == true)
			{
				return StageData_.StageRecipe[i];
			}
		}
		return FoodType::None;
	}

	bool IsClear()
	{
		for (size_t i = 0; i < Food_Current_.size(); i++)
		{
			if (Food_Current_[i] != IngredientType::None)
			{
				return false;
			}
		}
		return true;
	}

	void Clear()
	{
		Food_Current_.clear();
		for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
		{
			Food_Thumbnail_[i].lock()->Death();
			Food_Thumbnail_[i].lock()->Off();
			Food_Thumbnail_[i].reset();
		}
		Food_Thumbnail_.clear();
		Renderer_->Death();
		Renderer_->Off();
		Renderer_.reset();
	}

	void RefreshThumbnail()
	{
		RefreshOffset();
		for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
		{
			Food_Thumbnail_[i].lock()->SetThumbnail(Food_Current_[i]);
		}
	}

	void RefreshOffset()
	{
		switch (Food_Thumbnail_.size())
		{
		case 0:
			return;
			break;
		case 1:
			Food_Thumbnail_[0].lock()->SetOffset({ 0, 50, 0 });
			break;
		case 2:
			Food_Thumbnail_[0].lock()->SetOffset({ -20, 50, 0 });
			Food_Thumbnail_[1].lock()->SetOffset({ 20, 50, 0 });
			break;
		case 3:
			Food_Thumbnail_[0].lock()->SetOffset({ -20, 70, 0 });
			Food_Thumbnail_[1].lock()->SetOffset({ 20, 70, 0 });
			Food_Thumbnail_[2].lock()->SetOffset({ -20, 30, 0 });
			break;
		case 4:
			Food_Thumbnail_[0].lock()->SetOffset({ -20, 70, 0 });
			Food_Thumbnail_[1].lock()->SetOffset({ 20, 70, 0 });
			Food_Thumbnail_[2].lock()->SetOffset({ -20, 30, 0 });
			Food_Thumbnail_[3].lock()->SetOffset({ 20, 30, 0 });
			break;
		default:
			break;
		}
	}

	//CombinFood& operator=(const CombinFood& _Other)
	//{
	//	Renderer_->Death();
	//	Renderer_->Off();
	//	for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
	//	{
	//		Food_Thumbnail_[i].lock()->Death();
	//		Food_Thumbnail_[i].lock()->Off();
	//	}


	//	Food_Current_ = _Other.Food_Current_;


	//}

	//void SetRenderer(std::shared_ptr<GamePlayMoveable> _Moveable/*const std::string& _Name*/)
	//{
	//	Renderer_ = _Moveable->GetFBXMesh();
	//	Renderer_.lock()->SetParent(Moveable_.lock());
	//	const float4& Pos = Renderer_.lock()->GetTransform().GetWorldPosition();
	//	Renderer_.lock()->GetTransform().SetLocalPosition(float4::ZERO);
	//}

	static std::map<NoneFoodType, std::vector<IngredientType>> Static_NoneType_;
	std::vector<IngredientType> Food_Current_;
	std::vector<std::weak_ptr<FoodThumbnail>> Food_Thumbnail_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::weak_ptr<GamePlayMoveable> Moveable_;
	float4 RendererPos_;
};

class GamePlayBowl : public GamePlayEquipment
{
public:
	// constrcuter destructer
	GamePlayBowl();
	~GamePlayBowl();

	// delete Function
	GamePlayBowl(const GamePlayBowl& _Other) = delete;
	GamePlayBowl(GamePlayBowl&& _Other) noexcept = delete;
	GamePlayBowl& operator=(const GamePlayBowl& _Other) = delete;
	GamePlayBowl& operator=(GamePlayBowl&& _Other) noexcept = delete;

	inline ObjectBowlType GetObjectBowlType() const
	{
		if (Enum_ObjectBowlType_ == ObjectBowlType::None)
		{
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayBowl::Enum_ObjectStuffType_ ����)");
		}
		return Enum_ObjectBowlType_;
	}
	inline std::shared_ptr<CombinFood> GetCombinFood()
	{
		if (CombinFood_ == nullptr)
		{
			CombinFood_ = std::make_shared<CombinFood>();
		}
		return CombinFood_;
	}



protected:
	void Start() override;

	inline void SetObjectBowlType(ObjectBowlType _Type)
	{
		Enum_ObjectBowlType_ = _Type;
	}
private:
	ObjectBowlType Enum_ObjectBowlType_;
	std::shared_ptr<CombinFood> CombinFood_;

	//HoldDownEnum HoldOn(std::shared_ptr<Player> _Player) override;


	virtual bool CheckCombinFood(IngredientType	_Type) { return false; };

};

