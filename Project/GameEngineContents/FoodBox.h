#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayFood.h"

enum class FoodType
{
	Tomato,
	Onion,
	Potato,
	Dough, //���� ����
	Seaweed, //�̿�
	Mushroom,
	Meat, 
	Lettuce, //�����
	Rice,
	Flour, //�а���
	Bread,
	Fish,
	Sausage,
	DumplingSkin, //������
	Egg,
	Chicken,
	Burrito, //�θ���
	Cheese,
	Carrot,
	Chocolate,
	Honey,
	PastaNoodles, //�Ľ�Ÿ ��
	Shrimp,
	Cucumber //����
};

//���� ���� �ڽ�
class FoodBox : public GamePlayStaticObject
{
public:
	FoodBox();
	~FoodBox();

	FoodBox(const FoodBox& _Other) = delete;
	FoodBox(FoodBox&& _Other) noexcept = delete;
	FoodBox& operator=(const FoodBox& _Other) = delete;
	FoodBox& operator=(FoodBox&& _Other) noexcept = delete;

	inline void SwitchIsInteraction()
	{
		IsInteraction_ = !IsInteraction_;
	}
	void SetFoodType(FoodType _Type);

	FoodType GetFoodType()
	{
		return Type_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	ObjectFoodClass Enum_Ingredients_;

	std::shared_ptr<GameEngineTextureRenderer> Renderer_;

	bool IsInteraction_;
	bool IsOpen_;
	float Angle_;

	std::shared_ptr<GameEngineActor> Lid_;
	
	FoodType Type_;
};

