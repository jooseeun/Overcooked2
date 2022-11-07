#include "PreCompile.h"
#include "GameEngineFBXAnimationRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"

GameEngineFBXAnimationRenderer::GameEngineFBXAnimationRenderer()
{

}

GameEngineFBXAnimationRenderer::~GameEngineFBXAnimationRenderer()
{
	Animations.clear();
}


void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name, std::string _Material)
{
	GameEngineMaterial* Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_Name, _Material);
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex /*= 0*/)
{
	GameEngineMaterial* Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_Name, _Material, _MeshIndex, _SubSetIndex);
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBX, int _Index)
{
	// 본을 가진 fbx가 세팅되어 있는지 검사한다.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다.");
		return;
	}

	// 여기있는 함수를 외부에서 호출하면 됩니다.

	if (Animations.end() != Animations.find(_AnimationName))
	{
		MsgBoxAssertString("이미 존재하는 이름의 애니메이션입니다." + _AnimationName);
		return;
	}

	GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Find(_AnimationFBX);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation이 존재하지 않습니다. " + _AnimationFBX);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();

	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Aniamtion = Animation;
	NewAnimation->ParentRenderer = this;

	NewAnimation->Init(_Index);
	RenderOptionInst.IsAnimation = 1;

	Animations.insert(std::make_pair(_AnimationName, NewAnimation));
	Animation;
}

void GameEngineFBXAnimationRenderer::ChangeAnimation(const std::string& _AnimationName)
{
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>>::iterator FindIter = Animations.find(_AnimationName);

	if (Animations.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
		return;
	}

	CurAnimation = FindIter->second;
}

void FBXRendererAnimation::Init(int _Index)
{
	Aniamtion->AnimationMatrixLoad(Mesh, _Index);
	FBXAnimationData = Aniamtion->GetAnimationData(_Index);
	Start = 0;
	End = FBXAnimationData->TimeEndCount;
	FrameTime = 0.02f;
}

void FBXRendererAnimation::Reset()
{
}

void FBXRendererAnimation::Update()
{
	Start = 0;
}
