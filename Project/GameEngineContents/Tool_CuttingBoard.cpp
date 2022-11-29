#include "PreCompile.h"
#include "Tool_CuttingBoard.h"
#include "GamePlayMoveable.h"
#include "GamePlayFood.h"

Tool_CuttingBoard::Tool_CuttingBoard()
{
}

Tool_CuttingBoard::~Tool_CuttingBoard()
{
}

void Tool_CuttingBoard::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	GamePlayTool::SetToolInfoType(ToolInfo::CuttingBoard);
	GamePlayTool::SetObjectToolType(ObjectToolType::CuttingBoard);

	GetFBXMesh()->SetFBXMesh("CuttingBoard.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

UsingDownEnum Tool_CuttingBoard::UsingDown(std::shared_ptr<Player> _Player)
{
	return UsingDownEnum::Nothing;
}

bool Tool_CuttingBoard::CanHoldThis(std::shared_ptr<GamePlayMoveable> _Moveable)
{
	return true;
}