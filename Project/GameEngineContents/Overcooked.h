#pragma once
#include <GameEngineCore/GameEngineCore.h>

class Overcooked : public GameEngineCore
{
public:
	Overcooked();
	~Overcooked();

	Overcooked(const Overcooked& _Other) = delete;
	Overcooked(Overcooked&& _Other) noexcept = delete;
	Overcooked& operator=(const Overcooked& _Other) = delete;
	Overcooked& operator=(Overcooked&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LoadMaterial();
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void MeshLoad();
	void TextureLoad();
	void SoundLoad();
	void InputMake();

	void LoadStage(std::string_view _StageName);
	void LoadCommonResource();
};
