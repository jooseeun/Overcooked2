#pragma once
#include "GamePlayStaticObject.h"
#include "GamePlayTool.h"

class Rail : public GamePlayStaticObject
{
public:
	Rail();
	~Rail();

	Rail(const Rail& _Other) = delete;
	Rail(Rail&& _Other) noexcept = delete;
	Rail& operator=(const Rail& _Other) = delete;
	Rail& operator=(Rail&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	RenderOption RenderOptionMyInst;

};


class Tool_Rail : public GamePlayTool
{

public:
	// constrcuter destructer
	Tool_Rail();
	~Tool_Rail();

	// delete Function
	Tool_Rail(const Tool_Rail& _Other) = delete;
	Tool_Rail(Tool_Rail&& _Other) noexcept = delete;
	Tool_Rail& operator=(const Tool_Rail& _Other) = delete;
	Tool_Rail& operator=(Tool_Rail&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::weak_ptr<GamePlayStaticObject> Front_StaticObject_;
	std::weak_ptr<GamePlayMoveable> After_Moveable_;
	std::weak_ptr<GamePlayMoveable> Before_Moveable_;
	float MoveTime_;
	bool FirstTimeCheck_;

	CollisionReturn GetFrontStaticObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	void SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child) override;
};

