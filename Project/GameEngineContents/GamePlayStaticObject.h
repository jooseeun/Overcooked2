#pragma once
#include "GamePlayObject.h"

enum class StaticObjectType
{
	CounterTop,
	CounterTop_Corner,
	CounterTop_NoEdge,
	CounterTop_WiZard, //������ �������� ���� ������
	GasRange, //����������
	Bin, //��������
	Sink, //��ũ��
	Servicehatch, //�丮 ���� â��
	FoodBox //���� ���� �ڽ�
};

// ���� :
class GamePlayStuff;
class GamePlayStaticObject : public GamePlayObject
{
protected:
	GamePlayStaticObject();
public:
	// constrcuter destructer
	~GamePlayStaticObject();

	// delete Function
	GamePlayStaticObject(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject(GamePlayStaticObject&& _Other) noexcept = delete;
	GamePlayStaticObject& operator=(const GamePlayStaticObject& _Other) = delete;
	GamePlayStaticObject& operator=(GamePlayStaticObject&& _Other) noexcept = delete;

public:
	Input_PickUpOption Input_PickUp(GamePlayMoveable* _Object) override;

	inline int GetX() const
	{
		return X_;
	}
	inline int GetY() const
	{
		return Y_;
	}

	inline void SetX(int _X)
	{
		X_ = _X;
	}
	inline void SetY(int _Y)
	{
		Y_ = _Y;
	}

	inline void SetStaticObjectType(StaticObjectType _Type)
	{
		MyType_ = _Type;
	}

	inline StaticObjectType GetStaticObjectType()
	{
		return MyType_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override {};
	void End() override {};

	void OnEvent() override {};
	void OffEvent() override {};

	void LevelStartEvent() override {};
	void LevelEndEvent() override {};


private:
	GamePlayStuff* Stuff_Current_;

	StaticObjectType MyType_;

	int X_;
	int Y_;
};


