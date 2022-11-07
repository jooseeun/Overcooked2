#pragma once
#include "GamePlayTool.h"

// Ό³Έν :
class Tool_Sink : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Sink();
	~Tool_Sink();

	// delete Function
	Tool_Sink(const Tool_Sink& _Other) = delete;
	Tool_Sink(Tool_Sink&& _Other) noexcept = delete;
	Tool_Sink& operator=(const Tool_Sink& _Other) = delete;
	Tool_Sink& operator=(Tool_Sink&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

