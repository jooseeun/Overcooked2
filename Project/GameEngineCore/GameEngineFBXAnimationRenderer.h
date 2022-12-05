#pragma once
#include "GameEngineFBXRenderer.h"
#include "GameEngineFBXAnimation.h"
#include "GameEngineRenderingEvent.h"
#include <map>

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameEngineFBXAnimationRenderer;
class FBXRendererAnimation : public std::enable_shared_from_this<FBXRendererAnimation>
{
public:
	GameEngineFBXAnimationRenderer* ParentRenderer;
	// SetFBX 본을 가지고 있는 매쉬
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// 애니메이션을 가지고 있는 FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	FbxExAniData* FBXAnimationData;

	UINT Start;
	UINT End;

	GameEngineRenderingEvent Info;

	bool bOnceStart;
	bool bOnceEnd;
	std::function<void(const GameEngineRenderingEvent&)> FrameEvent;
	std::function<void(const GameEngineRenderingEvent&)> EndEvent;
	std::function<void(const GameEngineRenderingEvent&)> StartEvent;
	std::function<void(const GameEngineRenderingEvent&, float)> TimeEvent;

	void PauseSwtich();
	void Init(const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);

	GameEngineRenderingEvent& GetRendereringEvent()
	{
		return Info;
	}

public:
	FBXRendererAnimation() 
		: Start(0)
		, End(0)
		, bOnceStart(false)
		, bOnceEnd(false)
	{
	}

	~FBXRendererAnimation()
	{
	}
};

struct AnimationBoneData
{
public:
	int Index = -1;
	float4 Scale;
	float4 RotQuaternion;
	float4 Pos;
	float4 RotEuler;
};

// 설명 :
class GameEngineFBXAnimationRenderer : public GameEngineFBXRenderer
{
	friend FBXRendererAnimation;

public:
	// constrcuter destructer
	GameEngineFBXAnimationRenderer();
	~GameEngineFBXAnimationRenderer();

	// delete Function
	GameEngineFBXAnimationRenderer(const GameEngineFBXAnimationRenderer& _Other) = delete;
	GameEngineFBXAnimationRenderer(GameEngineFBXAnimationRenderer&& _Other) noexcept = delete;
	GameEngineFBXAnimationRenderer& operator=(const GameEngineFBXAnimationRenderer& _Other) = delete;
	GameEngineFBXAnimationRenderer& operator=(GameEngineFBXAnimationRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _Name) override;
	void SetFBXMesh(const std::string& _Name, const std::string& _Material) override;
	GameEngineRenderUnit* SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex = 0) override;

	void CreateFBXAnimation(const std::string& _AnimationName, const GameEngineRenderingEvent& _Desc, int _Index = 0);
	void ChangeAnimation(const std::string& _AnimationName, bool _IsBlending = false);
	void ChangeAnimationFrame(size_t _StartIndex);

	void Update(float _DeltaTime) override;
	void PauseSwtich();

	void AnimationBindStart(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->StartEvent = _Function;
	}

	void AnimationBindEnd(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->EndEvent = _Function;
	}

	void AnimationBindFrame(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->FrameEvent = _Function;
	}

	void AnimationBindTime(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&, float)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->TimeEvent = _Function;
	}

	size_t GetAnimationFrameCount()
	{
		if (CurAnimation == nullptr)
		{
			MsgBoxAssert("애니메이션을 세팅하지 않았습니다.");
		}
		return CurAnimation->GetRendereringEvent().Frames.size() - 1;
	}

	inline std::shared_ptr<FBXRendererAnimation> GetCurAnim()
	{
		return CurAnimation;
	}

protected:

private:
	bool Pause;
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>> Animations;
	std::shared_ptr<FBXRendererAnimation> CurAnimation;

	std::map<size_t, std::vector<float4x4>> AnimationBoneMatrixs;
	std::map<size_t, std::vector<AnimationBoneData>> AnimationBoneDatas;

	float IsChangeTimer_;
	std::map<size_t, std::vector<AnimationBoneData>> BeforeAnimationBoneDatas;

};

