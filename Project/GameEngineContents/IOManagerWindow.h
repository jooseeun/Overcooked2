#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class IOManagerWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	IOManagerWindow();
	~IOManagerWindow();

	// delete Function
	IOManagerWindow(const IOManagerWindow& _Other) = delete;
	IOManagerWindow(IOManagerWindow&& _Other) noexcept = delete;
	IOManagerWindow& operator=(const IOManagerWindow& _Other) = delete;
	IOManagerWindow& operator=(IOManagerWindow&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:

};

