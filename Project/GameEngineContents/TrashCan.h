#pragma once
#include "GamePlayStaticObject.h"

//��������
class TrashCan : public GamePlayStaticObject
{
public:
	TrashCan();
	~TrashCan();

	TrashCan(const TrashCan& _Other) = delete;
	TrashCan(TrashCan&& _Other) noexcept = delete;
	TrashCan& operator=(const TrashCan& _Other) = delete;
	TrashCan& operator=(TrashCan&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};
