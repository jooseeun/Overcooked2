#pragma once
#include "GamePlayEquipment.h"
#include "GamePlayFood.h"
#include "Enums.h"
#include "FoodThumbnail.h"
#include "InGameUIActor.h"
#include "GlobalGameData.h"

enum class ObjectBowlType
{
	None,
	Bowl,
	Pod,
	Plate,
	FryingPan,
	Steamer
};

struct CombinFood
{

	void Start(int _Index, std::shared_ptr<GameEngineUpdateObject> _Object, bool _bool)
	{
		Moveable_ = _Object->CastThis<GamePlayMoveable>();
		for (size_t i = 0; i < _Index; i++)
		{
			Food_Current_.push_back(IngredientType::None);
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
		RefreshFoodRecipe();
	}
	void RefreshFoodRecipe()
	{

	}

	FoodType GetFoodType()
	{
		const StageData& StageData_ = GlobalGameData::GetCurStageRef();
		std::vector<IngredientType> Data;
		std::vector<IngredientType> Food_Current = Food_Current_;
		for (size_t i = 0; i < StageData_.StageRecipe.size(); i++)
		{
			Data = GlobalGameData::GetFoodData(StageData_.StageRecipe[i]).Ingredient;
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
	//void SetRenderer(std::shared_ptr<GamePlayMoveable> _Moveable/*const std::string& _Name*/)
	//{
	//	Renderer_ = _Moveable->GetFBXMesh();
	//	Renderer_.lock()->SetParent(Moveable_.lock());
	//	const float4& Pos = Renderer_.lock()->GetTransform().GetWorldPosition();
	//	Renderer_.lock()->GetTransform().SetLocalPosition(float4::ZERO);
	//}


	std::vector<IngredientType> Food_Current_;
	std::vector<std::weak_ptr<FoodThumbnail>> Food_Thumbnail_;
	std::weak_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::weak_ptr<GamePlayMoveable> Moveable_;
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

	//HoldDownEnum HoldOn(std::shared_ptr<Player> _Player) override;


	virtual bool CheckCombinFood(IngredientType	_Type) { return false; };

};

