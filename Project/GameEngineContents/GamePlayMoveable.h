#pragma once
#include "GamePlayStuff.h"
// ���� :

enum class ObjectMoveableType
{
	None,
	Food,
	Equipment
};
class GamePlayMoveable : public GamePlayStuff
{
public:
	// constrcuter destructer
	GamePlayMoveable();
	~GamePlayMoveable();

	// delete Function
	GamePlayMoveable(const GamePlayMoveable& _Other) = delete;
	GamePlayMoveable(GamePlayMoveable&& _Other) noexcept = delete;
	GamePlayMoveable& operator=(const GamePlayMoveable& _Other) = delete;
	GamePlayMoveable& operator=(GamePlayMoveable&& _Other) noexcept = delete;

public:
	inline Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) override
	{
		return Input_PickUpOption::NoResponse;
	}

	inline ObjectMoveableType GetObjectMoveableType() const
	{
		if (Enum_ObjectMoveableType_ == ObjectMoveableType::None)
		{
			MsgBoxAssert("Object�� ObjectType�� �������� �ʾҽ��ϴ�. (GamePlayStuff::Enum_ObjectStuffType_ ����)");
		}
		return Enum_ObjectMoveableType_;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


protected:

	inline void SetObjectMoveableType(ObjectMoveableType _Type)
	{
		Enum_ObjectMoveableType_ = _Type;
	}

private:
	ObjectMoveableType Enum_ObjectMoveableType_;
};

