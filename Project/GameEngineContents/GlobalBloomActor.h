#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GlobalBloomActor : public GameEngineActor
{
public:
	// constrcuter destructer
	GlobalBloomActor();
	~GlobalBloomActor();

	// delete Function
	GlobalBloomActor(const GlobalBloomActor& _Other) = delete;
	GlobalBloomActor(GlobalBloomActor&& _Other) noexcept = delete;
	GlobalBloomActor& operator=(const GlobalBloomActor& _Other) = delete;
	GlobalBloomActor& operator=(GlobalBloomActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineTextureRenderer> BloomEffectRenderer_;
	PixelData PixelData_;

};

