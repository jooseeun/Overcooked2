#include "PreCompile.h"
#include "InGameUIActor.h"
#include "GlobalGameData.h"

#include "OverCookedUIRenderer.h"
#include "ContentsUtility.h"
#include "UIDebugGUI.h"

using namespace ContentsUtility;
using namespace UI_Utility;
RecipeManager::RecipeManager()
{
	//
}

RecipeManager::~RecipeManager()
{
	Recipes_.clear();
}

void RecipeManager::Init(std::weak_ptr<InGameUIActor> _ParentActor_, std::function<void(int, int, bool)> _Function, std::function<void(int)> _FailFunction)
{
	ParentActor_ = _ParentActor_;
	HandOverScore_ = _Function;
	FailScore_ = _FailFunction;
}

void RecipeManager::CreateRecipe(FoodType _Type)
{
	Recipe NewRecipe(_Type);

	NewRecipe.ParentRenderer_ = ParentActor_.lock()->CreateUIRenderer("Null.png");
	NewRecipe.ParentRenderer_.lock()->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	//NewRecipe.ParentRenderer_.lock()->Off();

	NewRecipe.BottomParentRenderer_ = ParentActor_.lock()->CreateUIRenderer("Null.png", "BottomParent");
	NewRecipe.BottomParentRenderer_.lock()->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	//NewRecipe.BottomParentRenderer_.lock()->Off();
	NewRecipe.BottomParentRenderer_.lock()->ResistDebug();
	NewRecipe.BottomParentRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	RecipeSetData Data = NewRecipe.GetRecipeSetData();

	//Top Background
	NewRecipe.TopBackgroundRenderer_ = ParentActor_.lock()->CreateUIRenderer("Top_Recipe_Background" + Data.TopBackgroundString + ".png");
	NewRecipe.TopBackgroundRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	//Bar Parent
	NewRecipe.BarParentRenderer_ = ParentActor_.lock()->CreateUIRenderer("Top_Recipe_Background.png", "BarParent");
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetLocalPosition({ Data.BarParentPosNScale.x,Data.BarParentPosNScale.y });
	NewRecipe.BarParentRenderer_.lock()->Off();
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	//BarBackground
	{
		float Inter = 2.f;
		for (int i = 0; i < 3; i++)
		{
			std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer("RecipeBar.png", "Bar");
			NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BarParentRenderer_.lock()->GetTransform());
			float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
			float4 Pos = { (ScaleX + Inter) * (i - 1),0,0 };
			NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
			NewRecipe.BarBackgroundRenderer_.push_back(NewRenderer);
			//NewRenderer->GetTransform().SetLocalPosition()
		}
	}
	//Bar
	{
		float Inter = 2.f;
		for (int i = 0; i < 3; i++)
		{
			std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer("RecipeBar.png", "Bar");
			NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BarParentRenderer_.lock()->GetTransform());
			float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
			float4 Pos = { (ScaleX + Inter) * (i - 1),0,0 };
			NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
			NewRecipe.BarRenderer_.push_back(NewRenderer);
			//NewRenderer->GetTransform().SetLocalPosition()
		}
	}

	//FoodIcon
	NewRecipe.FoodRenderer_ = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.Type), 0.50f);
	NewRecipe.FoodRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	//BottomBackground && Cookery
	{
		//Tool 파악
		if (NewRecipe.Data_.CommonCookery.empty() == true)
		{
			//BottomBackground
			for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
			{
				std::weak_ptr<OverCookedUIRenderer> NewRenderer;
				if (NewRecipe.Data_.Cookery[i] == ToolInfo::None)
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background0.png");
				}
				else
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background1.png");
				}
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
				float4 Pos = Data.IngredientPos[i];
				if (NewRecipe.Data_.Cookery[i] != ToolInfo::None)
				{
					Pos.y -= 22.5f;
				}
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.BottomBackgroundRenderer_.push_back(NewRenderer);
			}

			//Cookery
			for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
			{
				if (NewRecipe.Data_.Cookery[i] == ToolInfo::None)
				{
					continue;
				}
				std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.Cookery[i]), 0.38f);
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
				float4 Pos = Data.IngredientPos[i];
				Pos.y -= 42.f;
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.CookeryRenderer_.push_back(NewRenderer);
			}
		}
		else //commonCookery
		{
			//BottomBackground
			for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
			{
				std::weak_ptr<OverCookedUIRenderer> NewRenderer;
				if (NewRecipe.Data_.Ingredient.size() <= 2)
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background2.png");
				}
				else if (NewRecipe.Data_.Ingredient.size() == 3)
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background3.png");
				}
				else if (NewRecipe.Data_.Ingredient.size() == 4)
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background4.png");
				}
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float4 Pos = { 0,-22.5f,0 };
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.BottomBackgroundRenderer_.push_back(NewRenderer);
			}

			//Cookery
			std::vector<float4> Arr;
			Arr.push_back({ -22.5,0,0 });
			Arr.push_back({ 22.5,0,0 });
			for (int i = 0; i < NewRecipe.Data_.CommonCookery.size(); i++)
			{
				std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.CommonCookery[i]), 0.38f);
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
				float4 Pos = Arr[i];
				Pos.y -= 42.f;
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.CookeryRenderer_.push_back(NewRenderer);
			}
		}
	}

	//IngredientIcon
	{
		for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
		{
			std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.Ingredient[i]), 0.265f);
			NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
			float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
			float4 Pos = Data.IngredientPos[i];
			NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
			NewRecipe.IngredientRenderer_.push_back(NewRenderer);
		}
	}

	//Parent위치이동
	//이걸 왜 여기서 다시하냐고? > 처음에 BarParent의 Sclae을 1.f로 하고 나서 Bar을 변환하지 않으면 Bar의 Transform이 무너져
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetLocalScale({ Data.BarParentPosNScale.w,1.f,1.f });
	//NewRecipe.ParentRenderer_.lock()->GetTransform().SetLocalPosition({ 230.f * (Recipes_.size()),327,0 });
	NewRecipe.ParentRenderer_.lock()->GetTransform().SetLocalPosition({ 1000,327,0 });
	NewRecipe.BottomParentRenderer_.lock()->GetTransform().SetLocalPosition({ 0,36.f,1 });

	//LeftTargetPosSet
	NewRecipe.LeftTargetPos_ = NewRecipe.GetPos();

	Recipes_.push_back(NewRecipe);
}

bool RecipeManager::HandOver(FoodType _Type)
{
	if (_Type == FoodType::None)
	{
		return false;
	}

	//음식 검색
	std::list<Recipe>::iterator _Iter = Recipes_.begin();
	std::vector< std::list<Recipe>::iterator> Vector;
	for (; _Iter != Recipes_.end(); _Iter++)
	{
		if (_Iter->Data_.Type == _Type)
		{
			Vector.push_back(_Iter);
		}
	}

	//std::weak_ptr< Recipe> NewRecipe = std::dynamic_pointer_cast<Recipe>(_Iter);

	//검색한 음식이 없다면 false
	if (Vector.size() == 0)
	{
		return false;
	}

	std::list<Recipe>::iterator MostLeftIter = Vector[0];
	for (int i = 0; i < Vector.size(); i++)
	{
		if (Vector[i]->GetLeftTime() < MostLeftIter->GetLeftTime())
		{
			MostLeftIter = Vector[i];
		}
	}

	MostLeftIter->IsHandOver_ = true;
	std::vector<int> ScoreVector = MostLeftIter->GetScore();
	bool IsMostLeft = false;
	if (Recipes_.begin() == MostLeftIter)
	{
		IsMostLeft = true;
	}
	HandOverScore_(ScoreVector[0], ScoreVector[1], IsMostLeft);
	//퍼센트 기반 팁점수, 기본점수 > 필요한건
	return true;

	//_Iter->ParentRenderer_.lock()->Death();

	//_Iter->FoodRenderer_.lock()->Death();
	//_Iter->TopBackgroundRenderer_.lock()->Death();

	////Bar관련
	//_Iter->BarParentRenderer_.lock()->Death();
	//for (int i = 0; i < _Iter->BarBackgroundRenderer_.size(); i++)
	//{
	//	_Iter->BarBackgroundRenderer_[i].lock()->Death();
	//}
	//for (int i = 0; i < _Iter->BarRenderer_.size(); i++)
	//{
	//	_Iter->BarRenderer_[i].lock()->Death();
	//}

	//_Iter->BottomParentRenderer_.lock()->Death();
	//for (int i = 0; i < _Iter->BottomBackgroundRenderer_.size(); i++)
	//{
	//	_Iter->BottomBackgroundRenderer_[i].lock()->Death();
	//}
	//for (int i = 0; i < _Iter->IngredientRenderer_.size(); i++)
	//{
	//	_Iter->IngredientRenderer_[i].lock()->Death();
	//}
	//for (int i = 0; i < _Iter->CookeryRenderer_.size(); i++)
	//{
	//	_Iter->CookeryRenderer_[i].lock()->Death();
	//}
	//Recipes_.erase(_Iter);
	//return true;
}

void RecipeManager::DeleteRecipe(int _Count)
{
	std::list<Recipe>::iterator _Iter = Recipes_.begin();
	for (int Count = 0; Count < _Count; Count++)
	{
		_Iter++;
	}

	_Iter->ParentRenderer_.lock()->Death();

	_Iter->FoodRenderer_.lock()->Death();
	_Iter->TopBackgroundRenderer_.lock()->Death();

	//Bar관련
	_Iter->BarParentRenderer_.lock()->Death();
	for (int i = 0; i < _Iter->BarBackgroundRenderer_.size(); i++)
	{
		_Iter->BarBackgroundRenderer_[i].lock()->Death();
	}
	for (int i = 0; i < _Iter->BarRenderer_.size(); i++)
	{
		_Iter->BarRenderer_[i].lock()->Death();
	}

	_Iter->BottomParentRenderer_.lock()->Death();
	for (int i = 0; i < _Iter->BottomBackgroundRenderer_.size(); i++)
	{
		_Iter->BottomBackgroundRenderer_[i].lock()->Death();
	}
	for (int i = 0; i < _Iter->IngredientRenderer_.size(); i++)
	{
		_Iter->IngredientRenderer_[i].lock()->Death();
	}
	for (int i = 0; i < _Iter->CookeryRenderer_.size(); i++)
	{
		_Iter->CookeryRenderer_[i].lock()->Death();
	}
	Recipes_.erase(_Iter);
}

//void RecipeManager::DeleteRecipe(std::list<Recipe>::iterator _Iter)
//{
//	_Iter->ParentRenderer_.lock()->Death();
//
//	_Iter->FoodRenderer_.lock()->Death();
//	_Iter->TopBackgroundRenderer_.lock()->Death();
//
//	//Bar관련
//	_Iter->BarParentRenderer_.lock()->Death();
//	for (int i = 0; i < _Iter->BarBackgroundRenderer_.size(); i++)
//	{
//		_Iter->BarBackgroundRenderer_[i].lock()->Death();
//	}
//	for (int i = 0; i < _Iter->BarRenderer_.size(); i++)
//	{
//		_Iter->BarRenderer_[i].lock()->Death();
//	}
//
//	_Iter->BottomParentRenderer_.lock()->Death();
//	for (int i = 0; i < _Iter->BottomBackgroundRenderer_.size(); i++)
//	{
//		_Iter->BottomBackgroundRenderer_[i].lock()->Death();
//	}
//	for (int i = 0; i < _Iter->IngredientRenderer_.size(); i++)
//	{
//		_Iter->IngredientRenderer_[i].lock()->Death();
//	}
//	for (int i = 0; i < _Iter->CookeryRenderer_.size(); i++)
//	{
//		_Iter->CookeryRenderer_[i].lock()->Death();
//	}
//	Recipes_.erase(_Iter);
//}

void RecipeManager::Update(float _DeltaTime)
{
	//이동 할 위치 계산
	{
		float XSize = 8.f;
		std::list<Recipe>::iterator StartIter = Recipes_.begin();
		std::list<Recipe>::iterator EndIter = Recipes_.end();
		for (; StartIter != EndIter; StartIter++)
		{
			//시작Iter의 예외처리
			if (StartIter == Recipes_.begin())
			{
				float Left = -640.f;
				float4 CurPos = StartIter->GetPos();
				CurPos.x = Left;
				CurPos.x += StartIter->GetScale().Half().x;
				StartIter->SetTargetPos(CurPos);
				continue;
			}

			//앞 노드의 위치를 기반으로 현재 위치 찾기
			std::list<Recipe>::iterator FrontNode = StartIter;
			FrontNode--;
			float4 FrontNodeRightPivot = FrontNode->GetTargetPos();
			FrontNodeRightPivot.x += FrontNode->GetScale().Half().x;
			FrontNodeRightPivot.x += StartIter->GetScale().Half().x;
			FrontNodeRightPivot.x += XSize;
			StartIter->SetTargetPos(FrontNodeRightPivot);
		}
	}

	//이동
	{
		std::list<Recipe>::iterator StartIter = Recipes_.begin();
		std::list<Recipe>::iterator EndIter = Recipes_.end();
		for (; StartIter != EndIter; StartIter++)
		{
			float4 Des = StartIter->GetTargetPos();
			float4 CurPos = StartIter->GetPos();

			float4 MovePos = float4::LerpLimit(CurPos, Des, StartIter->AccTime_ * 0.2f);
			//LeftPivot.x -= StartIter->GetScale().Half().x;
			StartIter->SetWorldPosition(MovePos);

			float Length = Des.x - MovePos.x;
			Length = abs(Length);
			if (Length < 20.0f && StartIter->IsPumpHori_ == false)
			{
				StartIter->IsPumpHori_ = true;
				StartIter->ParentRenderer_.lock()->StartPumpHori(1.13f, 10.0f);
			}
			//다 도착하면 레시피 내려가게
			if (Length < 1.0f)
			{
				StartIter->IsRecipeOn_ = true;
			}
		}
	}

	//업데이트
	{
		std::list<Recipe>::iterator StartIter = Recipes_.begin();
		std::list<Recipe>::iterator EndIter = Recipes_.end();
		int RecipeCount = 0;
		for (; StartIter != EndIter; StartIter++)
		{
			if (IsHost_ == true)
			{
				StartIter->UpdateTime(_DeltaTime, true);
			}
			else
			{
				if (GlobalTimeVector_.empty() == false)
				{
					StartIter->UpdateTime(GlobalTimeVector_[RecipeCount], false);
				}
			}
			StartIter->Update(_DeltaTime);
			if (StartIter->GlobalTimer_.IsTimeOver() == true && StartIter->FailFlag_ == false)
			{
				FailScore_(StartIter->Data_.Score);
				StartIter->FailFlag_ = true;
			}
			RecipeCount++;
		}
	}

	//릴리즈
	{
		std::list<Recipe>::iterator StartIter = Recipes_.begin();
		std::list<Recipe>::iterator EndIter = Recipes_.end();
		int Count = 0;
		for (; StartIter != EndIter; StartIter++)
		{
			if (StartIter->IsDead_ == true)
			{
				DeleteRecipe(Count);
				break;
			}
			Count++;
		}
	}
}

void RecipeManager::DebugFunction()
{
	//뒤버그
	UIDebugGUI::Main_->AddFunction("DeleteFront Stage 1-1", std::bind(&RecipeManager::DeleteRecipe, this, 0));
	UIDebugGUI::Main_->AddFunction("HandOverFishSushimi", std::bind(&RecipeManager::HandOver, this, FoodType::FishSushimi));
}

std::vector<float> RecipeManager::GetRecipeTime()
{
	std::vector<float> Vector = { 9999,9999,9999,9999,9999 };
	int Count = 0;
	for (auto i : Recipes_)
	{
		Vector[Count] = i.GlobalTimer_.GetCurTime();
		Count++;
	}
	return Vector;
}

void RecipeManager::UpdateFixedTime(std::vector<float> _Vector)
{
	GlobalTimeVector_ = _Vector;
}

Recipe::Recipe(FoodType _Type)
{
	Data_ = GlobalGameData::GetFoodData(_Type); //복사가 일어남

	float LeftTime = Data_.WaitingTime / 3.f;
	GlobalTimer_.StartTimer(Data_.WaitingTime);
	for (int i = 0; i < 3; i++)
	{
		Timer NewTimer;
		NewTimer.StartTimer(LeftTime);
		BarTimer_.push_back(NewTimer);
	}
}

Recipe::~Recipe()
{
	BarBackgroundRenderer_.clear();
	BarRenderer_.clear();
	BottomBackgroundRenderer_.clear();
	IngredientRenderer_.clear();
}

RecipeSetData Recipe::GetRecipeSetData()
{
	RecipeSetData NewData;

	switch (Data_.Ingredient.size())
	{
	case 1:
	{
		NewData.TopBackgroundString = "0";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.02f };

		std::vector<float4> Arr;
		Arr.push_back({ -22.5,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	case 2:
	{
		NewData.TopBackgroundString = "0";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.02f };
		std::vector<float4> Arr;
		Arr.push_back({ -22.5,0,0 });
		Arr.push_back({ 22.5,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	case 3:
	{
		NewData.TopBackgroundString = "1";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.62f };
		std::vector<float4> Arr;
		Arr.push_back({ -45,0,0 });
		Arr.push_back({ 0,0,0 });
		Arr.push_back({ 45,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	case 4:
	{
		NewData.TopBackgroundString = "2";
		NewData.BarParentPosNScale = { 0.f,23.f,0,2.12f };
		std::vector<float4> Arr;
		Arr.push_back({ -67.5,0,0 });
		Arr.push_back({ -22.5,0,0 });
		Arr.push_back({ 22.5,0,0 });
		Arr.push_back({ 67.5,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	default:
		break;
	}
	return NewData;
}

float4 Recipe::GetPos()
{
	float4 CurPos = ParentRenderer_.lock()->GetTransform().GetWorldPosition();
	return CurPos;
}

float4 Recipe::GetScale()
{
	return TopBackgroundRenderer_.lock()->GetTransform().GetLocalScale();
}

void Recipe::SetWorldPosition(const float4& _WorldPos)
{
	float4 WantMovePos = _WorldPos;
	//WantMovePos.x += TopBackgroundRenderer_.lock()->GetTransform().GetLocalScale().Half().x;
	ParentRenderer_.lock()->GetTransform().SetWorldPosition(WantMovePos);
}

void Recipe::OpenRecipe()
{
	BottomParentRenderer_.lock()->GetTransform().SetLocalPosition({ 0,-52.f,1 });
}

float Recipe::GetLeftTime()
{
	return GlobalTimer_.GetCurTime();
}

std::vector<int> Recipe::GetScore()
{
	std::vector<int> Vector;
	Vector.push_back(Data_.Score);

	int Tips = static_cast<int>((GlobalTimer_.GetCurTime() / GlobalTimer_.Default_Time_) * Data_.Score);
	Vector.push_back(Tips);

	return Vector;
}

void Recipe::Update(float _DeltaTime)
{
	AccTime_ += _DeltaTime;
	FailSyncTimer_.Update(_DeltaTime);
	if (IsRecipeOn_ == true)
	{
		RecipeOnTime_ += _DeltaTime * 3.5f;
		float MoveYPos = GameEngineMath::LerpLimit(36.f, -52.f, RecipeOnTime_);
		BottomParentRenderer_.lock()->GetTransform().SetLocalPosition({ 0,MoveYPos,1 });

		//PumpVerti
		if (MoveYPos < -50.f && IsPumpVerti_ == false)
		{
			IsPumpVerti_ = true;
			BottomParentRenderer_.lock()->StartPumpVerti(1.14f, 10.0f);
		}
	}

	for (int i = 2; i >= 0; i--)
	{
		float Percentage = BarTimer_[i].GetCurTime() / BarTimer_[i].Default_Time_;
		BarRenderer_[i].lock()->UpdateLeftToRight(Percentage);

		float GlobalPercentage = GlobalTimer_.GetCurTime() / GlobalTimer_.Default_Time_;
		BarRenderer_[i].lock()->UpdateLeftTime(GlobalPercentage);
	}

	//부들부들 거리는거
	float GlobalPercentage = GlobalTimer_.GetCurTime() / GlobalTimer_.Default_Time_;
	if (0.001f < GlobalPercentage && GlobalPercentage < 0.18f)
	{
		ParentRenderer_.lock()->StartVibrationHori(3.0f, 21.0f);
		//TopBackgroundRenderer_.lock()->UpdateColor();
	}

	//시간 다되서 빨개지는거
	if (GlobalPercentage <= 0.001f)
	{
		if (FailSyncTimer_.IsTimeOver() == true)
		{
			float4 _PlusColor = { 0,0,0,0 };
			float4 _MulColor = { 1.0f,1.0f,1.0f,1.0f };

			Timeout_IterTime_ += _DeltaTime * 2.5f;
			if (Timeout_IterTime_ < 1.f)
			{
				_MulColor.y = 1 - Timeout_IterTime_;
				_MulColor.z = 1 - Timeout_IterTime_;
			}
			else if (Timeout_IterTime_ >= 1.f && Timeout_IterTime_ < 2.f)
			{
				_MulColor.y = Timeout_IterTime_ - 1.f;
				_MulColor.z = Timeout_IterTime_ - 1.f;
			}
			else//시간이 다됬으면
			{
				FailSyncTimer_.StartTimer(3.0f);
				FailFlag_ = false;
				Timeout_IterTime_ = 0.f;
				_MulColor.y = 1.f;
				_MulColor.z = 1.f;
				GlobalTimer_.StartTimer(Data_.WaitingTime);
				for (int i = 0; i < 3; i++)
				{
					BarTimer_[i].StartTimer();
				}
			}

			for (int i = 0; i < IngredientRenderer_.size(); i++)
			{
				IngredientRenderer_[i].lock()->UpdateColor(_PlusColor, _MulColor);
			}
			TopBackgroundRenderer_.lock()->UpdateColor(_PlusColor, _MulColor);
			FoodRenderer_.lock()->UpdateColor(_PlusColor, _MulColor);
			for (int i = 0; i < BottomBackgroundRenderer_.size(); i++)
			{
				BottomBackgroundRenderer_[i].lock()->UpdateColor(_PlusColor, _MulColor);
			}
		}
	}

	//제출해서 초록색
	if (IsHandOver_ == true && IsDead_ == false)
	{
		float4 _PlusColor = { 0,0,0,0 };
		float4 _MulColor = { 1.0f,1.0f,1.0f,1.0f };

		HandOver_IterTime_ += _DeltaTime * 2.5f;
		if (HandOver_IterTime_ < 1.f)
		{
			_MulColor.x = 1 - HandOver_IterTime_;
			_MulColor.z = 1 - HandOver_IterTime_;
		}
		else if (HandOver_IterTime_ >= 1.f && HandOver_IterTime_ < 2.f)
		{
			_MulColor.x = HandOver_IterTime_ - 1.f;
			_MulColor.z = HandOver_IterTime_ - 1.f;
			_MulColor.w = 2.f - HandOver_IterTime_;
		}
		else//시간이 다됬으면
		{
			IsDead_ = true;
		}

		for (int i = 0; i < IngredientRenderer_.size(); i++)
		{
			IngredientRenderer_[i].lock()->UpdateColor(_PlusColor, _MulColor);
		}
		TopBackgroundRenderer_.lock()->UpdateColor(_PlusColor, _MulColor);
		FoodRenderer_.lock()->UpdateColor(_PlusColor, _MulColor);
		for (int i = 0; i < BottomBackgroundRenderer_.size(); i++)
		{
			BottomBackgroundRenderer_[i].lock()->UpdateColor(_PlusColor, _MulColor);
		}
		for (int i = 0; i < BarRenderer_.size(); i++)
		{
			BarRenderer_[i].lock()->UpdateColor(_PlusColor, _MulColor);
		}
		for (int i = 0; i < BarBackgroundRenderer_.size(); i++)
		{
			BarBackgroundRenderer_[i].lock()->UpdateColor(_PlusColor, _MulColor);
		}
	}
}

void Recipe::UpdateTime(float _DeltaTime, bool _IsHost)
{
	//건네면 시간이 흐르지 않는다
	if (IsHandOver_ == false)
	{
		if (GlobalTimer_.IsTimeOver() == false)
		{
			if (_IsHost == true)
			{
				GlobalTimer_.Update(_DeltaTime);
			}
			else
			{
				GlobalTimer_.UpdateFixedTime(_DeltaTime);
			}
		}

		std::vector<float> TimeVector;
		float TimeValue = GlobalTimer_.GetCurTime();
		for (int i = 0; i < 3; i++)
		{
			float CheckValue = TimeValue;
			CheckValue -= BarTimer_[0].Default_Time_;
			if (CheckValue <= 0.f)
			{
				TimeVector.push_back(TimeValue);
				i++;
				for (; i < 3; i++)
				{
					TimeVector.push_back(0.f);
				}
				break;
			}
			TimeValue = CheckValue;
			TimeVector.push_back(BarTimer_[0].Default_Time_);
		}

		if (BarTimer_[2].IsTimeOver() == false)
		{
			BarTimer_[2].UpdateFixedTime(TimeVector[2]);
		}
		else
		{
			if (BarTimer_[1].IsTimeOver() == false)
			{
				BarTimer_[1].UpdateFixedTime(TimeVector[1]);
			}
			else
			{
				if (BarTimer_[0].IsTimeOver() == false)
				{
					BarTimer_[0].UpdateFixedTime(TimeVector[0]);
				}
			}
		}
	}
}