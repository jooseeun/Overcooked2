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

	// Collision ���� �浹��
	Floor,			// �ٴ� �ݸ���
	Map_Object,

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
	None = 0,
	Plate, //����
	FireExtinguisher, //��ȭ��
	FryingPan, //��������
	Pot, //����
	CuttingBoard, //������ Į
	FoodBox, // ���Ļ���
	TrashCan, // ��������
	Bowl,	// �ͼ��� �ִ� ����
	Steamer, // ���
	Max
};


enum class FoodType
{
	Tomato,
	Onion,
	Potato,
	Dough, //���� ����
	Seaweed, //�̿�
	Mushroom,
	Meat,
	Lettuce, //�����
	Rice,
	Flour, //�а���
	Bread,
	Fish,
	Sausage,
	DumplingSkin, //������
	Egg,
	Chicken,
	Burrito, //�θ���
	Cheese,
	Carrot,
	Chocolate,
	Honey,
	PastaNoodles, //�Ľ�Ÿ ��
	Prawn,
	Cucumber //����
};