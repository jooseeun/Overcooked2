#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineFBXStaticRenderer;
class LevelActor : public GameEngineActor
{

public:
	LevelActor();
	~LevelActor();

	LevelActor(const LevelActor& _Other) = delete;
	LevelActor(LevelActor&& _Other) noexcept = delete;
	LevelActor& operator=(const LevelActor& _Other) = delete;
	LevelActor& operator=(LevelActor&& _Other) noexcept = delete;

	void SetLevelMesh(std::string_view _Name)
	{
		Renderer_->SetFBXMesh(_Name.data(), "DeferredTexture");
		Renderer_->GetTransform().SetWorldScale({ 40, 40, 40 });
	};

	std::shared_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}

protected:
	void Start() override;
	void Update(float _Update) override;
	void End() override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

