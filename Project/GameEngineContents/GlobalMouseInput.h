#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MouseInputWindow;
class GlobalMouseInput : public GameEngineActor
{
public:
	// constrcuter destructer
	GlobalMouseInput();
	~GlobalMouseInput();

	// delete Function
	GlobalMouseInput(const GlobalMouseInput& _Other) = delete;
	GlobalMouseInput(GlobalMouseInput&& _Other) noexcept = delete;
	GlobalMouseInput& operator=(const GlobalMouseInput& _Other) = delete;
	GlobalMouseInput& operator=(GlobalMouseInput&& _Other) noexcept = delete;

	inline GameEngineTransform* GetNearTransform()
	{
		return NearTransform_;
	}

	inline void SetIsUI(bool _Value)
	{
		IsUI_ = _Value;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void TransformUpdate(float _Delta);
	void ClickUpdate(float _Delta);
	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	std::shared_ptr<MouseInputWindow> MouseWindow_;
	GameEngineCollision* Collision_;
	GameEngineCollision* StartCollision_;
	GameEngineCollision* GoalCollision_;
	GameEngineTransform* NearTransform_;
	bool IsUI_;

};

