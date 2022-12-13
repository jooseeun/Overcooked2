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
#include "GameEnginePixelShader.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineCamera::GameEngineCamera()
	: CameraRenderTarget(nullptr)
	, CameraForwardRenderTarget(nullptr)
	, CameraDeferredRenderTarget(nullptr)
{
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::PersPective;
	Near = 100.0f;
	Far = 5000.0f;
	Fov = 60.0f;

	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = Size.x;
	ViewPortDesc.Height = Size.y;
	ViewPortDesc.MinDepth = 0.0f;
	ViewPortDesc.MaxDepth = 1.0f;

	AllRenderUnit_.insert(std::make_pair(RENDERINGPATHORDER::FORWARD, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>()));
	AllRenderUnit_.insert(std::make_pair(RENDERINGPATHORDER::DEFERRED, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>()));
}

GameEngineCamera::~GameEngineCamera()
{
}

bool ZSort(std::shared_ptr<GameEngineRenderer> _Left, std::shared_ptr<GameEngineRenderer> _Right)
{
	return _Left->GetTransform().GetWorldPosition().z > _Right->GetTransform().GetWorldPosition().z;
}

bool ZSortUnit(std::shared_ptr<GameEngineRenderUnit> _Left, std::shared_ptr<GameEngineRenderUnit> _Right)
{
	return _Left->GetRenderer()->GetTransform().GetWorldPosition().z > _Right->GetRenderer()->GetTransform().GetWorldPosition().z;
}

GameEngineInstancing& GameEngineCamera::GetInstancing(const std::string& _Name)
{
	return InstancingMap[_Name];
}

void GameEngineCamera::Render(float _DeltaTime)
{
	// 랜더 전처리 디퍼드 포워드 가리지 않고 사용하는 정보들을 계산한다.
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

	{
		LightDataObject.Count = static_cast<int>(AllLight.size());
		int LightCount = 0;
		for (std::shared_ptr<GameEngineLight> Light : AllLight)
		{
			Light->LightDataUpdate(this);
			LightDataObject.Lights[LightCount++] = Light->GetLightData();
		}
	}

	// 포워드 타겟이 세팅되고
	CameraForwardRenderTarget->Clear();
	CameraForwardRenderTarget->Setting();

	// 행렬 연산 먼저하고
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
			Renderer->RenderOptionInst.SumDeltaTime += _DeltaTime;
			Renderer->GetTransform().SetView(View);
			Renderer->GetTransform().SetProjection(Projection);
			Renderer->GetTransform().CalculateWorldViewProjection();
		}
	}

	//// 포워드
	//{
	//	for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& Group : AllRenderer_)
	//	{
	//		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

	//		std::list<std::shared_ptr<GameEngineRenderer>>& RenderList = Group.second;
	//		RenderList.sort(ZSort);

	//		for (std::shared_ptr<GameEngineRenderer>& Renderer : Group.second)
	//		{
	//			if (false == Renderer->IsUpdate())
	//			{
	//				continue;
	//			}
	//			// 인스턴싱 정보 수집
	//			Renderer->Render(ScaleTime);
	//		}
	//	}
	//}

	{
		std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>::iterator ForwardIter
			= AllRenderUnit_.find(RENDERINGPATHORDER::FORWARD);

		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& OrderMap = ForwardIter->second;

		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>::iterator OrderStartIter = OrderMap.begin();
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>::iterator OrderEndIter = OrderMap.end();

		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderUnit>>>& Group : OrderMap)
		{
			float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

			std::list<std::shared_ptr<GameEngineRenderUnit>>& RenderList = Group.second;
			RenderList.sort(ZSortUnit);

			for (std::shared_ptr<GameEngineRenderUnit>& Unit : Group.second)
			{
				if (false == Unit->GetIsOn())
				{
					continue;
				}
				// 인스턴싱 정보 수집
				Unit->Render(ScaleTime);
			}
		}
	}

	//// 포워드 인스턴싱을 랜더링
	{
		// 쉐이더 리소스 세팅이 다른애들이 있으면
		std::unordered_map<std::string, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<std::string, GameEngineInstancing>::iterator EndIter = InstancingMap.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second.RenderInstancing(_DeltaTime);
		}
	}

	// 포워드 타겟이 세팅되고
	CameraDeferredGBufferRenderTarget->Clear();
	CameraDeferredGBufferRenderTarget->Setting();

	//// 이제부터는 디퍼드 랜더링
	//{
	//	for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& Group : AllRenderer_)
	//	{
	//		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

	//		std::list<std::shared_ptr<GameEngineRenderer>>& RenderList = Group.second;
	//		RenderList.sort(ZSort);

	//		for (std::shared_ptr<GameEngineRenderer>& Renderer : Group.second)
	//		{
	//			if (false == Renderer->IsUpdate())
	//			{
	//				continue;
	//			}
	//			// 인스턴싱 정보 수집
	//			Renderer->Render(ScaleTime);
	//		}
	//	}
	//}


	{
		std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>::iterator ForwardIter
			= AllRenderUnit_.find(RENDERINGPATHORDER::DEFERRED);

		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& OrderMap = ForwardIter->second;

		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>::iterator OrderStartIter = OrderMap.begin();
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>::iterator OrderEndIter = OrderMap.end();

		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderUnit>>>& Group : OrderMap)
		{
			float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

			std::list<std::shared_ptr<GameEngineRenderUnit>>& RenderList = Group.second;
			RenderList.sort(ZSortUnit);

			for (std::shared_ptr<GameEngineRenderUnit>& Unit : Group.second)
			{
				if (false == Unit->GetIsOn())
				{
					continue;
				}
				// 인스턴싱 정보 수집
				Unit->Render(ScaleTime);
			}
		}
	}

	CameraRenderTarget->Clear();
	CameraRenderTarget->Merge(CameraForwardRenderTarget);
	CameraRenderTarget->Merge(CameraDeferredRenderTarget);
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

	// 포워드 타겟 만들기.
	CameraForwardRenderTarget = GameEngineRenderTarget::Create();

	CameraForwardRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraForwardRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());

	// 디퍼드 타겟 만들기
	CameraDeferredGBufferRenderTarget = GameEngineRenderTarget::Create();
	// 색상 0
	CameraDeferredGBufferRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	// 포지션 1
	CameraDeferredGBufferRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	// 노말 2
	CameraDeferredGBufferRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraDeferredGBufferRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());

	CameraDeferredRenderTarget = GameEngineRenderTarget::Create();

	CameraDeferredRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraDeferredRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
}

void GameEngineCamera::PushRenderer(std::shared_ptr<GameEngineRenderer> _Renderer)
{
	AllRenderer_[_Renderer->RenderingOrder].push_back(_Renderer);
}

void GameEngineCamera::PushRenderUnit(std::shared_ptr < GameEngineRenderUnit> _RenderUnit)
{
	if (nullptr == _RenderUnit)
	{
		MsgBoxAssert("랜더유니트가 존재하지 않습니다.");
	}

	RENDERINGPATHORDER Path = RENDERINGPATHORDER::FORWARD;

	if (true == _RenderUnit->GetMaterial()->GetPixelShader()->GetIsDeferred())
	{
		Path = RENDERINGPATHORDER::DEFERRED;
	}

	AllRenderUnit_[Path][_RenderUnit->GetRenderer()->RenderingOrder].push_back(_RenderUnit);
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

void GameEngineCamera::PushLight(std::shared_ptr<class GameEngineLight> _Light)
{
	if (true == AllLight.contains(_Light))
	{
		return;
	}

	AllLight.insert(_Light);
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
