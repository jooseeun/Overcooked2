#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsUtility.h"

using namespace ContentsUtility;
class OverCookedUIRenderer;
class UIActor : public GameEngineActor
{
public:
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
		std::shared_ptr<GameEngineFBXAnimationRenderer> PlayerMesh;
	};
	UIActor();
	~UIActor();

	UIActor(const UIActor& _Other) = delete;
	UIActor(const UIActor&& _Other) noexcept = delete;
	UIActor& operator=(const UIActor& _Ohter) = delete;
	UIActor& operator=(const UIActor&& _Other) noexcept = delete;

	void StartFadeOut();
	void StartFadeIn();

	std::shared_ptr<OverCookedUIRenderer> CreateUIRenderer(std::string_view _TextrueName);
	std::shared_ptr<OverCookedUIRenderer> CreateUIRenderer(std::string_view _TextrueName, std::string_view _RendererName);
	std::shared_ptr<OverCookedUIRenderer> CreateUIRenderer(std::string_view _TextrueName, float _ScaleRatio);
protected:
	virtual void UIStart() = 0;
	virtual void UIUpdate(float _DeltaTime) = 0;
	virtual void UIEnd() { };

	void ResistDebug(std::string_view _Name, GameEngineTransform& Trans);

	void CreatePlayerIcon(int _Index, std::string_view _Name);
	void UpdatePlayerIcon(float _DeltaTime);

	//Transition
	std::shared_ptr<OverCookedUIRenderer> BlackRenderer_ = nullptr;
	std::shared_ptr<OverCookedUIRenderer> TransitionIcon_ = nullptr;

	//플레이어 아이콘
	int PlayerCount_ = 1; //현재 접속한 플레이어 수
	std::vector<PlayerIcon> Icons_;
private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void InitTransitionRenderer();
};
