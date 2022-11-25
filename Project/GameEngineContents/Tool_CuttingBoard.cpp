#include "PreCompile.h"
#include "Tool_CuttingBoard.h"

Tool_CuttingBoard::Tool_CuttingBoard()
{
}

Tool_CuttingBoard::~Tool_CuttingBoard()
{
}

void Tool_CuttingBoard::Start()
{
	GetFBXMesh()->SetFBXMesh("CuttingBoard.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}
