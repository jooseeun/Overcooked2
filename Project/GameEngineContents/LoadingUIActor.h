#pragma once
#include "UIActor.h"
#include "GlobalGameData.h"

class OverCookedUIRenderer;
class LoadingUIActor : public UIActor
{
	struct LevelSelect
	{
		int Index; // 처음 등록했을 때 Index
		std::shared_ptr<OverCookedUIRenderer> Parent;
		std::shared_ptr<OverCookedUIRenderer> Select;
		std::shared_ptr<GameEngineFontRenderer> Font;
		std::shared_ptr<OverCookedUIRenderer> BoarderSelected;
	};
public:
	LoadingUIActor();
	~LoadingUIActor();

	LoadingUIActor(const LoadingUIActor& _Other) = delete;
	LoadingUIActor(const LoadingUIActor&& _Other) noexcept = delete;
	LoadingUIActor& operator=(const LoadingUIActor& _Ohter) = delete;
	LoadingUIActor& operator=(const LoadingUIActor&& _Other) noexcept = delete;

	void StartLoad();
protected:
	void UIStart() override;
	void InitRenderer();
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;
private:
	std::shared_ptr<OverCookedUIRenderer> EndBackground_;
	std::shared_ptr<OverCookedUIRenderer> Background_;
	std::shared_ptr<OverCookedUIRenderer> Header_;
	std::vector<std::shared_ptr<OverCookedUIRenderer>> MaskBackground_;

	LevelSelect CurStage_;

	//최고점수 관련
	int HigestScore_ = 20;
	std::shared_ptr<GameEngineFontRenderer> HighestScoreRenderer_;

	//Star & Score
	std::vector<int> Score_ = { 350,650,950 };
	void CreateStarNScoreRenderer(const float4& _Pos, int _Score);
	std::vector< std::shared_ptr<OverCookedUIRenderer>> StarRenderer_;
	std::vector< std::shared_ptr<GameEngineFontRenderer>> ScoreRenderer_;

	//Info
	std::string StageName_;
	Thema StageThema_;

	//Loading
	std::shared_ptr<OverCookedUIRenderer> LoadingBackRenderer_;
	std::shared_ptr<OverCookedUIRenderer> LoadingFrontRenderer_;

	//Time
	float AccTime_ = 0.f;

	//bool
	bool IsLoadFirst_ = true;//최초의 로딩
};
