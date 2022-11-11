#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInstancing.h"
#include "GameEngineStructuredBuffer.h"
#include <GameEngineBase/GameEngineWindow.h>



GameEngineCamera::GameEngineCamera() 
	: CameraRenderTarget(nullptr)
{
	// 윈도우가 여러분들 생각하기 가장 쉬운 비율이라서 여기서 하는거고.
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::PersPective;
	Near = 0.1f;
	Far = 1000000.0f;
	Fov = 60.0f;

	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = Size.x;
	ViewPortDesc.Height = Size.y;
	ViewPortDesc.MinDepth = 0.0f;
	ViewPortDesc.MaxDepth = 1.0f;
}

GameEngineCamera::~GameEngineCamera() 
{
}

bool ZSort(std::shared_ptr<GameEngineRenderer> _Left, std::shared_ptr<GameEngineRenderer> _Right)
{
	return _Left->GetTransform().GetWorldPosition().z > _Right->GetTransform().GetWorldPosition().z;
}

GameEngineInstancing* GameEngineCamera::GetInstancing(const std::string& _Name)
{
	std::shared_ptr<GameEngineMaterial> Instancing = GameEngineMaterial::Find(_Name);
	return GetInstancing(Instancing);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	CameraRenderTarget->Clear();
	CameraRenderTarget->Setting();

	// 순서적으로보면 레스터라이저 단계이지만 변경이 거의 없을거기 때문에.
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortDesc);

	// 랜더하기 전에 
	View.LookToLH(
		GetActor()->GetTransform().GetLocalPosition(), 
		GetActor()->GetTransform().GetForwardVector(), 
		GetActor()->GetTransform().GetUpVector());

	switch (Mode)
	{
	case CAMERAPROJECTIONMODE::PersPective:
		Projection.PerspectiveFovLH(Fov, Size.x, Size.y, Near, Far);
		break;
	case CAMERAPROJECTIONMODE::Orthographic:
		Projection.OrthographicLH(Size.x, Size.y, Near, Far);
		break;
	default:
		break;
	}

	float4 WindowSize = GameEngineWindow::GetInst()->GetScale();

	// 인스턴싱정보를 초기화해요.
	{
		std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator EndIter = InstancingMap.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second.DataInsert = 0;
		}
	}

	{
		// 랜더링 하면서 인스턴싱 데이터를 수집하고
		// 수집하면서 ++DataInsert
		// 랜더링 하기 전에
		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& Group : AllRenderer_)
		{
			float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

			std::list<std::shared_ptr<GameEngineRenderer>>& RenderList = Group.second;
			RenderList.sort(ZSort);

			for (std::shared_ptr<GameEngineRenderer>& Renderer : Group.second)
			{
				if (false == Renderer->IsUpdate())
				{
					continue;
				}

				Renderer->RenderOptionInst.DeltaTime = _DeltaTime;
				Renderer->RenderOptionInst.SumDeltaTime = _DeltaTime;
				Renderer->GetTransform().SetView(View);
				Renderer->GetTransform().SetProjection(Projection);
				Renderer->GetTransform().CalculateWorldViewProjection();

				// 인스턴싱 정보 수집
				Renderer->Render(ScaleTime);
			}
		}
	}

	// 다끝나면 인스턴싱을 랜더링
	{
		// 쉐이더 리소스 세팅이 다른애들이 있으면
		std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator EndIter = InstancingMap.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (GameEngineInstancing::MinInstancingCount > StartIter->second.Count)
			{
				continue;
			}

			GameEngineMaterial* Pipe = StartIter->first;
			GameEngineInstancing& Instancing = StartIter->second;

			Instancing.InstancingBufferChangeData();
			Instancing.ShaderResources.AllResourcesSetting();
			Instancing.InstancingPipeLine->RenderingInstancing(Instancing.DataInsert, Instancing.Buffer);
		}
	}
}

void GameEngineCamera::SetCameraOrder(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushCamera(std::dynamic_pointer_cast<GameEngineCamera>(shared_from_this()), _Order);
}

void GameEngineCamera::Start()
{
	CameraRenderTarget = GameEngineRenderTarget::Create();

	CameraRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	// CameraRenderTarget->CreateDepthTexture()
}

void GameEngineCamera::PushRenderer(std::shared_ptr<GameEngineRenderer> _Renderer)
{
	AllRenderer_[_Renderer->RenderingOrder].push_back(_Renderer);
}

float4 GameEngineCamera::GetWorldPositionToScreenPosition(const float4& _Pos)
{
	float4 Pos = _Pos;
	float4x4 ViewPort;
	ViewPort.ViewPort(Size.x, Size.y, 0, 0, 0, 1);

	Pos = Pos * View;
	Pos = Pos * Projection;
	Pos /= Pos.w;
	Pos = Pos * ViewPort;
	return Pos;
}


GameEngineInstancing* GameEngineCamera::GetInstancing(std::shared_ptr < GameEngineMaterial> _Pipe)
{
	if (nullptr == _Pipe)
	{
		MsgBoxAssert("존재하지 않는 파이프라인의 인스턴싱 데이터를 가져올수 없습니다.");
	}

	std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator FindIter
		= InstancingMap.find(_Pipe.get());


	return &FindIter->second;
}


void GameEngineCamera::PushInstancing(std::shared_ptr<GameEngineMaterial> _Pipe, int Count)
{
	if (false == _Pipe->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("인스턴싱이 불가능한 랜더러 입니다.")
	}

	// Camera->gameenginepipeline

	GameEngineInstancing& Instancing = InstancingMap[_Pipe.get()];

	Instancing.Count += Count;

}

int GameEngineCamera::PushInstancingIndex(std::shared_ptr<GameEngineMaterial> _Pipe)
{
	int InsertCount = InstancingMap[_Pipe.get()].DataInsert;
	return PushInstancingData(_Pipe, &InsertCount, sizeof(int));
}


int GameEngineCamera::PushInstancingData(std::shared_ptr<GameEngineMaterial> _Pipe, void* _DataPtr, int _Size)
{
	int DataOffset = InstancingMap[_Pipe.get()].DataInsert * _Size;

	// 넣어주다가 사이즈가 오버되면 어떻하지?
	// 아니다.
	// PushInstancing에서 이미 버퍼는 충분한 사이즈만큼 늘어나 있어야 한다.

	char* DataPtr = &InstancingMap[_Pipe.get()].DataBuffer[DataOffset];
	memcpy_s(DataPtr, InstancingMap[_Pipe.get()].DataBuffer.size() - DataOffset, _DataPtr, _Size);
	DataOffset += _Size;

	int ResultIndex = InstancingMap[_Pipe.get()].DataInsert;

	++InstancingMap[_Pipe.get()].DataInsert;

	return ResultIndex;
}


void GameEngineCamera::Release(float _DelataTime)
{
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& Group = StartGroupIter->second;
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator GroupStart = Group.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseUpdate(_DelataTime);
			if (true == (*GroupStart)->IsDeath())
			{
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}

		}
	}
}

float4 GameEngineCamera::GetMouseScreenPosition() 
{
	POINT P;

	GetCursorPos(&P);

	ScreenToClient(GameEngineWindow::GetHWND(), &P);

	return { static_cast<float>(P.x), static_cast<float>(P.y) };
}

float4 GameEngineCamera::GetMouseMyPosition()
{
	float4 ScreenPos = GetMouseScreenPosition();
	float4 WindowScale = GameEngineWindow::GetScale();
	return { ScreenPos.x - WindowScale.x * 0.5f, -ScreenPos.y + WindowScale.y * 0.5f, 0 };
}

float4 GameEngineCamera::GetMouseMyPositionWithRotation()
{
	float4 Result = GetMouseMyPosition();

	float4x4 CameraRotation;
	CameraRotation.RotationDegree(GetTransform().GetWorldRotation());
	Result *= CameraRotation;

	return Result;
}

void GameEngineCamera::Update(float _DeltaTime) 
{
	float4 MousePos = GetMouseWorldPosition();
	MousePos.w = 0.0f;
	MouseDir = MousePos - PrevMouse;
	PrevMouse = MousePos;
}

// 뷰포트에 있는거죠?
float4 GameEngineCamera::GetMouseWorldPosition()
{
	float4 Pos = GetMouseScreenPosition();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.x, Size.y, 0, 0, 0, 1);
	ViewPort.Inverse();

	float4x4 ProjectionInvers = Projection.InverseReturn();

	Pos = Pos * ViewPort;
	Pos = Pos * ProjectionInvers;
	// 마우스는 뷰포트의 좌표다?

	return Pos;
}


float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

void GameEngineCamera::ChangeRenderingOrder(std::shared_ptr<GameEngineRenderer> _Renderer, int _ChangeOrder)
{
	// 0번째에서 삭제되고
	AllRenderer_[_Renderer->GetRenderingOrder()].remove(_Renderer);

	_Renderer->RenderingOrder = _ChangeOrder;

	// 10000번째로 이동한다.
	AllRenderer_[_Renderer->GetRenderingOrder()].push_back(_Renderer);
}

void GameEngineCamera::OverRenderer(std::shared_ptr < GameEngineCamera> _NextCamera)
{
	if (nullptr == _NextCamera)
	{
		MsgBoxAssert("next camera is nullptr! fuck you");
		return;
	}

	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& Group = StartGroupIter->second;
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator GroupStart = Group.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			std::shared_ptr<GameEngineActor> Root = (*GroupStart)->GetRoot<GameEngineActor>();

			if (true == Root->IsLevelOver)
			{
				_NextCamera->AllRenderer_[StartGroupIter->first].push_back(*GroupStart);
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}

		}
	}
}
