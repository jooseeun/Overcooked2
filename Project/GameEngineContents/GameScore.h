#pragma once
#include "Enums.h"

class GameScore
{
public:
	GameScore();
	~GameScore();

	//리턴값 : Multiply된 팁의 점수
	//int HandOver(std::weak_ptr<

private:
	//토탈 점수
	int TotalScore_ = 0;

	//딸배점수
	int DeliveredScore_ = 0;
	int DeliveredCount_ = 0;

	//팁 점수
	int TotalTips_ = 0;

	//실패 점수
	int TotalFailScore_ = 0;
	int FailCount_ = 0;
};
