#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayFood.h"
#include "GamePlayTool.h"
#include "Enums.h"

enum class FoodBoxType
{
	Normal,
	Winter,	// 2-1 맵 전용
	Max,
};

//음식 스폰 박스
class FoodBox;
class Tool_FoodBox : public GamePlayTool
{
	friend FoodBox;
public:
	// constrcuter destructer
	Tool_FoodBox();
	~Tool_FoodBox();

	// delete Function
	Tool_FoodBox(const Tool_FoodBox& _Other) = delete;
	Tool_FoodBox(Tool_FoodBox&& _Other) noexcept = delete;
	Tool_FoodBox& operator=(const Tool_FoodBox& _Other) = delete;
	Tool_FoodBox& operator=(Tool_FoodBox&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	inline void SetFoodBox(std::shared_ptr<FoodBox> _Box)
	{
		Box_ = _Box;
	}

	std::weak_ptr<FoodBox> Box_;
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
	IngredientType Type_;

};

class FoodBox : public GamePlayStaticObject
{
public:
	FoodBox();
	~FoodBox();

	FoodBox(const FoodBox& _Other) = delete;
	FoodBox(FoodBox&& _Other) noexcept = delete;
	FoodBox& operator=(const FoodBox& _Other) = delete;
	FoodBox& operator=(FoodBox&& _Other) noexcept = delete;

	inline void SetFoodBoxType(FoodBoxType _Type)
	{
		Type_ = _Type;
	}

	inline FoodBoxType GetFoodBoxType()
	{
		return Type_;
	}

	void SetFoodBoxMesh(FoodBoxType _Type);

	inline void SwitchIsInteraction()
	{
		IsInteraction_ = !IsInteraction_;
	}
	void SetFoodType(IngredientType _Type);

	IngredientType GetFoodType()
	{
		return std::dynamic_pointer_cast<Tool_FoodBox>(GetStuff())->Type_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineActor> Lid_;

	std::shared_ptr<GameEngineFBXStaticRenderer> LidRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> Renderer_;

private:
	bool IsInteraction_;
	bool IsOpen_;
	float Angle_;

	FoodBoxType Type_;

	void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override
	{
		Packet->MapObjData = GetStaticObjectType();
		Packet->IngredientData = GetStuff()->CastThis<Tool_FoodBox>()->Type_;
	}


	void SetHighlightEffectOn() override
	{
		GamePlayStaticObject::SetHighlightEffectOn();
		LidRenderer_->SetAllPixelDataPlusColor(float4(0.2f, 0.2f, 0.2f, 0.0f));

	}

	void SetHighlightEffectOff() override
	{
		GamePlayStaticObject::SetHighlightEffectOff();
		LidRenderer_->SetAllPixelDataPlusColor(float4(0, 0, 0, 0));

	}

};
