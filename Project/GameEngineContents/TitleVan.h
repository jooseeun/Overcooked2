#pragma once
#include "GamePlayObject.h"

class GameEngineFBXAnimationRenderer;
class VanSign : public GamePlayObject
{
public:
	// constrcuter destructer
	VanSign();
	~VanSign();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> SignRenderer_;
};

// Ό³Έν :
class TitleVan : public GamePlayObject
{
public:
	// constrcuter destructer
	TitleVan();
	~TitleVan();

	// delete Function
	TitleVan(const TitleVan& _Other) = delete;
	TitleVan(TitleVan&& _Other) noexcept = delete;
	TitleVan& operator=(const TitleVan& _Other) = delete;
	TitleVan& operator=(TitleVan&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<VanSign> Sign_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

	bool IsSignUp_;
};

