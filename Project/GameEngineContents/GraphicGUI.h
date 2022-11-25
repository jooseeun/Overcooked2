#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class GraphicGUI : public GameEngineGUI
{
public:
	// constrcuter destructer
	GraphicGUI();
	~GraphicGUI();

	// delete Function
	GraphicGUI(const GraphicGUI& _Other) = delete;
	GraphicGUI(GraphicGUI&& _Other) noexcept = delete;
	GraphicGUI& operator=(const GraphicGUI& _Other) = delete;
	GraphicGUI& operator=(GraphicGUI&& _Other) noexcept = delete;

protected:

private:

};

