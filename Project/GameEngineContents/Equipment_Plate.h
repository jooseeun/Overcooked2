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

	bool SetPlate(std::shared_ptr<Equipment_Plate> _Plate)
	{
		if (_Plate == nullptr)
		{
			return false;
		}
		else
		{
			if (Dirty_ != _Plate->Dirty_)
			{
				return false;
			}
			else
			{
				if (Pile_Plate_ != nullptr)
				{
					Pile_Plate_->SetPlate(_Plate);
			
				}
				else
				{
					Pile_Plate_ = _Plate;
					Pile_Plate_->SetParent(shared_from_this());
					Pile_Plate_->On();
					Pile_Plate_->GetTransform().SetLocalPosition({ 0, 25 , 0 });
				}
				return true;
			}
		}
		return false;
	}

	std::shared_ptr<Equipment_Plate> GetPlate()
	{
		if (Pile_Plate_ == nullptr)
		{
			return CastThis<Equipment_Plate>();
		}
		else
		{
			std::weak_ptr<Equipment_Plate> Plate = Pile_Plate_->GetPlate();
			if (Pile_Plate_ == Plate.lock())
			{
				Pile_Plate_ = nullptr;
			}
			return Plate.lock();
		}
	}

	void SetDirty();
	void SetClean();
protected:
	void Start() override;
private:
	bool Dirty_;
	bool Washing_;

	//HoldDownEnum HoldOn(std::shared_ptr<GamePlayStaticObject> _Object) override;
	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;


	std::shared_ptr<Equipment_Plate> Pile_Plate_;
};

