#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestPortal : public GameEngineActor
{
public:
	// constrcuter destructer
	TestPortal();
	~TestPortal();

	// delete Function
	TestPortal(const TestPortal& _Other) = delete;
	TestPortal(TestPortal&& _Other) noexcept = delete;
	TestPortal& operator=(const TestPortal& _Other) = delete;
	TestPortal& operator=(TestPortal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Test_;

};

