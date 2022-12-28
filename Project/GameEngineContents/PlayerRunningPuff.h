#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineFBXStaticRenderer;
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

	void inline SetScale(float _Scale)
	{
		Scale_ = _Scale;
		RunningPuffRenderer_->GetTransform().SetLocalScale(RunningPuffRenderer_->GetTransform().GetLocalScale() * Scale_);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	std::shared_ptr< GameEngineFBXStaticRenderer> RunningPuffRenderer_;
	float Scale_;
	float4 OriginalScale_;
};

