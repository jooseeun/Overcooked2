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
	Object_CharacterColCheck,
	Object_CharacterCameraCheck,
	Object_Character_Interact,
	Object_Moveable,
	Object_StaticObject_1,

	Object_Sink,

	// Collision ���� �浹��
	Lift,
	Floor,// �ٴ� �ݸ���
	DeadZone,		// �÷��̾ ������ �״� �ݸ��� ex) ��, ���
	Map_Object,
	Map_Potal,
	Map_Cannon,
	Map_Button,
	Map_IcePlatform,

	MoveCar
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
enum class PlayerCurStateType // �÷��̾ ������������
{
	Idle,
	Sink,
	Cannon,
	HoldUp,
	HoldDown,
	Slice,
	FireOff,
	DishWash,
	Throw,
	Max
};

enum class PlayerHoldType // �տ��ִ°� ����Ÿ������
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
	Bowl,
	Steamer,
	Mixer,
	OvenPot,
	Max
};

enum class FoodType
{
	None,
	CucumberSushi,              // ���� + �� + ��
	FishSushi,                  // �� + �� + ȸ
	FishandCucumberSushi,       // ���� + �� + �� + ȸ
	FishSushimi,                // ȸ
	PrawnSushimi,               // ����
	PlainBurger,                // �� + ���
	CheeseBurger,               // �� + ��� + ġ��
	CheeseBurgerLettuceTomato,  // �� + ��� + ����� + �丶��
	PrawnDumpling,              // ���� + �а���
	SteamedFish,                // �����(��)
	MeatDumpling,               // ��� + �а���
	CarrotDumpling,             // ��� + �а���
	StrawberryPancake,			// �а��� + �ް� + ����
	BlueberryPancake,			// �а��� + �ް� + ��纣��
	ChrismasPuddingOrange		// �а��� + �ް� + �������� + ������
};

enum class IngredientType
{
	None = -1, //�ƹ��͵� �ƴ� ���� (+)
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
	Cucumber, //����
	Orange,
	DriedFruit,
	Strawberry,
	Blueberry

	//Cucumber, //����
};