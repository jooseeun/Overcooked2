#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>

class FbxExBoneFrameData
{
public:
	float4 S; // 크기
	float4 Q; // 자전
	float4 T; // 이동
	double Time;
	float4x4 FrameMat;

	fbxsdk::FbxAMatrix GlobalAnimation;
	fbxsdk::FbxAMatrix LocalAnimation;

	FbxExBoneFrameData() 
	{
	}

	void Write(GameEngineFile* _File) const
	{
		_File->Write(S);
		_File->Write(Q);
		_File->Write(T);
		_File->Write(Time);
		_File->Write(FrameMat);
		_File->Write(&GlobalAnimation, sizeof(fbxsdk::FbxAMatrix));
		_File->Write(&LocalAnimation, sizeof(fbxsdk::FbxAMatrix));
	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(S);
		_File->Read(Q);
		_File->Read(T);
		_File->Read(Time);
		_File->Read(FrameMat);
		_File->Read(&GlobalAnimation, sizeof(fbxsdk::FbxAMatrix), sizeof(fbxsdk::FbxAMatrix));
		_File->Read(&LocalAnimation, sizeof(fbxsdk::FbxAMatrix), sizeof(fbxsdk::FbxAMatrix));
	}
};

class FbxExBoneFrame
{
public:
	int BoneIndex;
	int BoneParentIndex;

	std::vector<FbxExBoneFrameData> BoneMatData;

	FbxExBoneFrame() 
	{
	}

	void Write(GameEngineFile* _File) const
	{
		_File->Write(BoneIndex);
		_File->Write(BoneParentIndex);
		_File->Write(BoneMatData);
	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(BoneIndex);
		_File->Read(BoneParentIndex);
		_File->Read(BoneMatData);
	}
};

class FbxExAniData
{
public:
	std::string				AniName;
	fbxsdk::FbxTime			StartTime; // 설정된 애니메이션 시간
	fbxsdk::FbxTime			EndTime; // 
	fbxsdk::FbxLongLong		TimeStartCount; 
	fbxsdk::FbxLongLong		TimeEndCount;
	fbxsdk::FbxLongLong		FrameCount;
	fbxsdk::FbxTime::EMode	TimeMode;
	__int64					FbxModeCount;
	double					FbxModeRate;

	std::map<size_t, std::vector<FbxExBoneFrame>> AniFrameData;

	void Write(GameEngineFile* _File) const
	{
		_File->Write(AniName);
		_File->Write(&StartTime, sizeof(fbxsdk::FbxTime));
		_File->Write(&EndTime, sizeof(fbxsdk::FbxTime));
		_File->Write(&TimeStartCount, sizeof(fbxsdk::FbxLongLong));
		_File->Write(&TimeEndCount, sizeof(fbxsdk::FbxLongLong));
		_File->Write(&FrameCount, sizeof(fbxsdk::FbxLongLong));
		_File->Write(&TimeMode, sizeof(fbxsdk::FbxTime::EMode));
		_File->Write(&FbxModeCount, sizeof(__int64));
		_File->Write(&FbxModeRate, sizeof(double));
		_File->Write(AniFrameData);
	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(AniName);
		_File->Read(&StartTime, sizeof(fbxsdk::FbxTime), sizeof(fbxsdk::FbxTime));
		_File->Read(&EndTime, sizeof(fbxsdk::FbxTime), sizeof(fbxsdk::FbxTime));
		_File->Read(&TimeStartCount, sizeof(fbxsdk::FbxLongLong), sizeof(fbxsdk::FbxLongLong));
		_File->Read(&TimeEndCount, sizeof(fbxsdk::FbxLongLong), sizeof(fbxsdk::FbxLongLong));
		_File->Read(&FrameCount, sizeof(fbxsdk::FbxLongLong), sizeof(fbxsdk::FbxLongLong));
		_File->Read(&TimeMode, sizeof(fbxsdk::FbxTime::EMode), sizeof(fbxsdk::FbxTime::EMode));
		_File->Read(&FbxModeCount, sizeof(__int64), sizeof(__int64));
		_File->Read(&FbxModeRate, sizeof(double), sizeof(double));
		_File->Read(AniFrameData);
	}


public:
	float FrameTime(int _Frame)
	{
		fbxsdk::FbxTime tTime = {};
		tTime.SetFrame(_Frame, TimeMode);

		return (float)tTime.GetSecondDouble();
	}

public:
	__int64 FrameModeRateInt()
	{
		return static_cast<__int64>(fbxsdk::FbxGetFrameRate(TimeMode));
	}
	double FrameModeRateDouble()
	{
		return fbxsdk::FbxGetFrameRate(TimeMode);
	}

	float FrameModeRateFloat()
	{
		return static_cast<float>(fbxsdk::FbxGetFrameRate(TimeMode));
	}


public:
	FbxExAniData() : AniName(""), StartTime(0), EndTime(0), TimeStartCount(0), TimeEndCount(0), FrameCount(0), FbxModeCount(0), FbxModeRate(0.0), TimeMode()
	{}
	~FbxExAniData() {}
};


// 설명 :
class GameEngineFBXMesh;
class GameEngineFBXAnimationRenderer;
class GameEngineFBXAnimation : public GameEngineFBX, public GameEngineRes<GameEngineFBXAnimation>
{
public:
	// constrcuter destructer
	GameEngineFBXAnimation();
	~GameEngineFBXAnimation();

	// delete Function
	GameEngineFBXAnimation(const GameEngineFBXAnimation& _Other) = delete;
	GameEngineFBXAnimation(GameEngineFBXAnimation&& _Other) noexcept = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation& _Other) = delete;
	GameEngineFBXAnimation& operator=(GameEngineFBXAnimation&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFBXAnimation> Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static std::shared_ptr<GameEngineFBXAnimation> Load(const std::string& _Path, const std::string& _Name);


	void AnimationMatrixLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimationRenderer> _Renderer, int _AnimationIndex);

	FbxExAniData* GetAnimationData(int _Index)
	{
		if (AnimationDatas.size() <= _Index)
		{
			MsgBoxAssert("애니메이션 데이터 범위를 넘어섰습니다");
		}

		return &AnimationDatas[_Index];
	}

protected:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	void ProcessAnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* pNode, int _index);
	bool AnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* _Node, int AnimationIndex);
	void ProcessAnimationCheckState(std::shared_ptr <GameEngineFBXMesh> _Fbx, int userAniDataIndex);
	fbxsdk::FbxAMatrix GetGeometryTransformation(fbxsdk::FbxNode* pNode);

	std::vector<FbxExAniData> AnimationDatas;

private:
	bool CheckAnimation();

};

