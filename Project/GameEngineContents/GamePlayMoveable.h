#pragma once
#include "GamePlayStuff.h"
#include "Player.h"
// 설명 :

enum class ObjectMoveableType
{
	None,
	Food,
	Equipment
};
enum class CookedStat
{
	NoResponse,
	Cooking,
	End
};
class GamePlayMoveable : public GamePlayStuff
{
	friend class GamePlayTool;
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

	inline ObjectMoveableType GetObjectMoveableType() const
	{
		if (Enum_ObjectMoveableType_ == ObjectMoveableType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectStuffType_ 설정)");
		}
		return Enum_ObjectMoveableType_;
	}

	inline float GetCookingGage() const
	{
		return CookingGage_;
	}
//	HoldDownEnum CalculateMoveable(std::shared_ptr<GamePlayMoveable> _Other);

protected:
	void Start() override;
	//void Update(float _DeltaTime) final;
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
	float CookingGage_;
};

