#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <functional>

// Ό³Έν :
class LightTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LightTestLevel();
	~LightTestLevel();

	// delete Function
	LightTestLevel(const LightTestLevel& _Other) = delete;
	LightTestLevel(LightTestLevel&& _Other) noexcept = delete;
	LightTestLevel& operator=(const LightTestLevel& _Other) = delete;
	LightTestLevel& operator=(LightTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delat) override;
	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineLight> LightObject;

};

