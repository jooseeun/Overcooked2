#pragma once

enum class CollisionOrder
{
	Default,
	Mouse,
	Max,
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
	Table,
	Test2,
	Test3,
	Max,
};


enum class ToolInfo
{
	Dish, //Á¢½Ã
	FireExtinguisher, //¼ÒÈ­±â
	FryingPan, //ÇÁ¶óÀÌÆÒ
	Pot, //³¿ºñ
	CuttingBoard, //µµ¸¶¶û Ä®
};
