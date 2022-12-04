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
	Object_Character_Interact,
	Object_Moveable,

	// Collision 물리 충돌용
	Floor,			// 바닥 콜리전
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
enum class PlayerCurStateType // 플레이어가 무슨상태인지
{
	Idle,
	HoldUp,
	HoldDown,
	Slice,
	FireOff,
	DishWash,
	Throw,
	Max
};

enum class PlayerHoldType // 손에있는게 무슨타입인지
	//컨트롤 키를 눌렀을때 어떤 상호작용을 할지 정하려고 만든 enum
{
	CanThrow, // 던질수 있는것
	NotThrow, // 못던지는 도구
	FireExtinguisher, // 소화기
	Max // 손에 아무것도 없을때
};

enum class ToolInfo
{
	None = 0,
	Plate, //접시
	FireExtinguisher, //소화기
	FryingPan, //프라이팬
	Pot, //냄비
	CuttingBoard, //도마랑 칼
	Bowl,
	Steamer,
	Mixer,
	Max
};

enum class FoodType
{
	None,
	CucumberSushi,
	FishSushi,
	FishandCucumberSushi,
	FishSushimi,
	PrawnSushimi,
	PlainBurger,
	CheeseBurger,
	CheeseBurgerLettuceTomato,
	PrawnDumpling,
	SteamedFish,
	MeatDumpling,
	CarrotDumpling
};

enum class IngredientType
{
	None = -1, //아무것도 아닌 상태 (+)
	Tomato,
	Onion,
	Potato,
	Dough, //피자 반죽
	Seaweed, //미역
	Mushroom,
	Meat,
	Lettuce, //양상추
	Rice,
	Flour, //밀가루
	Bread,
	Fish,
	Sausage,
	DumplingSkin, //만두피
	Egg,
	Chicken,
	Burrito, //부리또
	Cheese,
	Carrot,
	Chocolate,
	Honey,
	PastaNoodles, //파스타 면
	Prawn,
	Cucumber, //오이
	Orange,
	Nuts,
	Strawberry,

	Cucumber, //오이
};