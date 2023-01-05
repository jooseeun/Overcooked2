#pragma once
#include "UIActor.h"
#include "GameServerObject.h"

class SelectStageUIActor : public UIActor , public GameServerObject
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

public:
	SelectStageUIActor();
	~SelectStageUIActor();

	SelectStageUIActor(const SelectStageUIActor& _Other) = delete;
	SelectStageUIActor(SelectStageUIActor&& _Other) noexcept = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor& _Other) = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor&& _Other) = delete;


	void ServerRelease();
	void ServerInit();

protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;

private:
	void InitRenderer();
	void MovingMap(float _DeltaTime);
	void StartSelectMap();
	void SetCurStage(int _Index);
	void EndChange();

	void CreateLevelSelect(std::string_view _MapFileName, int _BoarderType, std::string_view _Text, int _Index);

private:

private:
	std::shared_ptr<OverCookedUIRenderer> EndBackground_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> Background_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> Header_ = nullptr;
	std::vector<std::shared_ptr<OverCookedUIRenderer>> MaskBackground_;

	std::shared_ptr<OverCookedUIRenderer> ControlGuide_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> SelectMap_ = nullptr;

	std::vector<std::shared_ptr<OverCookedUIRenderer>> ArrowRenderer_; // 화살표 렌더러

	std::shared_ptr<GameEngineFontRenderer> CountDownFont_ = nullptr;

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

	//페이즈 관련
	int Phase_ = 0;

	//카운트다운&Transition 관련
	Timer CountDown_ = 4.5f;
	void StartTransition(int _A);

	//서버용 변수
	int InputBuffer_ = -2;
};
