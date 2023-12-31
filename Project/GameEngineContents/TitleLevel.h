#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> KevinRenderer_;
	std::shared_ptr<LevelActor> LevelActor_;
	int SubsetDebugIndex_ = 0;

	RenderOption SkyRenderOption_;

	std::shared_ptr<GameEngineActor> Shutter_;
	std::shared_ptr<GameEngineFBXStaticRenderer> ShutterRenderer_;

	std::shared_ptr<GameEngineFBXStaticRenderer> PoleRenderer_;
};
