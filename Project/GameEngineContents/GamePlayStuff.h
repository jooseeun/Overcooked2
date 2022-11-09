#pragma once
#include "GamePlayObject.h"

// 설명 :
enum class ObjectStuffType
{
	None,
	Tool,
	Moveable,
};
class GamePlayStuff : public GamePlayObject
{
protected:
	GamePlayStuff();
public:
	// constrcuter destructer
	~GamePlayStuff();

	// delete Function
	GamePlayStuff(const GamePlayStuff& _Other) = delete;
	GamePlayStuff(GamePlayStuff&& _Other) noexcept = delete;
	GamePlayStuff& operator=(const GamePlayStuff& _Other) = delete;
	GamePlayStuff& operator=(GamePlayStuff&& _Other) noexcept = delete;

	inline ObjectStuffType GetObjectStuffType() const
	{
		if (Enum_ObjectStuffType_ == ObjectStuffType::None)
		{
			MsgBoxAssert("Object의 ObjectType이 설정되지 않았습니다. (GamePlayStuff::Enum_ObjectStuffType_ 설정)");
		}
		return Enum_ObjectStuffType_;
	}

	inline ToolInfo GetToolInfoType()
	{
		return Enum_ToolInfo_;
	}

	inline void SetToolInfoType(ToolInfo _Info)
	{
		Enum_ToolInfo_ = _Info;
	}


public: 
	void SetParentObject(GamePlayObject* _Object);      // Nullptr 검사 필요


protected:

	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};



protected:

	inline void SetObjectStuffType(ObjectStuffType _Type)
	{
		Enum_ObjectStuffType_ = _Type;
	}

	// Enum
private:
	ObjectStuffType Enum_ObjectStuffType_;

private:
	ToolInfo Enum_ToolInfo_;
};

