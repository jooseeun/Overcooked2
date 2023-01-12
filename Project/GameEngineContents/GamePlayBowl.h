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
	Bread_Meat_Lettuce,
	Bread_Lettuce,
	Bread_Lettuce_Tomato,
	Bread_Cheese,
	Bread,

	Meat_Cheese,
	Meat_Lettuce,
	Meat_Cheese_Lettuce,
	Meat_Lettuce_Tomato,
	Meat,

	Lettuce_Cheese,
	Lettuce_Tomato,
	Lettuce,

	Cheese,

	Tomato,

};

class CombinFood
{
public:
	void Start(int _Index, std::shared_ptr<GameEngineUpdateObject> _Object, const float4& _Pos = float4::ZERO)
	{
		NoneThumbnailMode_ = true;
		RendererPos_ = _Pos;
		Moveable_ = _Object->CastThis<GamePlayMoveable>();
		if (_Index == 0)
		{
			NoneThumbnailMode_ = false;
		}
		else if (Food_NoneThumbnail_.lock() == nullptr)
		{
			Food_NoneThumbnail_ = (Moveable_.lock()->GetLevel()->CreateActor<FoodThumbnail>());
			Food_NoneThumbnail_.lock()->LinkObject(Moveable_.lock(), float4::ZERO);
			Food_NoneThumbnail_.lock()->SetThumbnail(IngredientType::None);
			Food_NoneThumbnail_.lock()->SetOffset({ 0, 50, 0 });
		}
		size_t stack =  static_cast<size_t>(_Index)- Food_Current_.size();
		for (size_t i = 0; i < stack; i++)
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
			Static_NoneType_[NoneFoodType::Bread_Meat_Lettuce].push_back(IngredientType::Bread);
			Static_NoneType_[NoneFoodType::Bread_Meat_Lettuce].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Bread_Meat_Lettuce].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Bread_Lettuce].push_back(IngredientType::Bread);
			Static_NoneType_[NoneFoodType::Bread_Lettuce].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Bread_Cheese].push_back(IngredientType::Bread);
			Static_NoneType_[NoneFoodType::Bread_Cheese].push_back(IngredientType::Cheese);
			


			Static_NoneType_[NoneFoodType::Bread_Lettuce_Tomato].push_back(IngredientType::Bread);
			Static_NoneType_[NoneFoodType::Bread_Lettuce_Tomato].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Bread_Lettuce_Tomato].push_back(IngredientType::Tomato);
			

			Static_NoneType_[NoneFoodType::Meat_Lettuce_Tomato].push_back(IngredientType::Meat);
			Static_NoneType_[NoneFoodType::Meat_Lettuce_Tomato].push_back(IngredientType::Lettuce);
			Static_NoneType_[NoneFoodType::Meat_Lettuce_Tomato].push_back(IngredientType::Tomato);
			
			
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

	bool PushFood(IngredientType _Type)
	{
		if (NoneThumbnailMode_ == false)
		{
			if (Food_Current_.size() >= 4)
			{
				return false;
			}
			Food_Current_.push_back(_Type);
			std::shared_ptr<FoodThumbnail> Thumbnail = Moveable_.lock()->GetLevel()->CreateActor<FoodThumbnail>();
			Thumbnail->LinkObject(Moveable_.lock()->CastThis<GameEngineActor>(), float4::ZERO);
			Food_Thumbnail_.push_back(Thumbnail);
			RefreshThumbnailAndRenderer();
			Renderer_->Off();
			Moveable_.lock()->CookingGageHalf();
			return true;
		}
		else
		{
			for (size_t i = 0; i < Food_Current_.size(); i++)
			{
				if (Food_Current_[i] == IngredientType::None)
				{
					Food_Current_[i] = _Type;
					RefreshThumbnail();
					Moveable_.lock()->CookingGageHalf();
					return true;
				}
			}
			return false;
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
				if (Renderer.lock() != nullptr)
				{
					Renderer.lock()->Death();
					Renderer.lock()->Off();
				}

				Food_Thumbnail_.push_back(Thumbnail);
				RefreshThumbnail();
				Moveable_.lock()->CookingGageHalf();
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
						Moveable_.lock()->CookingGageHalf();
						return true;
					}
				}
			}
			return false;
		}

	}

	bool AddFood(std::shared_ptr<CombinFood> _Food)
	{
		if (_Food->Food_Current_.size() + Food_Current_.size() > 4)
		{
			return false;
		}
		else
		{
			std::shared_ptr<CombinFood> Food = std::make_shared<CombinFood>();
			for (size_t i = 0; i < Food_Current_.size(); i++)
			{
				Food->Food_Current_.push_back(Food_Current_[i]);
			}

			for (size_t i = 0; i < _Food->Food_Current_.size(); i++)
			{
				Food->Food_Current_.push_back(_Food->Food_Current_[i]);
			}
			if (Food->GetFoodType() != FoodType::None || Food->GetNoneFoodClass() != NoneFoodType::None)
			{
				for (size_t i = 0; i < _Food->Food_Current_.size(); i++)
				{
					Food_Current_.push_back(_Food->Food_Current_[i]);
				}
				RefreshThumbnailAndRenderer();
				_Food->Clear();
				return true;
			}
		}
		return false;
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
			Food_Thumbnail_[i].lock()->Off();
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
			Renderer_->SetFBXMesh("m_recipe_dimsum_03.FBX", "Texture");
			break;
		case FoodType::SteamedFish:
			Renderer_->SetFBXMesh("Sushi_Roll_Salmon.FBX", "Texture");
			Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
			break;
		case FoodType::MeatDumpling:
			Renderer_->SetFBXMesh("m_recipe_dimsum_01.FBX", "Texture");
			break;
		case FoodType::CarrotDumpling:
			Renderer_->SetFBXMesh("m_recipe_dimsum_02.FBX", "Texture");
			break;
		case FoodType::StrawberryPancake:
			Renderer_->SetFBXMesh("m_recipe_strawberry_pancake_01.FBX", "Texture");
			break;
		case FoodType::BlueberryPancake:
			Renderer_->SetFBXMesh("m_recipe_blueberry_pancake_01.FBX", "Texture");
			break;
		case FoodType::ChrismasPuddingOrange:
			Renderer_->SetFBXMesh("m_recipe_ChristmasPudding_01.FBX", "Texture");
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
				Renderer_->SetFBXMesh("m_recipe_cheese_lettuce_burger_01.FBX", "Texture");
				break;
			case NoneFoodType::Bread_Meat_Lettuce:
				Renderer_->SetFBXMesh("Lettuce_plain_burger.FBX", "Texture");
				break;
			case NoneFoodType::Bread_Lettuce:
				Renderer_->SetFBXMesh("Leffuce_burger.FBX", "Texture");
				break;
				
			case NoneFoodType::Bread:
				Renderer_->SetFBXMesh("t_ingredients_bun_01_d.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Meat_Cheese:
				Renderer_->SetFBXMesh("m_prep_meat_burger_02.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Meat_Lettuce:
				Renderer_->SetFBXMesh("m_prep_meat_burger_02.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Meat_Cheese_Lettuce:
				Renderer_->SetFBXMesh("m_prep_meat_burger_02.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Bread_Lettuce_Tomato:
				Renderer_->SetFBXMesh("m_recipe_lettuce_tomato_burger_01.fbx", "Texture");
				break;
			case NoneFoodType::Meat_Lettuce_Tomato:
				Renderer_->SetFBXMesh("m_prep_meat_burger_02.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				
				break;
			case NoneFoodType::Meat:
				Renderer_->SetFBXMesh("m_prep_meat_burger_02.FBX", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				break;
			case NoneFoodType::Lettuce_Cheese:
				break;
			case NoneFoodType::Lettuce_Tomato:
				Renderer_->SetFBXMesh("m_plated_lettuce_01.fbx", "Texture");
				Renderer_->GetTransform().SetWorldScale({ 1,1,1 });
				
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
			case NoneFoodType::Bread_Cheese:
				Renderer_->SetFBXMesh("m_recipe_cheeseburger_01.FBX", "Texture");
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

		if (NoneThumbnailMode_ == true)
		{
			Renderer_->Off();
		}
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

			for (size_t i = 0; i < Food_Current.size(); i++)
			{
				if (Food_Current[i] == IngredientType::None)
				{
					continue;
				}
				Index++;
			}
			if (Index != Data.size())
			{
				continue;
			}
			Index = 0;

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
		//NoneThumbnailMode_ = false;
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
				Food_Thumbnail_[i].lock()->Off();
			}
		}
		RefreshThumbnail();

		if (Renderer_ != nullptr)
		{
			Renderer_->Death();
			Renderer_->Off();
			Renderer_.reset();
		}
		Moveable_.lock()->ReSetCookingGage();
		CookType_ = ToolInfo::None;
	}

	void RefreshThumbnail()
	{
		if (NoneThumbnailMode_ == true)
		{
			if (IsClear())
			{
				Food_NoneThumbnail_.lock()->On();
				return;
			}
			else
			{
				Food_NoneThumbnail_.lock()->Off();
			}
		}

		RefreshOffset();
		for (size_t i = 0; i < Food_Thumbnail_.size(); i++)
		{
			Food_Thumbnail_[i].lock()->SetThumbnail(Food_Current_[i]);
			Food_Thumbnail_[i].lock()->On();
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

	void Move(std::shared_ptr<CombinFood> _Food)
	{
		Clear();
		if (NoneThumbnailMode_ == false)
		{
			for (int i = 0; i < _Food->Food_Current_.size(); i++)
			{
				if (_Food->Food_Current_[i] != IngredientType::None)
				{
					Food_Current_.push_back(_Food->Food_Current_[i]);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			Food_Current_ = _Food->Food_Current_;
		}
		
		CookType_ = _Food->CookType_;
		RefreshThumbnailAndRenderer();
		_Food->Moveable_.lock()->ReSetCookingGage();

		_Food->Clear();
	}

	void Switching(std::shared_ptr<CombinFood> _Food)
	{
		std::vector<IngredientType> Food_Current = Food_Current_;
		Clear();
		Food_Current_ = _Food->Food_Current_;
		RefreshThumbnailAndRenderer();

		float Gage = _Food->Moveable_.lock()->GetCookingGage();
		_Food->Moveable_.lock()->CookingGage_ = Moveable_.lock()->CookingGage_;
		Moveable_.lock()->CookingGage_ = Gage;

		_Food->Clear();
		_Food->Food_Current_ = Food_Current;
		_Food->RefreshThumbnailAndRenderer();
	}

	inline bool GetTrim()
	{
		if (Moveable_.lock()->CookingGage_ >= 100.f)
		{
			return true;
		}
		return false;
	}

	inline ToolInfo GetCookType() const
	{
		return CookType_;
	}

	inline void SetCookType(ToolInfo _Type)
	{
		CookType_ = _Type;
	}

	FoodData GetFoodData()
	{
		return GlobalGameData::GetFoodData(GetFoodType());
	}

	std::shared_ptr<GameEngineFBXStaticRenderer> GetFoodRenderer()
	{
		return Renderer_;
	};

	std::vector<IngredientType> GetFoodCurrent()
	{
		return Food_Current_;
	}

	static std::map<NoneFoodType, std::vector<IngredientType>> Static_NoneType_;
private:
	std::vector<IngredientType> Food_Current_;
	std::vector<std::weak_ptr<FoodThumbnail>> Food_Thumbnail_;
	std::weak_ptr<FoodThumbnail> Food_NoneThumbnail_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::weak_ptr<GamePlayMoveable> Moveable_;

	ToolInfo CookType_ = ToolInfo::None;
	float4 RendererPos_;
	bool NoneThumbnailMode_;
};

class GamePlayBowl : public GamePlayMoveable
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
		int index = 0; int max = 0;
		const std::vector<FoodType>& FoodType__ = GlobalGameData::GetCurStageRef().StageRecipe;
		for (size_t i = 0; i < FoodType__.size(); i++)
		{
			index = 0;
			const FoodData& Data = GlobalGameData::GetFoodData(FoodType__[i]);

			for (size_t j = 0; j < Data.Ingredient.size(); j++)
			{
				if (!Data.Cookery.empty())
				{
					if (ConvertToolinfo(Data.Cookery[j]) == Enum_ObjectBowlType_)
					{
						index++;
					}

				}
				else
				{
					for (size_t k = 0; k < Data.CommonCookery.size(); k++)
					{
						if (ConvertToolinfo(Data.CommonCookery[k]) == Enum_ObjectBowlType_)
						{
							index = static_cast<int>(Data.Ingredient.size());
							break;
						}
					}
					break;
				}
			}
			if (max < index)
			{
				max = index;
			}
		}
		GetCombinFood()->Start(max, shared_from_this());
	}
	//static ToolInfo ConvertBowlObject(ObjectBowlType _Type)
	//{
	//	switch (_Type)
	//	{
	//	case ObjectBowlType::Bowl:
	//		return ToolInfo::Mixer;
	//		break;
	//	case ObjectBowlType::Pod:
	//		return ToolInfo::Pot;
	//		break;
	//	case ObjectBowlType::Plate:
	//		return ToolInfo::Plate;
	//		break;
	//	case ObjectBowlType::FryingPan:
	//		return ToolInfo::FryingPan;
	//		break;
	//	case ObjectBowlType::Steamer:
	//		return ToolInfo::Steamer;
	//		break;
	//	default:
	//		return ToolInfo::None;
	//		break;
	//	}
	//}
	static ObjectBowlType ConvertToolinfo(ToolInfo _Type)
	{
		switch (_Type)
		{
		case ToolInfo::OvenPot:
		case ToolInfo::Mixer:
			return ObjectBowlType::Bowl;
			break;
		case ToolInfo::Pot:
			return ObjectBowlType::Pod;
			break;
		case ToolInfo::Plate:
			return ObjectBowlType::Plate;
			break;
		case ToolInfo::FryingPan:
			return ObjectBowlType::FryingPan;
			break;
		case ToolInfo::Steamer:
			return ObjectBowlType::Steamer;
			break;
		default:
			return ObjectBowlType::None;
			break;
		}
	}

private:
	ObjectBowlType Enum_ObjectBowlType_;
	std::shared_ptr<CombinFood> CombinFood_;


	// FoodThumbnail
protected:

	virtual void BowltoBowl(std::shared_ptr<GamePlayBowl> _Bowl)
	{
		FoodData Data = _Bowl->GetCombinFood()->GetFoodData();
		ToolInfo ToolBefore = ToolInfo::None;
		for (size_t i = 0; i < Data.CommonCookery.size(); i++)
		{
			if (_Bowl->GetCombinFood()->GetCookType() == ToolBefore)
			{
				GetCombinFood()->Move(_Bowl->GetCombinFood());
			}
			else
			{
				ToolBefore = Data.CommonCookery[i];
			}
		}
	}

	inline bool ChangeSameBowl(std::shared_ptr<GamePlayBowl> _Bowl)
	{
		if (GetObjectBowlType() == _Bowl->GetObjectBowlType())
		{
			GetCombinFood()->Switching(_Bowl->GetCombinFood());
			SwitchingCookingGage(_Bowl);
			return true;
		}
		return false;
	}
	
	void SetHighlightEffectOn() override
	{
		GamePlayObject::SetHighlightEffectOn();
		if (GetCombinFood()->GetFoodRenderer() != nullptr)
		{
			GetCombinFood()->GetFoodRenderer()->SetAllPixelDataPlusColor(float4(0.2f, 0.2f, 0.2f, 0.0f));
		}
	}

	void SetHighlightEffectOff() override
	{
		GamePlayObject::SetHighlightEffectOff();
		if (GetCombinFood()->GetFoodRenderer() != nullptr)
		{
			GetCombinFood()->GetFoodRenderer()->SetAllPixelDataPlusColor(float4(0, 0, 0, 0));
		}
	}

};

