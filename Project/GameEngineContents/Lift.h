#pragma once
#include "GamePlayMapObject.h"

enum class LIFTSTATE
{
	UP,
	WAIT,
	DOWN
};

// ���� :
class Lift : public GamePlayFloor
{
public:
	// constrcuter destructer
	Lift();
	~Lift();

	// delete Function
	Lift(const Lift& _Other) = delete;
	Lift(Lift&& _Other) noexcept = delete;
	Lift& operator=(const Lift& _Other) = delete;
	Lift& operator=(Lift&& _Other) noexcept = delete;

protected:    
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float MoveTime_; //����Ʈ �̵� ���� �ð�
	float WaitingTime_; //����Ʈ �������� �ö� �� ��� �ð�

	float Speed_;

	LIFTSTATE LiftState_;

	float LerpTime_;

	void SetServerCookingGage(std::shared_ptr<ObjectCookingGagePacket> _Packet) override;
};

