#include "PreCompile.h"
#include "GameEngineFBX.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineFBX::GameEngineFBX() 
	:
	IOSetting(nullptr),
	Importer(nullptr),
	Scene(nullptr),
	RootNode(nullptr),
	Manager(nullptr)
{
}




float4x4 GameEngineFBX::FbxMatTofloat4x4(const fbxsdk::FbxAMatrix& _BaseTrans)
{
	float4x4 Mat;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			Mat.Arr2D[y][x] = (float)_BaseTrans.Get(y, x);
		}
	}

	return Mat;
}

fbxsdk::FbxAMatrix GameEngineFBX::float4x4ToFbxAMatrix(const float4x4& _MATRIX)
{
	fbxsdk::FbxAMatrix mat;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mat.mData[y].mData[x] = _MATRIX.Arr2D[y][x];
		}
	}

	return mat;
}

float4 GameEngineFBX::FbxVecTofloat4(const fbxsdk::FbxVector4& _BaseVector)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseVector.mData[0];
	Vec.Arr1D[1] = (float)_BaseVector.mData[1];
	Vec.Arr1D[2] = (float)_BaseVector.mData[2];
	Vec.Arr1D[3] = (float)_BaseVector.mData[3];

	return Vec;

}

float4 GameEngineFBX::FbxVecToTransform(const fbxsdk::FbxVector4& _BaseVector)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseVector.mData[0];
	Vec.Arr1D[1] = (float)_BaseVector.mData[1];
	Vec.Arr1D[2] = -(float)_BaseVector.mData[2];
	Vec.Arr1D[3] = (float)_BaseVector.mData[3];
	return Vec;
}

float4 GameEngineFBX::FbxQuaternionTofloat4(const fbxsdk::FbxQuaternion& _BaseQ)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseQ.mData[0];
	Vec.Arr1D[1] = (float)_BaseQ.mData[1];
	Vec.Arr1D[2] = -(float)_BaseQ.mData[2];
	Vec.Arr1D[3] = -(float)_BaseQ.mData[3];
	return Vec;
}


GameEngineFBX::~GameEngineFBX() 
{
	if (nullptr != Scene)
	{
		Scene->Destroy();
		Scene = nullptr;
	}
	if (nullptr != Importer)
	{
		Importer->Destroy();
		Importer = nullptr;
	}
	if (nullptr != IOSetting)
	{
		IOSetting->Destroy();
		IOSetting = nullptr;
	}
	if (nullptr != Manager)
	{
		Manager->Destroy();
		Manager = nullptr;
	}
}

bool GameEngineFBX::CreateFBXSystemInitialize(const std::string& _Path)
{
		Manager = fbxsdk::FbxManager::Create();
		if (nullptr == Manager)
		{
			MsgBoxAssert("FBX 매니저 생성에 실패했습니다.");
			return false;
		}

	IOSetting = fbxsdk::FbxIOSettings::Create(Manager, IOSROOT);
	Importer = fbxsdk::FbxImporter::Create(Manager, "");

	if (false == 
		Importer->Initialize(GameEngineString::AnsiToUTF8Return(_Path).c_str(), -1, IOSetting))
	{
		Importer->Destroy();
		IOSetting->Destroy();
		MsgBoxAssert("FBX 로드 이니셜라이즈 실패.");
		return false;
	}

	Scene = fbxsdk::FbxScene::Create(Manager, "");

	if (nullptr == Scene)
	{
		MsgBoxAssert("FBX 씬생성 실패.");
		return false;
	}

	if (false == Importer->Import(Scene))
	{
		MsgBoxAssert("FBX 임포트 실패.");
		return false;
	}

	return true;
}

void GameEngineFBX::FBXConvertScene()
{
	AxisVector = { 0.0f, 0.0f, 0.0f, 1.0f };

	fbxsdk::FbxAxisSystem::EFrontVector FrontVector = (fbxsdk::FbxAxisSystem::EFrontVector)-fbxsdk::FbxAxisSystem::eParityOdd;
	fbxsdk::FbxAxisSystem::EUpVector UpVector = fbxsdk::FbxAxisSystem::eYAxis;
	fbxsdk::FbxAxisSystem::ECoordSystem CooreSystem = fbxsdk::FbxAxisSystem::ECoordSystem::eRightHanded;

	fbxsdk::FbxAxisSystem EngineAxisSystem(UpVector, FrontVector, CooreSystem);

	fbxsdk::FbxAxisSystem SourceAxisSystem = Scene->GetGlobalSettings().GetAxisSystem();

	if (SourceAxisSystem != EngineAxisSystem)
	{
		fbxsdk::FbxRootNodeUtility::RemoveAllFbxRoots(Scene);
		EngineAxisSystem.ConvertScene(Scene);

		fbxsdk::FbxAMatrix SourceMatrix;
		SourceAxisSystem.GetMatrix(SourceMatrix);

		fbxsdk::FbxAMatrix EngineMatrix;
		EngineAxisSystem.GetMatrix(EngineMatrix);

		ConvertMatrix = SourceMatrix.Inverse() * EngineMatrix;
	}

	int OriginUpSign = 0;
	int OriginFrontSign = 0;
	int EngineUpSign = 0;
	int EngineFrontSign = 0;

	fbxsdk::FbxAxisSystem::EFrontVector OriginFrontVector = SourceAxisSystem.GetFrontVector(OriginFrontSign);
	fbxsdk::FbxAxisSystem::EFrontVector EngineFrontVector = EngineAxisSystem.GetFrontVector(EngineFrontSign);

	fbxsdk::FbxAxisSystem::EUpVector OriginUpVector = SourceAxisSystem.GetUpVector(OriginUpSign);
	fbxsdk::FbxAxisSystem::EUpVector EngineUpVector = EngineAxisSystem.GetUpVector(EngineUpSign);

	fbxsdk::FbxAxisSystem::ECoordSystem  OriginCoordSystem = SourceAxisSystem.GetCoorSystem();
	fbxsdk::FbxAxisSystem::ECoordSystem  EngineCoordSystem = EngineAxisSystem.GetCoorSystem();

	if (OriginUpVector == EngineUpVector && OriginUpSign == EngineUpSign)
	{
		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == EngineUpVector && OriginUpSign != EngineUpSign)
	{
		if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
		{
			AxisVector.mData[1] += 180;
		}
		else
		{
			AxisVector.mData[0] += 180;
		}

		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
	{


		AxisVector.mData[1] += OriginUpSign * 90;
	}
	else
	{
		AxisVector.mData[0] += OriginUpSign * 90;
		if (OriginUpSign != EngineFrontSign)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += OriginUpSign * 180;
		}
	}

	JointMatrix.SetR(AxisVector);

	if (true == JointMatrix.IsIdentity())
	{
		JointMatrix = ConvertMatrix;
	}

	Scene->GetAnimationEvaluator()->Reset();
	RootNode = Scene->GetRootNode();
	if (nullptr == RootNode)
	{
		MsgBoxAssert("루트노드생성에 실패했습니다.");
	}

	fbxsdk::FbxGeometryConverter Con(Manager);
	if (false == Con.Triangulate(Scene, true))
	{
		MsgBoxAssert("삼각화에 실패했습니다.");
	}

	return;
}

std::vector<FBXNodeInfo> GameEngineFBX::CheckAllNode()
{
	std::vector<FBXNodeInfo> AllNode;

	RecursiveAllNode(RootNode);

	return AllNode;
}

void GameEngineFBX::FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode)
{
	if (nullptr == _RootNode)
	{
		return;
	}

	std::string Name = _RootNode->GetName();
}

void GameEngineFBX::RecursiveAllNode(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function /*= nullptr*/)
{
	// 노드의 정보들을 얻어올수가 있습니다.
	// fbxsdk::FbxNodeAttribute* Info = _Node->GetNodeAttribute();
	if (nullptr != _Function)
	{
		_Function(_Node);
	}

	//FBXNodeInfo& NewNodeInfo = _AllNode.emplace_back();
	//NewNodeInfo.Name = _Node->GetName();
	//NewNodeInfo.Node = _Node;

	fbxsdk::FbxNodeAttribute* Info = _Node->GetNodeAttribute();

	if (nullptr != Info)
	{
		fbxsdk::FbxNodeAttribute::EType Type = Info->GetAttributeType();
	}

	int Count = _Node->GetChildCount();

	for (int i = 0; i < Count; i++)
	{
		fbxsdk::FbxNode* Node = _Node->GetChild(i);
		RecursiveAllNode(Node);
	}

}

void GameEngineFBX::FBXInit(std::string _Path)
{
	if (false == CreateFBXSystemInitialize(_Path))
	{
		MsgBoxAssert("시스템 로드에 실패했습니다.");
	}

	FBXConvertScene();
}