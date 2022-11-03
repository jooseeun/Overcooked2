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
	Tile,
	//Tile1-2,
	//Tile1-3,
	Max,
};

enum class MapObjType
{
	Table,
	Max,
};