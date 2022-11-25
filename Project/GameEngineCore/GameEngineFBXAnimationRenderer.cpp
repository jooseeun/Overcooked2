#include "PreCompile.h"
#include "GameEngineFBXAnimationRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXAnimationRenderer::GameEngineFBXAnimationRenderer()
	: Pause(false)
{

}

GameEngineFBXAnimationRenderer::~GameEngineFBXAnimationRenderer()
{
	Animations.clear();
}

void FBXRendererAnimation::Init(const std::string_view& _Name, int _Index)
{
	Aniamtion->AnimationMatrixLoad(Mesh, _Name, _Index);
	FBXAnimationData = Aniamtion->GetAnimationData(_Index);
	Start = 0;
	End = static_cast<unsigned int>(FBXAnimationData->TimeEndCount);
}

void FBXRendererAnimation::Update(float _DeltaTime)
{
	if (false == ParentRenderer->Pause)
	{
		Info.CurFrameTime += _DeltaTime;
		Info.PlayTime += _DeltaTime;

		while (Info.CurFrameTime >= Info.Inter)
		{
			Info.CurFrameTime -= Info.Inter;
			++Info.CurFrame;

			if (false == bOnceStart && Info.CurFrame == 0)
			{
				if (nullptr != StartEvent)
				{
					StartEvent(Info);
				}
				bOnceStart = true;
				bOnceEnd = false;
			}

			if (Info.CurFrame == (Info.Frames.size() - 1) && false == bOnceEnd)
			{
				if (nullptr != EndEvent)
				{
					EndEvent(Info);
				}
				bOnceEnd = true;
				bOnceStart = false;
				break;
			}

			if (nullptr != FrameEvent)
			{
				FrameEvent(Info);
			}

			if (nullptr != TimeEvent)
			{
				TimeEvent(Info, _DeltaTime);
			}

			if (Info.CurFrame >= Info.Frames.size() - 1)
			{
				if (true == Info.Loop)
				{
					Info.CurFrame = Start;
				}
				else
				{
					Info.CurFrame = static_cast<unsigned int>(Info.Frames.size()) - 1;
				}
			}
		}
	}

	unsigned int NextFrame = Info.CurFrame;

	++NextFrame;

	if (NextFrame >= End)
	{
		NextFrame = 0;
	}

	if (ParentRenderer->IsChangeTimer_ > 0.0f)
	{
		ParentRenderer->IsChangeTimer_ -= _DeltaTime;
	}

	float CurChangeTimer = 1 - ParentRenderer->IsChangeTimer_ * 5.0f;

	std::vector<std::vector<GameEngineRenderUnit>>& Units = ParentRenderer->GetAllRenderUnit();

	for (size_t UnitSetIndex = 0; UnitSetIndex < Units.size(); ++UnitSetIndex)
	{
		for (size_t RenderUnitIndex = 0; RenderUnitIndex < Units[UnitSetIndex].size(); ++RenderUnitIndex)
		{
			GameEngineRenderUnit& Render = Units[UnitSetIndex][RenderUnitIndex];

			std::map<size_t, std::vector<float4x4>>::iterator MatrixIter = ParentRenderer->AnimationBoneMatrixs.find(UnitSetIndex);

			if (MatrixIter == ParentRenderer->AnimationBoneMatrixs.end())
			{
				continue;
			}

			std::vector<float4x4>& AnimationBoneMatrix = MatrixIter->second;

			std::map<size_t, std::vector<AnimationBoneData>>::iterator AnimationDataIter = ParentRenderer->AnimationBoneDatas.find(UnitSetIndex);
			std::vector<AnimationBoneData>& AnimationBoneDatas = AnimationDataIter->second;

			size_t MeshIndex = MatrixIter->first;

			for (int i = 0; i < AnimationBoneMatrix.size(); i++)
			{
				Bone* BoneData = ParentRenderer->GetFBXMesh()->FindBone(MeshIndex, i);

				if (true == FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData.empty())
				{
					AnimationBoneMatrix[i] = float4x4::Affine(BoneData->BonePos.GlobalScale, BoneData->BonePos.GlobalRotation, BoneData->BonePos.GlobalTranslation);
					return;
				}

				FbxExBoneFrameData& CurData = FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData[Info.CurFrame];
				FbxExBoneFrameData& NextData = FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData[NextFrame];

				AnimationBoneDatas[i].Scale = float4::Lerp(CurData.S, NextData.S, Info.CurFrameTime);
				AnimationBoneDatas[i].RotQuaternion = float4::SLerpQuaternion(CurData.Q, NextData.Q, Info.CurFrameTime);
				AnimationBoneDatas[i].Pos = float4::Lerp(CurData.T, NextData.T, Info.CurFrameTime);

				// 애니메이션 블렌딩
				if (ParentRenderer->IsChangeTimer_ > 0.0f)
				{
					std::map<size_t, std::vector<AnimationBoneData>>::iterator BeforeAnimationDataIter = ParentRenderer->BeforeAnimationBoneDatas.find(UnitSetIndex);
					if (BeforeAnimationDataIter != ParentRenderer->BeforeAnimationBoneDatas.end())
					{
						std::vector<AnimationBoneData>& BeforeAnimationBoneData = BeforeAnimationDataIter->second;

						AnimationBoneDatas[i].Scale = float4::LerpLimit(BeforeAnimationBoneData[i].Scale, AnimationBoneDatas[i].Scale, CurChangeTimer);
						AnimationBoneDatas[i].RotQuaternion = float4::SLerpQuaternion(BeforeAnimationBoneData[i].RotQuaternion, AnimationBoneDatas[i].RotQuaternion, CurChangeTimer);
						AnimationBoneDatas[i].Pos = float4::LerpLimit(BeforeAnimationBoneData[i].Pos, AnimationBoneDatas[i].Pos, CurChangeTimer);
					}
				}

				float4x4 Mat = float4x4::Affine(AnimationBoneDatas[i].Scale, AnimationBoneDatas[i].RotQuaternion, AnimationBoneDatas[i].Pos);
				AnimationBoneMatrix[i] = BoneData->BonePos.Offset * Mat;
			}
		}
	}
}

void FBXRendererAnimation::Reset()
{
	Info.CurFrameTime = 0.0f;
	Info.CurFrame = 0;
	Info.PlayTime = 0.0f;
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name)
{
	SetFBXMesh(_Name, "TextureAnimation");
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name, const std::string& _Material)
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_Material);

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

GameEngineRenderUnit* GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex /*= 0*/)
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return nullptr;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return nullptr;
	}

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return nullptr;
	}

	if (AnimationBoneMatrixs.end() == AnimationBoneMatrixs.find(_MeshIndex))
	{
		size_t BoneCount = FindFBXMesh->GetBoneCount(_MeshIndex);
		AnimationBoneMatrixs.insert(std::make_pair(_MeshIndex, std::vector<float4x4>()));
		AnimationBoneMatrixs[_MeshIndex].resize(BoneCount);

		AnimationBoneDatas.insert(std::make_pair(_MeshIndex, std::vector<AnimationBoneData>()));
		AnimationBoneDatas[_MeshIndex].resize(BoneCount);
	}

	FindFBXMesh->GetMeshInfosCount();

	// 텍스처 세팅은 부모님이 맡아서 처리해주고
	GameEngineRenderUnit* Unit = GameEngineFBXRenderer::SetFBXMesh(_Name, _Material, _MeshIndex, _SubSetIndex);

	if (nullptr == Unit)
	{
		MsgBoxAssert("FBX애니메이션 랜더유니트를 만들어내지 못했습니다.");
		return nullptr;
	}

	// 이때 스트럭처드 버퍼를 세팅할거냐.
	if (Unit->ShaderResources.IsStructuredBuffer("ArrAniMationMatrix"))
	{
		GameEngineStructuredBufferSetter* AnimationBuffer = Unit->ShaderResources.GetStructuredBuffer("ArrAniMationMatrix");
		AnimationBuffer->Res = GetFBXMesh()->GetAnimationStructuredBuffer(_MeshIndex);
		if (nullptr == AnimationBuffer->Res)
		{
			MsgBoxAssert("애니메이션용 스트럭처드 버퍼가 존재하지 않습니다.");
			return Unit;
		}

		if (0 == AnimationBoneMatrixs[_MeshIndex].size())
		{
			return Unit;
		}

		AnimationBuffer->SetData = &AnimationBoneMatrixs[_MeshIndex][0];
		AnimationBuffer->Size = sizeof(float4x4);
		AnimationBuffer->Count = AnimationBoneMatrixs[_MeshIndex].size();
		AnimationBuffer->Bind();
	}

	return Unit;
}

void GameEngineFBXAnimationRenderer::PauseSwtich()
{
	Pause = !Pause;
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(const std::string& _AnimationName, const GameEngineRenderingEvent& _Desc, int _Index)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	// 본을 가진 fbx가 세팅되어 있는지 검사한다.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다.");
		return;
	}

	// 여기있는 함수를 외부에서 호출하면 됩니다.

	if (Animations.end() != Animations.find(UpperName))
	{
		MsgBoxAssertString("이미 존재하는 이름의 애니메이션입니다." + UpperName);
		return;
	}

	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Find(_Desc.ResourcesName);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation이 존재하지 않습니다. " + _Desc.ResourcesName);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();
	FbxExAniData* AnimData = Animation->GetAnimationData(_Index);

	NewAnimation->Info = _Desc;
	NewAnimation->Info.Init(AnimData->TimeStartCount, AnimData->TimeEndCount);
	NewAnimation->Info.Renderer = this;
	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Aniamtion = Animation;
	NewAnimation->ParentRenderer = this;
	NewAnimation->Reset();

	NewAnimation->Init(_AnimationName, _Index);

	RenderOptionInst.IsAnimation = 1;

	Animations.insert(std::make_pair(UpperName, NewAnimation));

	Animation;
}

void GameEngineFBXAnimationRenderer::ChangeAnimation(const std::string& _AnimationName, bool _IsBlending)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<FBXRendererAnimation>>::iterator FindIter = Animations.find(UpperName);

	if (Animations.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
		return;
	}

	if (true == _IsBlending)
	{
		IsChangeTimer_ = 0.2f;
		BeforeAnimationBoneDatas = AnimationBoneDatas;
	}

	CurAnimation = FindIter->second;
}


void GameEngineFBXAnimationRenderer::ChangeAnimationFrame(size_t _StartIndex)
{
	size_t ChangeFrame = _StartIndex;
	size_t MaxSize = GetAnimationFrameCount();
	if (MaxSize <= _StartIndex)
	{
		ChangeFrame = MaxSize;
	}

	CurAnimation->GetRendereringEvent().CurFrame = ChangeFrame;
}


void GameEngineFBXAnimationRenderer::Update(float _DeltaTime)
{
	if (nullptr == CurAnimation)
	{
		return;
	}

	CurAnimation->Update(_DeltaTime);
}