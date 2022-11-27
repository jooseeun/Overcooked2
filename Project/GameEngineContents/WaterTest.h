#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class WaterTest : public GameEngineActor
{
public:
	// constrcuter destructer
	WaterTest();
	~WaterTest();

	// delete Function
	WaterTest(const WaterTest& _Other) = delete;
	WaterTest(WaterTest&& _Other) noexcept = delete;
	WaterTest& operator=(const WaterTest& _Other) = delete;
	WaterTest& operator=(WaterTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineTextureRenderer> Renderer_;
	std::shared_ptr<GameEngineTextureRenderer> Renderer2_;
	std::shared_ptr<GameEngineTextureRenderer> Renderer3_;

};
