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
#include "GameEngineShaderResourcesHelper.h"

GameEngineCamera::GameEngineCamera()
	: CameraRenderTarget(nullptr)
	, CameraForwardRenderTarget(nullptr)
	, CameraDeferredRenderTarget(nullptr)
{
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::PersPective;
	Near = 10.0f;
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

	DeferredCalLightUnit = std::make_shared<GameEngineRenderUnit>();
	DeferredCalLightUnit->SetMesh("FullRect");
	DeferredCalLightUnit->SetMaterial("CalDeferredLight");
	DeferredCalLightUnit->ShaderResources.SetConstantBufferLink("LightDatas", LightDataObject);

	DeferredMergeUnit = std::make_shared<GameEngineRenderUnit>();
	DeferredMergeUnit->SetMesh("FullRect");
	DeferredMergeUnit->SetMaterial("CalDeferredMerge");

	ShadowRenderStaticUnit = std::make_shared<GameEngineRenderUnit>();
	ShadowRenderStaticUnit->SetMaterial("ShadowStatic");
	ShadowRenderStaticUnit->ShaderResources.SetConstantBufferLink("TransformData", ShadowTrans);

	ShadowRenderAnimationUnit = std::make_shared<GameEngineRenderUnit>();
	ShadowRenderAnimationUnit->SetMaterial("ShadowAnimation");
	ShadowRenderAnimationUnit->ShaderResources.SetConstantBufferLink("TransformData", ShadowTrans);
	ShadowRenderAnimationUnit->ShaderResources.SetConstantBufferLink("RenderOption", ShadowRenderOption);
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
	CurTarget = CameraForwardRenderTarget;

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

			//Renderer->Render(_DeltaTime);
		}
	}

	{
		std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>::iterator ForwardIter
			= AllRenderUnit_.find(RENDERINGPATHORDER::FORWARD);
	
		std::vector<std::shared_ptr<GameEngineRenderUnit>> TmpUnits;
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& OrderMap = ForwardIter->second;
		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderUnit>>>& Group : OrderMap)
		{
			float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
	
			std::list<std::shared_ptr<GameEngineRenderUnit>>& RenderList = Group.second;
			RenderList.sort(ZSortUnit);
	
			for (std::shared_ptr<GameEngineRenderUnit>& Unit : RenderList)
			{
				if (nullptr != Unit->GetMaterial() && Unit->GetMaterial()->GetName() == "GLASS")
				{
					TmpUnits.push_back(Unit);
					continue;
				}
				if (false == Unit->GetIsOn())
				{
					continue;
				}
				// 인스턴싱 정보 수집
				Unit->Render(ScaleTime);
			}

			for (size_t i = 0; i < TmpUnits.size(); i++)
			{
				TmpUnits[i]->Render(_DeltaTime);
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
	CameraDeferredGBufferRenderTarget->Clear(false);
	CameraDeferredGBufferRenderTarget->Setting();
	CurTarget = CameraDeferredGBufferRenderTarget;
	
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
	
			for (std::shared_ptr<GameEngineRenderUnit>& Unit : RenderList)
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

	{
		for (std::shared_ptr<class GameEngineLight> Light : AllLight)
		{
			GameEngineDevice::GetContext()->RSSetViewports(1, &Light->GetViewPortDesc());
			Light->ShadowTargetSetting();

			for (size_t i = 0; i < static_cast<size_t>(RENDERINGPATHORDER::MAX); i++)
			{
				std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>::iterator ForwardIter
					= AllRenderUnit_.find(static_cast<RENDERINGPATHORDER>(i));

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

						ShadowRenderOption = Unit->GetRenderer()->RenderOptionInst;

						ShadowTrans = Unit->GetRenderer()->GetTransform().GetTransformData();
						ShadowTrans.ViewMatrix = Light->GetLightData().LightViewMatrix;
						ShadowTrans.ProjectionMatrix = Light->GetLightData().LightProjectionMatrix;
						ShadowTrans.CalculateWorldViewProjection();

						if (0 != ShadowRenderOption.IsAnimation)
						{
							GameEngineStructuredBufferSetter* Setter = Unit->ShaderResources.GetStructuredBuffer("ArrAniMationMatrix");
							GameEngineStructuredBufferSetter* ShadowSetter = ShadowRenderAnimationUnit->ShaderResources.GetStructuredBuffer("ArrAniMationMatrix");
							ShadowSetter->Res = Setter->Res;
							ShadowSetter->SetData = Setter->SetData;
							ShadowSetter->Size = Setter->Size;
							ShadowSetter->Count = Setter->Count;
							ShadowSetter->SettingFunction = Setter->SettingFunction;
							ShadowRenderAnimationUnit->SetMesh(Unit->GetMesh());
							ShadowRenderAnimationUnit->Render(ScaleTime);
						}
						else 
						{
							ShadowRenderStaticUnit->SetMesh(Unit->GetMesh());
							ShadowRenderStaticUnit->Render(ScaleTime);
						}
					}
				}
			}
		}
	}
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortDesc);

	CameraDeferredLightRenderTarget->Clear();

	for (std::shared_ptr<class GameEngineLight> Light : AllLight)
	{
		LightDataObject.Count = 1;
		LightDataObject.Lights[0] = Light->GetLightData();

		switch (LightDataObject.Lights[0].LightType)
		{
		case 0: // dir
			DeferredCalLightUnit->SetMesh("FullRect");
			break;
		case 1: // point
			DeferredCalLightUnit->SetMesh("Sphere");
			break;
		case 2: // spot
			break;
		default:
			break;
		}

		DeferredCalLightUnit->ShaderResources.SetTexture("ShadowTex", Light->GetShadowTarget()->GetRenderTargetTexture(0));
		CameraDeferredLightRenderTarget->Effect(DeferredCalLightUnit);
	}
	
	CameraDeferredRenderTarget->Clear();
	CameraDeferredRenderTarget->Effect(DeferredMergeUnit);

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

	DeferredCalLightUnit->ShaderResources.SetTexture("PositionTex", CameraDeferredGBufferRenderTarget->GetRenderTargetTexture(1));
	DeferredCalLightUnit->ShaderResources.SetTexture("NormalTex", CameraDeferredGBufferRenderTarget->GetRenderTargetTexture(2));

	CameraDeferredGBufferRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());

	// 라이트 타겟
	CameraDeferredLightRenderTarget = GameEngineRenderTarget::Create();
	// 디퓨즈라이트
	CameraDeferredLightRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	// 스펙큘러
	CameraDeferredLightRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	// 앰비언트
	CameraDeferredLightRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);


	CameraDeferredRenderTarget = GameEngineRenderTarget::Create();

	CameraDeferredRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraDeferredRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());

	DeferredMergeUnit->ShaderResources.SetTexture("DiffuseTex", CameraDeferredGBufferRenderTarget->GetRenderTargetTexture(0));

	DeferredMergeUnit->ShaderResources.SetTexture("DiffuseLightTex", CameraDeferredLightRenderTarget->GetRenderTargetTexture(0));

	DeferredMergeUnit->ShaderResources.SetTexture("SpacularLightTex", CameraDeferredLightRenderTarget->GetRenderTargetTexture(1));

	DeferredMergeUnit->ShaderResources.SetTexture("AmbientLightTex", CameraDeferredLightRenderTarget->GetRenderTargetTexture(2));

}

void GameEngineCamera::PushRenderer(std::shared_ptr<GameEngineRenderer> _Renderer)
{
	AllRenderer_[_Renderer->RenderingOrder].push_back(_Renderer);
}

void GameEngineCamera::PushRenderUnit(std::shared_ptr<GameEngineRenderUnit> _RenderUnit)
{
	if (nullptr == _RenderUnit)
	{
		MsgBoxAssert("랜더유니트가 존재하지 않습니다.");
	}

	RENDERINGPATHORDER Path = RENDERINGPATHORDER::FORWARD;

	if (nullptr != _RenderUnit->GetMaterial())
	{
		if (true == _RenderUnit->GetMaterial()->GetPixelShader()->GetIsDeferred())
		{
			Path = RENDERINGPATHORDER::DEFERRED;
		}
	}

	_RenderUnit->SetPath(Path);

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
	// 렌더유닛 릴리즈
	for (size_t i = 0; i < static_cast<size_t>(RENDERINGPATHORDER::MAX); i++)
	{
		std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>::iterator ForwardIter
			= AllRenderUnit_.find(static_cast<RENDERINGPATHORDER>(i));

		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& OrderMap = ForwardIter->second;
		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderUnit>>>& Group : OrderMap)
		{
			std::list<std::shared_ptr<GameEngineRenderUnit>>& List = Group.second;
			std::list<std::shared_ptr<GameEngineRenderUnit>>::iterator GroupStart = List.begin();
			std::list<std::shared_ptr<GameEngineRenderUnit>>::iterator GroupEnd = List.end();
			for (; GroupStart != GroupEnd; )
			{
				if (true == (*GroupStart)->IsDeath())
				{
					GroupStart = List.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}
			}
		}
	}

	// 렌더러 릴리즈
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
	AllRenderer_[_Renderer->GetRenderingOrder()].remove(_Renderer);

	std::list<std::shared_ptr<GameEngineRenderUnit>>& Units = _Renderer->GetUnits();
	for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
	{
		for (size_t i = 0; i < static_cast<size_t>(RENDERINGPATHORDER::MAX); i++)
		{
			std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& Group = AllRenderUnit_[static_cast<RENDERINGPATHORDER>(i)];
			int Order = _Renderer->RenderingOrder;
			std::list<std::shared_ptr<class GameEngineRenderUnit>>& List = Group[Order];
			List.remove(Unit);
		}
	}

	_Renderer->RenderingOrder = _ChangeOrder;
		
	for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
	{
		AllRenderUnit_[Unit->GetPath()][_ChangeOrder].push_back(Unit);
	}

	AllRenderer_[_Renderer->GetRenderingOrder()].push_back(_Renderer);
}


void GameEngineCamera::OverRenderer(std::shared_ptr < GameEngineCamera> _NextCamera)
{
	if (nullptr == _NextCamera)
	{
		MsgBoxAssert("next camera is nullptr! fuck you");
		return;
	}

	// 렌더유닛 이동
	for (size_t i = 0; i < static_cast<size_t>(RENDERINGPATHORDER::MAX); i++)
	{
		std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>::iterator ForwardIter
			= AllRenderUnit_.find(static_cast<RENDERINGPATHORDER>(i));

		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& OrderMap = ForwardIter->second;
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>::iterator OrderStartIter = OrderMap.begin();
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>::iterator OrderEndIter = OrderMap.end();

		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderUnit>>>& Group : OrderMap)
		{
			std::list<std::shared_ptr<GameEngineRenderUnit>>& List = Group.second;
			std::list<std::shared_ptr<GameEngineRenderUnit>>::iterator GroupStart = List.begin();
			std::list<std::shared_ptr<GameEngineRenderUnit>>::iterator GroupEnd = List.end();

			for (; GroupStart != GroupEnd; )
			{
				std::shared_ptr<GameEngineRenderUnit> Unit = (*GroupStart);
				if (nullptr == Unit->GetRenderer())
				{
					MsgBoxAssert("랜더러가 존재하지 않는 유니트 입니다.");
				}

				std::shared_ptr<GameEngineActor> Root = Unit->GetRenderer()->GetRoot<GameEngineActor>();
				if (true == Root->IsLevelOver)
				{
					_NextCamera->AllRenderUnit_[static_cast<RENDERINGPATHORDER>(i)][OrderStartIter->first].push_back(*GroupStart);
					GroupStart = List.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}
			}
		}
	}

	// 렌더러 이동
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
