#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FadeFont : public GameEngineActor
{
public:
	FadeFont();
	~FadeFont();

	FadeFont(const FadeFont& _Other) = delete;
	FadeFont(const FadeFont&& _Other) noexcept = delete;
	FadeFont& operator=(const FadeFont& _Ohter) = delete;
	FadeFont& operator=(const FadeFont&& _Other) noexcept = delete;

	inline void Init(std::string_view _Str, const float4& _Color, float _Size)
	{
		Str_ = _Str.data();
		Color_ = _Color;
		Size_ = _Size;
	}

	void Debug()
	{
		IsDebug_ = true;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:
	std::string Str_ = "";
	float4 Color_ = { 1.f,1.f,1.f,1.f };
	std::weak_ptr<GameEngineFontRenderer> FontRenderer_;
	float Size_ = 30.f;

	bool GoingToDead_ = false;
	bool IsDebug_ = false;
};
