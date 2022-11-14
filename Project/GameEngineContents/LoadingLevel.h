#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class UIDebugGUI;
class LoadingUIActor;
class LoadingLevel : public GameEngineLevel
{
public:
	LoadingLevel();
	~LoadingLevel();

	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(const LoadingLevel&& _Other) = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr< LoadingUIActor> UIActor_;
};
