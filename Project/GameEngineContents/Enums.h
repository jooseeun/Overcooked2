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
	Floor,			// ¹Ù´Ú ÄÝ¸®Àü

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

enum class ToolInfo
{
	Dish, //Á¢½Ã
	FireExtinguisher, //¼ÒÈ­±â
	FryingPan, //ÇÁ¶óÀÌÆÒ
	Pot, //³¿ºñ
	CuttingBoard, //µµ¸¶¶û Ä®
};
