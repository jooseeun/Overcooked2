#pragma once
#include "GamePlayObject.h"

class Equipment_Plate : public GamePlayObject
{
	friend class Tool_Sink;
public:
	// constrcuter destructer
	Equipment_Plate();
	~Equipment_Plate();

	// delete Function
	Equipment_Plate(const Equipment_Plate& _Other) = delete;
	Equipment_Plate(Equipment_Plate&& _Other) noexcept = delete;
	Equipment_Plate& operator=(const Equipment_Plate& _Other) = delete;
	Equipment_Plate& operator=(Equipment_Plate&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

