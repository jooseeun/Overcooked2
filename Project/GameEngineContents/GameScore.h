#pragma once
#include "Enums.h"

class GameScore
{
public:
	GameScore();
	~GameScore();

	//���ϰ� : Multiply�� ���� ����
	//int HandOver(std::weak_ptr<

private:
	//��Ż ����
	int TotalScore_ = 0;

	//��������
	int DeliveredScore_ = 0;
	int DeliveredCount_ = 0;

	//�� ����
	int TotalTips_ = 0;

	//���� ����
	int TotalFailScore_ = 0;
	int FailCount_ = 0;
};
