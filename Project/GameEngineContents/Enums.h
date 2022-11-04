#pragma once

enum class CollisionOrder
{
	Default,
	Mouse,
	Max,



	// Object
	Object_None,
	Object_Static,
	Object_Character,
	Object_Moveable
};

enum class PlayerDir
{
	Front = 0,
	FrontRight = 45,
	Right = 90,
	BackRight = 135,
	Back = 180,
	BackLeft = 225,
	Left = 270,
	FrontLeft = 315,
	Max
};

enum class IOType
{
	Mesh,	
	Map,
	Max,
};

enum class MapObjType
{
	Transform,
	CounterTop,
	CounterTop_Corner,
	CounterTop_NoEdge,
	CounterTop_WiZard, //������ �������� ���� ������
	GasRange, //����������
	Bin, //��������
	Sink, //��ũ��
	Servicehatch, //�丮 ���� â��
	FoodBox, //���� ���� �ڽ�
	Npc,
	Collision_Wall,
};


enum class ToolInfo
{
	Dish, //����
	FireExtinguisher, //��ȭ��
	FryingPan, //��������
	Pot, //����
	CuttingBoard, //������ Į
};
