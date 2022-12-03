#pragma once
#include "GamePlayBowl.h"
// Ό³Έν :

class Equipment_Plate final : public GamePlayBowl
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

	//Input_PickUpOption CheckMoveable(GamePlayMoveable* _Object) override;
	//Input_InteractOption Input_Interact() override;

	inline bool IsDirty()
	{
		return Dirty_;
	}

	inline void SetWashing()
	{
		Washing_ = true;
	}

	void SetDirty();
	void SetClean();
protected:
	void Start() override;
private:
	bool Dirty_;
	bool Washing_;

	HoldDownEnum HoldOn(std::shared_ptr<Player> _Player) override;
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable> _Moveable) override;
	//HoldDownEnum HoldOn(std::shared_ptr<GamePlayStaticObject> _Object) override;

	std::shared_ptr<Equipment_Plate> Pile_Plate_;
};

