#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>

class FbxExBoneFrameData : public GameEngineSerializObject
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

	void Write(GameEngineFile& _File) override
	{
		_File.Write(S);
		_File.Write(Q);
		_File.Write(T);
		_File.Write(Time);
		_File.Write(FrameMat);
		_File.Write(GlobalAnimation);
		_File.Write(LocalAnimation);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(S);
		_File.Read(Q);
		_File.Read(T);
		_File.Read(Time);
		_File.Read(FrameMat);
		_File.Read(GlobalAnimation);
		_File.Read(LocalAnimation);
	}
};

class FbxExBoneFrame : public GameEngineSerializObject
{
public:
	int BoneIndex;
	int BoneParentIndex;

	std::vector<FbxExBoneFrameData> BoneMatData;

	FbxExBoneFrame() 
	{
	}

	void Write(GameEngineFile& _File) override
	{
		_File.Write(BoneIndex);
		_File.Write(BoneParentIndex);
		_File.Write(BoneMatData);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(BoneIndex);
		_File.Read(BoneParentIndex);
		_File.Read(BoneMatData);
	}
};

class FbxExAniData : public GameEngineSerializObject
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

	void Write(GameEngineFile& _File) override
	{
		_File.Write(AniName);
		_File.Write(StartTime);
		_File.Write(EndTime);
		_File.Write(TimeStartCount);
		_File.Write(TimeEndCount);
		_File.Write(FrameCount);
		_File.Write(TimeMode);
		_File.Write(FbxModeCount);
		_File.Write(FbxModeRate);
		_File.Write(AniFrameData);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(AniName);
		_File.Read(StartTime);
		_File.Read(EndTime);
		_File.Read(TimeStartCount);
		_File.Read(TimeEndCount);
		_File.Read(FrameCount);
		_File.Read(TimeMode);
		_File.Read(FbxModeCount);
		_File.Read(FbxModeRate);
		_File.Read(AniFrameData);
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
	FbxExAniData() 
		: AniName("")
		, StartTime(0)
		, EndTime(0)
		, TimeStartCount(0)
		, TimeEndCount(0)
		, FrameCount(0)
		, FbxModeCount(0)
		, FbxModeRate(0.0)
		, TimeMode()
	{
	}
	~FbxExAniData() 
	{
	}
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


	void AnimationMatrixLoad(std::shared_ptr<GameEngineFBXMesh> _Mesh, const std::string_view& _Name, int _AnimationIndex);

	FbxExAniData* GetAnimationData(int _Index)
	{
		if (AnimationDatas.size() <= _Index)
		{
			MsgBoxAssert("애니메이션 데이터 범위를 넘어섰습니다");
		}

		return &AnimationDatas[_Index];
	}


	void UserLoad(const std::string_view& _Path);
	void UserSave(const std::string_view& _Path);

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

