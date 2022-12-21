#pragma once
#include "GameEngineTransformComponent.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineInstancingBuffer.h"
#include "GameEngineLight.h"
#include <set>

enum class CAMERAPROJECTIONMODE
{
	PersPective,
	Orthographic,
};

enum class RENDERINGPATHORDER
{
	FORWARD,
	DEFERRED,
	MAX,
};

// 설명 :
class GameEngineLight;
class GameEngineLevel;
class GameEngineCamera;
class GameEngineInstancing;
class GameEngineRenderTarget;
class GameEngineMaterial;
class GameEngineRenderUnit;
class GameEngineCamera : public GameEngineTransformComponent
{
	friend GameEngineLevel;
	friend GameEngineRenderer;
	friend GameEngineRenderUnit;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> GetAllRenderer()
	{
		return AllRenderer_;
	}

	inline CAMERAPROJECTIONMODE GetProjectionMode()
	{
		return Mode;
	}

	inline std::shared_ptr<GameEngineRenderTarget> GetCameraRenderTarget()
	{
		return CameraRenderTarget;
	}

	inline std::shared_ptr<GameEngineRenderTarget> GetCameraDeferredGBufferRenderTarget()
	{
		return CameraDeferredGBufferRenderTarget;
	}

	inline std::shared_ptr<GameEngineRenderTarget> GetCameraDeferredLightRenderTarget()
	{
		return CameraDeferredLightRenderTarget;
	}

	void SetCameraOrder(CAMERAORDER _Order);

	inline void SetProjectionMode(CAMERAPROJECTIONMODE _Mode)
	{
		Mode = _Mode;
	}

	// 왼쪽 위가 0,0
	float4 GetMouseScreenPosition();

	float4 GetMouseMyPosition();
	
	float4 GetMouseMyPositionWithRotation();

	float4 GetMouseWorldPosition();

	float4 GetMouseWorldPositionToActor();

	inline float4x4 GetViewMatrix() 
	{
		return View;
	}
	inline float4x4 GetProjectionMatrix()
	{
		return Projection;
	}

	inline float4 GetMouseWorldDir()
	{
		return MouseDir;
	}

	inline void SetProjectionSize(const float4& _Value) 
	{
		Size = _Value;
	}

	inline float4 GetProjectionSize()
	{
		return Size;
	}

	inline std::shared_ptr<class GameEngineRenderTarget> GetCurTarget()
	{
		return CurTarget;
	}

	GameEngineInstancing& GetInstancing(const std::string& _Name);
	float4 GetWorldPositionToScreenPosition(const float4& _Pos);
	void PushLight(std::shared_ptr<class GameEngineLight> _Light);

protected:
	void Start();

	void ChangeRenderingOrder(std::shared_ptr < GameEngineRenderer> _Renderer, int _ChangeOrder);

private:
	void Render(float _DeltaTime);

	void PushRenderer(std::shared_ptr<GameEngineRenderer> _Renderer);

	void PushRenderUnit(std::shared_ptr<GameEngineRenderUnit> _RenderUnit);

	void Release(float _DelataTime);

	void Update(float _DeltaTime) override;

	void OverRenderer(std::shared_ptr < GameEngineCamera> _NextOver);

	std::shared_ptr<class GameEngineRenderTarget> CurTarget;

	std::shared_ptr<GameEngineRenderTarget> CameraRenderTarget;

	std::shared_ptr<GameEngineRenderTarget> CameraForwardRenderTarget;

	std::shared_ptr<GameEngineRenderUnit> DeferredCalLightUnit;

	std::shared_ptr<class GameEngineRenderTarget> CameraDeferredGBufferRenderTarget;

	std::shared_ptr<GameEngineRenderUnit> DeferredMergeUnit;

	std::shared_ptr<class GameEngineRenderTarget> CameraDeferredLightRenderTarget;

	std::shared_ptr<GameEngineRenderTarget> CameraDeferredRenderTarget;

	std::shared_ptr<GameEngineRenderUnit> ShadowRenderStaticUnit;

	std::shared_ptr<GameEngineRenderUnit> ShadowRenderAnimationUnit;

	TransformData ShadowTrans;

	RenderOption ShadowRenderOption;

	class GameEngineConstantBufferSetter* ShadowTransformSetter;

	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> AllRenderer_;

	std::map<RENDERINGPATHORDER, std::map<int, std::list<std::shared_ptr<GameEngineRenderUnit>>>> AllRenderUnit_;

	std::unordered_map<std::string, GameEngineInstancing> InstancingMap;

	std::set<std::shared_ptr<GameEngineLight>> AllLight;

	LightDatas LightDataObject;

	float4x4 View; // 바라보는것
	float4x4 Projection;
	float4x4 ViewPort;
	CAMERAPROJECTIONMODE Mode;

	float4 PrevMouse;
	float4 MouseDir;

	D3D11_VIEWPORT ViewPortDesc;

	// Projection Data
	float4 Size;
	float Near;
	float Far;

	// Perspective
	float Fov;
};

