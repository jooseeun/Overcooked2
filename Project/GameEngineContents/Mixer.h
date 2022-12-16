#pragma once
#include "GamePlayTool.h"
#include "GamePlayStaticObject.h"

// 설명 :

enum class MixerType
{
	Mixer_Kevin,
	Mixer_Winter,
	Max,
};

// 설명 :
class Mixer : public GamePlayStaticObject
{
public:
	// constrcuter destructer
	Mixer();
	~Mixer();

	// delete Function
	Mixer(const Mixer& _Other) = delete;
	Mixer(Mixer&& _Other) noexcept = delete;
	Mixer& operator=(const Mixer& _Other) = delete;
	Mixer& operator=(Mixer&& _Other) noexcept = delete;

	inline void SetMixerType(MixerType _Type)
	{
		MyType_ = _Type;
	}

	inline MixerType GetMixerType()
	{
		return MyType_;
	}

	void SetMixerMesh(MixerType _Type);

	float4 GetToolPos() override
	{
		ToolPos_ = GetTransform().GetWorldPosition() + float4{ 0, 60.f };

		return ToolPos_;
	};

protected:
	void Start() override;

private:
	MixerType MyType_;

};

class Tool_Mixer final : public GamePlayTool
{
public:
	// constrcuter destructer
	Tool_Mixer();
	~Tool_Mixer();

	// delete Function
	Tool_Mixer(const Tool_Mixer& _Other) = delete;
	Tool_Mixer(Tool_Mixer&& _Other) noexcept = delete;
	Tool_Mixer& operator=(const Tool_Mixer& _Other) = delete;
	Tool_Mixer& operator=(Tool_Mixer&& _Other) noexcept = delete;

protected:
	void Start() override;



};

