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
	Seaweed_Prawn,              // 새우 + 김 들어간 모든 재료
	Seaweed_Prawn_Rice,
	Seaweed_Prawn_Rice_Cucumber,
	Prawn_Rice,					// 새우 + 밥
	Prawn_Cucumber,				// 새우 + 오이
	Prawn_Rice_Cucumber,		// 새우 + 밥 + 오이
	Prawn_Rice_Cucumber_Fish,		// 새우 + 밥 + 오이 + 회
	Prawn_Rice_Fish,

	Seaweed_Cucumber,			// 김 + 오이
	Seaweed_Fish,				// 김 + 회
	Seaweed_Fish_Cucumber,		// 김 + 회 + 오이
	Seaweed_Rice,				// 김 + 밥
	Seaweed,

	Rice_Cucumber,				// 밥 + 오이
	Rice_Fish,					// 밥 + 회
	Rice_Cucumber_Fish,			// 밥 + 오이 + 회
	Rice,

	Cucumber_Fish,				// 오이 + 회
	Cucumber,


	Flour_Flour,
	Flour_Carrot,
	Flour_Meat,
	Flour,


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
		NoneThumbnailMode_ = true;
		RendererPos_ = _Pos;
		Moveable_ = _Object->CastThis<GamePlayMoveable>();
		if (_Index == 0)
		{
			NoneThumbnailMode_ = false;
		}
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


			Static_NoneType_[NoneFoodType::Flour].push_back(IngredientType::Flour);
			Static_NoneType_[NoneFoodType::Flour_Flour].push_back(IngredientType::Flour);
			Static_NoneType_[NoneFoodType::Flour_Flour].push_back(IngredientType::Flour);
			Static_NoneType_[NoneFoodType::Flour_Carrot].push_back(IngredientType::Flour);
			Static_NoneType_[NoneFoodType::Flour_Carrot].push_back(IngredientType::Carrot);
			Static_NoneType_[NoneFoodType::Flour_Meat].push_back(IngredientType::Flour);
			Static_NoneType_[NoneFoodType::Flour_Meat].push_back(IngredientType::Meat);



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
		if (NoneThumbnailMode_ == false)
		{
			Food_Current_.push_back(_Type);

			std::weak_ptr<GameEngineFBXStaticRenderer> Renderer = Renderer_;
			Renderer_.reset();

			if (!RefreshFoodRenderer())
			{
				Food_Current_.pop_back();
				Renderer_->Death();
				Renderer_->Off();
				Renderer_ = Renderer.lock();
				return false;
			}
			else
			{
				std::shared_ptr<FoodThumbnail> Thumbnail = Moveable_.lock()->GetLevel()->CreateActor<FoodThumbnail>();
				Thumbnail->LinkObject(Moveable_.lock()->CastThis<GameEngineActor>(), float4::ZERO);
				Food_Thumbnail_.push_back(Thumbnail);
				RefreshThumbnail();
				return true;
			}
		}
		else
		{
			for (size_t i = 0; i < Food_Current_.size(); i++)
			{
				if (Food_Current_[i] == IngredientType::None)
				{
					Food_Current_[i] = _Type;

					std::weak_ptr<GameEngineFBXStaticRenderer> Renderer = Renderer_;
					Renderer_.reset();

					if (!RefreshFoodRenderer())
					{
						Food_Current_[i] = IngredientType::None;
						Renderer_->Death();
						Renderer_->Off();
						Renderer_ = Renderer.lock();
						return false;
					}
					else
					{
						RefreshThumbnail();
						return true;
					}
				}
			}
			return false;
		}

	}

	//void PushFood(IngredientType _Type)
	//{
	//	Food_Current_.push_back(_Type);
	//	RefreshThumbnailAndRenderer();
	//}

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
	bool RefreshFoodRenderer()
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
				Renderer_->SetFBXMesh("t_ingredients_bun_01_d.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Meat_Cheese:
				break;
			case NoneFoodType::Meat_Lettuce:
				break;
			case NoneFoodType::Meat_Cheese_Lettuce:
				break;
			case NoneFoodType::Meat:
				Renderer_->SetFBXMesh("m_prep_meat_burger_02.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Lettuce_Cheese:
				break;
			case NoneFoodType::Lettuce_Tomato:
				break;
			case NoneFoodType::Lettuce:
				Renderer_->SetFBXMesh("m_plated_lettuce_01.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Cheese:
				Renderer_->SetFBXMesh("m_plated_cheese_01.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Tomato:
				Renderer_->SetFBXMesh("m_plated_tomato_01.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Flour_Flour:
			case NoneFoodType::Flour_Carrot:
			case NoneFoodType::Flour_Meat:
			case NoneFoodType::Flour:
				break;
			default:
				return false;
				break;
			}
			break;
		}
		Renderer_->GetTransform().SetLocalPosition(RendererPos_);
		return true;
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
		if (!NoneThumbnailMode_)
		{
			for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
			{
				Food_Thumbnail_[i].lock()->Death();
				Food_Thumbnail_[i].lock()->Off();
				Food_Thumbnail_[i].reset();
			}
			Food_Thumbnail_.clear();
			Food_Current_.clear();
		}
		else
		{
			for (size_t i = 0; i < Food_Current_.size(); i++)
			{
				Food_Current_[i] = IngredientType::None;
			}
			for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
			{
				Food_Thumbnail_[i].lock()->SetThumbnail(IngredientType::None);
			}
		}

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


	static std::map<NoneFoodType, std::vector<IngredientType>> Static_NoneType_;
	std::vector<IngredientType> Food_Current_;
	std::vector<std::weak_ptr<FoodThumbnail>> Food_Thumbnail_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::weak_ptr<GamePlayMoveable> Moveable_;
	float4 RendererPos_;
	bool NoneThumbnailMode_;
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
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayBowl::Enum_ObjectStuffType_ 설정)");
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


	// FoodThumbnail
protected:

	//std::vector<IngredientType> FoodThumbnail_IngredientType;
	//std::vector<std::shared_ptr<FoodThumbnail>> FoodThumbnail_;

	//void CreateFoodThumbnail(unsigned int _Index)
	//{
	//	for (size_t i = 0; i < FoodThumbnail_.size(); i++)
	//	{
	//		FoodThumbnail_[i]->Death();
	//		FoodThumbnail_[i]->Off();
	//	}
	//	FoodThumbnail_.clear();
	//	std::shared_ptr<FoodThumbnail> Thumbnail = nullptr;
	//	for (size_t i = 0; i < _Index; i++)
	//	{
	//		FoodThumbnail_IngredientType.push_back(IngredientType::None);
	//		Thumbnail = GetLevel()->CreateActor<FoodThumbnail>();
	//		Thumbnail->LinkObject(CastThis<GameEngineActor>(), float4::ZERO);
	//		FoodThumbnail_.push_back(Thumbnail);
	//	}
	//}

	//bool PushFoodThumbnail(IngredientType _Type)
	//{
	//	for (size_t i = 0; i < FoodThumbnail_IngredientType.size(); i++)
	//	{
	//		if (FoodThumbnail_IngredientType[i] == IngredientType::None)
	//		{
	//			FoodThumbnail_IngredientType[i] = _Type;
	//			RefreshThumbnail();
	//			return true;
	//		}
	//	}

	//	if (FoodThumbnail_IngredientType.size() < 4)
	//	{
	//		FoodThumbnail_IngredientType.push_back(_Type);
	//		std::shared_ptr<FoodThumbnail> Thumbnail = nullptr;
	//		Thumbnail = GetLevel()->CreateActor<FoodThumbnail>();
	//		Thumbnail->LinkObject(CastThis<GameEngineActor>(), float4::ZERO);
	//		FoodThumbnail_.push_back(Thumbnail);
	//		RefreshThumbnail();
	//		return true;
	//	}
	//	return false;
	//}




	//void RefreshThumbnail()
	//{
	//	RefreshOffset();
	//	for (size_t i = 0; i < FoodThumbnail_IngredientType.size(); i++)
	//	{
	//		FoodThumbnail_[i]->SetThumbnail(FoodThumbnail_IngredientType[i]);
	//	}
	//}

	//void RefreshOffset()
	//{
	//	switch (FoodThumbnail_.size())
	//	{
	//	case 0:
	//		return;
	//		break;
	//	case 1:
	//		FoodThumbnail_[0]->SetOffset({ 0, 50, 0 });
	//		break;
	//	case 2:
	//		FoodThumbnail_[0]->SetOffset({ -20, 50, 0 });
	//		FoodThumbnail_[1]->SetOffset({ 20, 50, 0 });
	//		break;
	//	case 3:
	//		FoodThumbnail_[0]->SetOffset({ -20, 70, 0 });
	//		FoodThumbnail_[1]->SetOffset({ 20, 70, 0 });
	//		FoodThumbnail_[2]->SetOffset({ -20, 30, 0 });
	//		break;
	//	case 4:
	//		FoodThumbnail_[0]->SetOffset({ -20, 70, 0 });
	//		FoodThumbnail_[1]->SetOffset({ 20, 70, 0 });
	//		FoodThumbnail_[2]->SetOffset({ -20, 30, 0 });
	//		FoodThumbnail_[3]->SetOffset({ 20, 30, 0 });
	//		break;
	//	default:
	//		break;
	//	}
	//}

};

