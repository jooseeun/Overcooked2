#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsUtility.h"

using namespace ContentsUtility;

class OverCookedUIRenderer;
class SelectStageUIActor : public GameEngineActor
{
	struct LevelSelect
	{
		void On();
		void Off();
		int Index; // 처음 등록했을 때 Index
		int CurPos;
		std::shared_ptr<OverCookedUIRenderer> Parent;
		std::shared_ptr<OverCookedUIRenderer> Select;
		std::shared_ptr<GameEngineFontRenderer> Font;
		int BoarderType; //1,2,3
		std::shared_ptr<OverCookedUIRenderer> Boarder;
		std::shared_ptr<OverCookedUIRenderer> BoarderSelected;
		std::shared_ptr<OverCookedUIRenderer> LevelHighlisht;
	};

	struct PlayerIcon
	{
	public:
		void Off();
		void On();
		int Index; //0 ~ 3
		std::shared_ptr<OverCookedUIRenderer> Parent;
		std::shared_ptr<OverCookedUIRenderer> Hat;
		std::shared_ptr<OverCookedUIRenderer> NameBox;

		std::string Name;
		std::shared_ptr<GameEngineFontRenderer> CountFont;
		std::shared_ptr<GameEngineFontRenderer> NameFont;
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
	void UpdatePlayerIcon();
	void MovingMap(float _DeltaTime);
	void StartSelectMap();
	void EndChange();
	void End() override;

	void ResistDebug(std::string_view _Name, GameEngineTransform& Trans);

	void CreateLevelSelect(std::string_view _MapFileName, int _BoarderType, std::string_view _Text, int _Index);

	std::shared_ptr<OverCookedUIRenderer> CreateUIRenderer(std::string_view _TextrueName);

private:
	std::shared_ptr<OverCookedUIRenderer> EndBackground_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> Background_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> Header_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> ControlGuide_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> SelectMap_ = nullptr;

	std::vector<std::shared_ptr<OverCookedUIRenderer>> ArrowRenderer_; // 화살표 렌더러
	std::vector<std::shared_ptr<OverCookedUIRenderer>> MaskBackground_;

	std::shared_ptr<GameEngineFontRenderer> CountDownFont_ = nullptr;

	//Transition
	std::shared_ptr<OverCookedUIRenderer> BlackRenderer_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> TransitionIcon_ = nullptr;

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

	//페이즈 관련
	int Phase_ = 0;

	//카운트다운 관련
	Timer CountDown_ = 4.5f;
	void StartLevelChange(int _A);

	float4 DebugPos_;
	float DebugSize_;
};
