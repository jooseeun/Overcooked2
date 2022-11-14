#pragma once
#include "UIActor.h"

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

	LevelSelect CurMap_;

	//최고점수 관련
	int HigestScore_ = 20;
	std::shared_ptr<GameEngineFontRenderer> HighestScoreRenderer_;

	//Star & Score
	void CreateStarNScoreRenderer(const float4& _Pos, int _Score);
	std::vector< std::shared_ptr<OverCookedUIRenderer>> StarRenderer_;
	std::vector< std::shared_ptr<GameEngineFontRenderer>> ScoreRenderer_;
	std::vector<int> Score_ = { 350,650,950 };

	//Loading
	std::shared_ptr<OverCookedUIRenderer> LoadingBackRenderer_;
	std::shared_ptr<OverCookedUIRenderer> LoadingFrontRenderer_;
};
