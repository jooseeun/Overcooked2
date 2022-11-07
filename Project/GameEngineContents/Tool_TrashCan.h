#pragma once

// Ό³Έν :
class Tool_TrashCan
{
public:
	// constrcuter destructer
	Tool_TrashCan();
	~Tool_TrashCan();

	// delete Function
	Tool_TrashCan(const Tool_TrashCan& _Other) = delete;
	Tool_TrashCan(Tool_TrashCan&& _Other) noexcept = delete;
	Tool_TrashCan& operator=(const Tool_TrashCan& _Other) = delete;
	Tool_TrashCan& operator=(Tool_TrashCan&& _Other) noexcept = delete;

protected:

private:

};

