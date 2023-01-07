#pragma once
#include "UIActor.h"

class TitleLevelActor : public UIActor
{
	struct MenuButton
	{
		std::weak_ptr<OverCookedUIRenderer> Parent;

		std::weak_ptr<OverCookedUIRenderer> Button;
		std::weak_ptr<OverCookedUIRenderer> Button_Disabled;
		std::weak_ptr<OverCookedUIRenderer> Button_Highlight;

		std::weak_ptr<GameEngineFontRenderer> Font;

		std::function<void()> CallBack;

		bool IsDisabled = false;
		bool IsHighlighted = false;

		void Disable();
		void Enable();
		void Highlight();
	};
public:
	TitleLevelActor();
	~TitleLevelActor();

	TitleLevelActor(const TitleLevelActor& _Other) = delete;
	TitleLevelActor(const TitleLevelActor&& _Other) noexcept = delete;
	TitleLevelActor& operator=(const TitleLevelActor& _Ohter) = delete;
	TitleLevelActor& operator=(const TitleLevelActor&& _Other) noexcept = delete;

protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UpdateInput();
	void UIEnd() override;

private:

	void ChangeLevel();
	void CreateButton(std::string_view _Font, const float4& _Pos, std::function<void()> _Function);

	std::vector< MenuButton> AllButtons_;

	int CurNum_ = 0;

	std::vector< std::weak_ptr< GameEngineFBXAnimationRenderer>> PlayerMesh_;
};
