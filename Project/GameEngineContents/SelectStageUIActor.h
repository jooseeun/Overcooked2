#pragma once
#include <GameEngineCore/GameEngineActor.h>
class OverCookedUIRenderer;
class SelectStageUIActor : public GameEngineActor
{
	struct LevelSelect
	{
		int Index; // 처음 등록했을 때 Index
		int CurPos;
		OverCookedUIRenderer* Parent;
		OverCookedUIRenderer* Select;
		GameEngineFontRenderer* Font;
		int BoarderType; //1,2,3
		OverCookedUIRenderer* Boarder;
		OverCookedUIRenderer* BoarderSelected;
		OverCookedUIRenderer* LevelHighlisht;
	};

	struct PlayerIcon
	{
		int Index; //0 ~ 3
		OverCookedUIRenderer* Parent;
		OverCookedUIRenderer* Hat;
		OverCookedUIRenderer* NameBox;

		std::string Name;
		GameEngineFontRenderer* CountFont;
		GameEngineFontRenderer* NameFont;
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
	void CreatePlayerIcon(int _Index, std::string_view _Name);
	void LoadResource();
	void Update(float _DeltaTime) override;
	void MovingMap(float _DeltaTime);
	void EndChange();
	void End() override;

	void ResistDebug(std::string_view _Name, GameEngineTransform& Trans);

	void CreateLevelSelect(std::string_view _MapFileName, int _BoarderType, std::string_view _Text, int _Index);

	OverCookedUIRenderer* CreateUIRenderer(std::string_view _TextrueName);

private:
	OverCookedUIRenderer* EndBackground_ = nullptr;
	OverCookedUIRenderer* Background_ = nullptr;
	OverCookedUIRenderer* Header_ = nullptr;
	OverCookedUIRenderer* ControlGuide_ = nullptr;
	OverCookedUIRenderer* SelectMap_ = nullptr;

	std::vector<OverCookedUIRenderer*> ArrowRenderer_; // 화살표 렌더러
	std::vector<OverCookedUIRenderer*> MaskBackground_;

	GameEngineFontRenderer* CountDownFont_ = nullptr;

	std::vector<LevelSelect> LevelSelect_;

	float Interval_ = 360.f;

	int StartIndex_ = 3; //맨 처음 화면에 보이는 Index

	//방향키로 이동시 필요한 멤버들
	float CurInterval_Iter_ = 0.f;
	std::vector<float4> PrevPos_;
	bool IsChanging_ = false;
	void StartChange(int _Dir);
	void ShowSelectEffect(int _Dir);
	bool IsChanging();
	int MovingDir_ = 0;

	//플레이어 아이콘
	int PlayerCount_ = 1; //현재 접속한 플레이어 수
	std::vector<PlayerIcon> Icons_;

	float4 DebugPos_;
	float DebugSize_;
};
