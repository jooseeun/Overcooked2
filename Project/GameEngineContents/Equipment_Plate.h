#pragma once
#include "GamePlayBowl.h"
// ���� :

class Equipment_Plate final : public GamePlayBowl
{
public:
	// constrcuter destructer
	Equipment_Plate();
	~Equipment_Plate();

	// delete Function
	Equipment_Plate(const Equipment_Plate& _Other) = delete;
	Equipment_Plate(Equipment_Plate&& _Other) noexcept = delete;
	Equipment_Plate& operator=(const Equipment_Plate& _Other) = delete;
	Equipment_Plate& operator=(Equipment_Plate&& _Other) noexcept = delete;

	//Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	//Input_InteractOption Input_Interact() override;
	Input_PickUpOption Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object) override;


	inline int GetPlateStack() const
	{
		return StackValue_;
	}

	inline void PlusPlateStack()
	{
		++StackValue_;
	}

	inline void MinusPlateStack()
	{
		--StackValue_;
	}


	inline bool IsDirty()
	{
		return Dirty;
	}

	void SetDirty();
	void SetClean();
protected:
	void Start() override;
private:
	bool Dirty;
	int StackValue_;
};

