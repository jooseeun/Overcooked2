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
	CounterTop_WiZard, //마법사 스테이지 전용 조리대
	GasRange, //가스레인지
	Bin, //쓰레기통
	Sink, //싱크대
	Servicehatch, //요리 내는 창구
	FoodBox, //음식 스폰 박스
	Npc,
	Collision_Wall,
};


enum class ToolInfo
{
	Dish, //접시
	FireExtinguisher, //소화기
	FryingPan, //프라이팬
	Pot, //냄비
	CuttingBoard, //도마랑 칼
};
