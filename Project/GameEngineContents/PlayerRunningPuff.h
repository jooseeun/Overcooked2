#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class PlayerRunningPuff : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerRunningPuff();
	~PlayerRunningPuff();

	// delete Function
	PlayerRunningPuff(const PlayerRunningPuff& _Other) = delete;
	PlayerRunningPuff(PlayerRunningPuff&& _Other) noexcept = delete;
	PlayerRunningPuff& operator=(const PlayerRunningPuff& _Other) = delete;
	PlayerRunningPuff& operator=(PlayerRunningPuff&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	std::shared_ptr< GameEngineTextureRenderer> RunningPuffRenderer_;
	PixelData Renderer;
};

