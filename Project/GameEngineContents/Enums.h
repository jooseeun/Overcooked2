#pragma once

enum class CollisionOrder
{
	Default,
	Mouse,
	Max,



	// Object
	Object_None,
	Object_StaticObject,
	Object_Character,
	Object_Character_Interact,
	Object_Moveable,
	//
	Floor,			// �ٴ� �ݸ���

};

enum class PlayerDir
{
	Front,
	FrontRight,
	Right,
	BackRight,
	Back,
	BackLeft,
	Left,
	FrontLeft,
	Max
};
enum class PlayerHoldType
	//��Ʈ�� Ű�� �������� � ��ȣ�ۿ��� ���� ���Ϸ��� ���� enum
{
	CanThrow, // ������ �ִ°�
	NotThrow, // �������� ����
	FireExtinguisher, // ��ȭ��
	Max // �տ� �ƹ��͵� ������
};
enum class ToolInfo
{
	Dish, //����
	FireExtinguisher, //��ȭ��
	FryingPan, //��������
	Pot, //����
	CuttingBoard, //������ Į
};

