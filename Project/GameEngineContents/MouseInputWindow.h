#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class GlobalMouseInput;
class MouseInputWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	MouseInputWindow();
	~MouseInputWindow();

	// delete Function
	MouseInputWindow(const MouseInputWindow& _Other) = delete;
	MouseInputWindow(MouseInputWindow&& _Other) noexcept = delete;
	MouseInputWindow& operator=(const MouseInputWindow& _Other) = delete;
	MouseInputWindow& operator=(MouseInputWindow&& _Other) noexcept = delete;

	void SetMouseInput(GlobalMouseInput* _Input);

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	
private:
	std::string SelectFolderTexture_;
	GlobalMouseInput* Input_;
	GameEngineActor* InputActor_;
	float Pos_[3];
	float Rot_[3];
	float Scale_[3];

	bool IsChanging_;
};

