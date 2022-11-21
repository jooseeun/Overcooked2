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
enum class PlayerHoldType
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
	FoodBox, // 음식상자
	TrashCan, // 쓰레기통
	Max
};

//enum class UnsortMapObjType
//{
//	StaticNoCollision,		// 애니메이션 X, 콜리전 X		ex) Grass, Bamboo
//	//Static,					// 애니메이션 X				ex) TrafficLight 
//	AnimationNoCollision,	// 애니메이션 O, 콜리전 x		ex) Candle, Pigeon_Idle, Pigeon_Move
//	Animation,				// 애니메이션 O				ex) Kevin
//
//	Npc,					// 애니메이션 O, 콜리전 O
//	Car,					// 애니메이션 X
//	TrafficLight,			// 애니메이션 X, 콜리전 O
//
//	Max,
//};