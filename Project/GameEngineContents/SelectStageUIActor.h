#pragma once
#include "UIActor.h"

class SelectStageUIActor : public UIActor
{
	struct LevelSelect
	{
		void On();
		void Off();
		int Index; // ó�� ������� �� Index
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
	SelectStageUIActor(SelectStageUIActor&& _Other) noexcept = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor& _Other) = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor&& _Other) = delete;

protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;

private:
	void InitRenderer();
	void CreatePlayerIcon(int _Index, std::string_view _Name);
	void UpdatePlayerIcon();
	void MovingMap(float _DeltaTime);
	void StartSelectMap();
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

	std::vector<std::shared_ptr<OverCookedUIRenderer>> ArrowRenderer_; // ȭ��ǥ ������

	std::shared_ptr<GameEngineFontRenderer> CountDownFont_ = nullptr;

	std::vector<LevelSelect> LevelSelect_;

	float Interval_ = 360.f;

	int StartIndex_ = 3; //�� ó�� ȭ�鿡 ���̴� Index

	//����Ű�� �̵��� �ʿ��� �����
	float CurInterval_Iter_ = 0.f;
	std::vector<float4> PrevPos_;
	bool IsChanging_ = false;
	void StartChange(int _Dir);
	void ShowSelectEffect(int _Dir);
	bool IsChanging();
	int MovingDir_ = 0;

	//�÷��̾� ������
	int PlayerCount_ = 1; //���� ������ �÷��̾� ��
	std::vector<PlayerIcon> Icons_;

	//������ ����
	int Phase_ = 0;

	//ī��Ʈ�ٿ�&Transition ����
	Timer CountDown_ = 4.5f;
	void StartTransition(int _A);
};
