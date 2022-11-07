#pragma once
#include "GamePlayTool.h"
// Ό³Έν :
class Tool_Cooker : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Cooker();
	~Tool_Cooker();

	// delete Function
	Tool_Cooker(const Tool_Cooker& _Other) = delete;
	Tool_Cooker(Tool_Cooker&& _Other) noexcept = delete;
	Tool_Cooker& operator=(const Tool_Cooker& _Other) = delete;
	Tool_Cooker& operator=(Tool_Cooker&& _Other) noexcept = delete;

	Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;

protected:
	void Start() override;
private:

};

