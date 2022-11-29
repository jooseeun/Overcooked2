#pragma once
#include "GamePlayMoveable.h"

// 설명 :
enum class ObjectEquipmentType
{
	None,
	Dish,
	Bowl,
	Using
};
class GamePlayEquipment : public GamePlayMoveable
{
public:
	// constrcuter destructer
	GamePlayEquipment();
	~GamePlayEquipment();

	// delete Function
	GamePlayEquipment(const GamePlayEquipment& _Other) = delete;
	GamePlayEquipment(GamePlayEquipment&& _Other) noexcept = delete;
	GamePlayEquipment& operator=(const GamePlayEquipment& _Other) = delete;
	GamePlayEquipment& operator=(GamePlayEquipment&& _Other) noexcept = delete;

	inline ObjectEquipmentType GetObjectEquipmentType() const
	{
		if (Enum_ObjectEquipmentType_ == ObjectEquipmentType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectEquipmentType_ 설정)");
		}
		return Enum_ObjectEquipmentType_;
	}


protected:
	void Start() override;
	//void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


protected:

	inline void SetObjectEquipmentType(ObjectEquipmentType _Type)
	{
		Enum_ObjectEquipmentType_ = _Type;
	}
private:
	ObjectEquipmentType Enum_ObjectEquipmentType_;

};

