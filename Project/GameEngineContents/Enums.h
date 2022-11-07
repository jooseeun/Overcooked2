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
	Floor,			// 바닥 콜리전

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
	Dish, //접시
	FireExtinguisher, //소화기
	FryingPan, //프라이팬
	Pot, //냄비
	CuttingBoard, //도마랑 칼
};

