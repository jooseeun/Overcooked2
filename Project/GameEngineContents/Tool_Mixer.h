#pragma once
#include "GamePlayTool.h"
// Ό³Έν :
class Tool_Mixer final : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Mixer();
	~Tool_Mixer();

	// delete Function
	Tool_Mixer(const Tool_Mixer& _Other) = delete;
	Tool_Mixer(Tool_Mixer&& _Other) noexcept = delete;
	Tool_Mixer& operator=(const Tool_Mixer& _Other) = delete;
	Tool_Mixer& operator=(Tool_Mixer&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

