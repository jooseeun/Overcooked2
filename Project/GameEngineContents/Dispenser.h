#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

enum class DispenserType
{
	Type1,
	Type2,
};

// Ό³Έν :
class Dispenser : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Dispenser();
	~Dispenser();

	// delete Function
	Dispenser(const Dispenser& _Other) = delete;
	Dispenser(Dispenser&& _Other) noexcept = delete;
	Dispenser& operator=(const Dispenser& _Other) = delete;
	Dispenser& operator=(Dispenser&& _Other) noexcept = delete;

public:
	inline DispenserType GetDispenserType()
	{
		return Type_;
	}

	inline void SetDispenserType(DispenserType _Type)
	{
		Type_ = _Type;
	}

	void SettingIngredientList(DispenserType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	DispenserType Type_;


};

class Tool_Dispenser : public GamePlayTool
{

public:
	// constrcuter destructer
	Tool_Dispenser();
	~Tool_Dispenser();

	// delete Function
	Tool_Dispenser(const Tool_Dispenser& _Other) = delete;
	Tool_Dispenser(Tool_Dispenser&& _Other) noexcept = delete;
	Tool_Dispenser& operator=(const Tool_Dispenser& _Other) = delete;
	Tool_Dispenser& operator=(Tool_Dispenser&& _Other) noexcept = delete;

	void SettingIngredientList(DispenserType _Type);
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	bool FirstTimeCheck_;
	float Delay_;
	int Index_;
	std::weak_ptr<GamePlayStaticObject> Front_StaticObject_;
	CollisionReturn GetFrontStaticObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	std::vector<IngredientType> IngredientList_;
};

