#include "PreCompile.h"
#include "GamePacket.h"
#include "GamePlayTool.h"

ObjectStartPacket::ObjectStartPacket()
	: ObjectToolData(ObjectToolType::None)
	, ExceptionData(ExceptionObject::None)
{
	SetPacketID(ContentsPacketType::ObjectStart);
}