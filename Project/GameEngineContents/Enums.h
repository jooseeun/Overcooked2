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
	Max
};

//enum class UnsortMapObjType
//{
//	StaticNoCollision,		// �ִϸ��̼� X, �ݸ��� X		ex) Grass, Bamboo
//	//Static,					// �ִϸ��̼� X				ex) TrafficLight 
//	AnimationNoCollision,	// �ִϸ��̼� O, �ݸ��� x		ex) Candle, Pigeon_Idle, Pigeon_Move
//	Animation,				// �ִϸ��̼� O				ex) Kevin
//
//	Npc,					// �ִϸ��̼� O, �ݸ��� O
//	Car,					// �ִϸ��̼� X
//	TrafficLight,			// �ִϸ��̼� X, �ݸ��� O
//
//	Max,
//};