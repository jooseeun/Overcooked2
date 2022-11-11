#pragma once
#include "GamePlayObject.h"

// Ό³Έν :
class GameEngineFBXAnimationRenderer;
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
	std::shared_ptr<GameEngineFBXStaticRenderer> Van_;
};

