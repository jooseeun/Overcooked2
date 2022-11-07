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
	UnsortMap,
	SortMap,
	Max,
};

enum class MapObjType
{
	Origin,
	CounterTop,
	CounterTop_Corner,
	CounterTop_NoEdge,
	CounterTop_WiZard,  //마법사 스테이지 전용 조리대
	GasRange,			//가스레인지
	TrashCan,			//쓰레기통
	Sink,				//싱크대
	Servicehatch,		//요리 내는 창구
	FoodBox,			//음식 스폰 박스
	Npc_Static,			// 움직이지 않는 NPC
	Npc_Move,			// 1-2 레벨 내 움직이는 NPC
	Car_Static,			// 움직이지 않는 자동차
	Car_Move,			// 1-2 레벨 내 움직이는 자동차
	Grass,
	Pigeon, 
	TrafficLight,
	Candle_Move,		// 1-4 레벨 내 움직이는 초
	Collision,			// 벽, 바닥용 콜리전
};


enum class ToolInfo
{
	Dish, //접시
	FireExtinguisher, //소화기
	FryingPan, //프라이팬
	Pot, //냄비
	CuttingBoard, //도마랑 칼
};
