#pragma once
#include "GamePlayStaticObject.h"

//�丮 ���� â��
class Servicehatch : public GamePlayStaticObject
{
public:
	Servicehatch();
	~Servicehatch();

	Servicehatch(const Servicehatch& _Other) = delete;
	Servicehatch(Servicehatch&& _Other) noexcept = delete;
	Servicehatch& operator=(const Servicehatch& _Other) = delete;
	Servicehatch& operator=(Servicehatch&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

