#pragma once
#include "GamePlayObject.h"
#include "Enums.h"

// Ό³Έν :
class GamePlayStaticObject : public GamePlayObject
{
protected:
	GamePlayStaticObject();
public:
	// constrcuter destructer
	~GamePlayStaticObject();

	// delete Function
	GamePlayStaticObject(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject(GamePlayStaticObject&& _Other) noexcept = delete;
	GamePlayStaticObject& operator=(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject& operator=(GamePlayStaticObject&& _Other) noexcept = delete;

public:

	inline void SetStaticObjectType(MapObjType _Type)
	{
		MyType_ = _Type;
	}

	inline MapObjType GetStaticObjectType()
	{
		return MyType_;
	}

	//inline ToolInfo GetToolInfo() const
	//{

	//}

	inline void SetToolPos(float4& _Pos)
	{
		ToolPos_ = _Pos;
	}

	virtual float4 GetToolPos() 
	{
		ToolPos_ = GetTransform().GetWorldPosition() + float4{ 0, 50.f };

		return ToolPos_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};

	float4 ToolPos_;

private:

	MapObjType MyType_;



	// Bloom
public:
	void SetBloomEffectOff() override;
	void SetBloomEffectOn() override;

	//
};


