#pragma once
#include <GameEngineCore/GameEngineActor.h>
class OverCookedUIRenderer;
class SelectStageUIActor : public GameEngineActor
{
	struct LevelSelect
	{
		OverCookedUIRenderer* Parent;
		OverCookedUIRenderer* Select;
		GameEngineFontRenderer* Font;
		int BoarderType; //1,2,3
		OverCookedUIRenderer* Boarder;
		OverCookedUIRenderer* BoarderSelected;
		OverCookedUIRenderer* LevelHighlisht;
	};
public:
	SelectStageUIActor();
	~SelectStageUIActor();

	SelectStageUIActor(const SelectStageUIActor& _Other) = delete;
	SelectStageUIActor(const SelectStageUIActor&& _Other) noexcept = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor& _Ohter) = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void InitRenderer();
	void LoadResource();
	void Update(float _DeltaTime) override;
	void End() override;

	void ResistDebug(std::string_view _Name, GameEngineTransform& Trans);

	OverCookedUIRenderer* CreateUIRenderer(std::string_view _TextrueName);

private:
	OverCookedUIRenderer* EndBackground_ = nullptr;
	OverCookedUIRenderer* Background_ = nullptr;
	OverCookedUIRenderer* Header_ = nullptr;
	OverCookedUIRenderer* ControlGuide_ = nullptr;
	OverCookedUIRenderer* SelectMap_ = nullptr;

	GameEngineFontRenderer* CountDownFont_ = nullptr;

	std::vector<LevelSelect> LevelSelect_;

	float4 DebugPos_;
	float DebugSize_;
};
