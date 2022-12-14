#pragma once
#include "GameEngineCamera.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineMesh.h"

struct RenderOption
{
	float DeltaTime = 0.0f;
	float SumDeltaTime = 0.0f;
	int IsAnimation = 0;
	int dummy = 0;
	float4 UV = { 0, 0, 0 };
	float Random = 0.0f;
};

struct PixelData
{
	float4 MulColor;
	float4 PlusColor;
	float4 Slice;

	int AlphaFlag;
	float4 AlphaColor;

	PixelData()
		: MulColor(float4::WHITE)
		, PlusColor(float4::ZERO)
		, Slice(float4::ZERO)
		, AlphaFlag(0)
		, AlphaColor(float4::ZERO)
	{

	}
};

// ���� :
class GameEngineMaterial;
class GameEngineShaderResourcesHelper;
class GameEngineRenderer
	: public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;

public:
	RenderOption RenderOptionInst;

	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// float4x4 ViewPort;
	void ChangeCamera(CAMERAORDER _Order);

	inline int GetRenderingOrder()
	{
		return RenderingOrder;
	}

	void SetRenderingOrder(int _Order);

	inline virtual void InstancingOn()
	{
		IsInstancing_ = true;
	};

	GameEngineCamera* GetCamera()
	{
		return Camera;
	}

	void PushRendererToMainCamera();

	void PushRendererToUICamera();

	PixelData& GetPixelData()
	{
		return PixelDataInst;
	}

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

	class GameEngineCamera* Camera;
	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	PixelData PixelDataInst;


private:
	CAMERAORDER CameraOrder;
	int RenderingOrder;
	bool IsInstancing_;

	virtual void Render(float _DeltaTime) = 0;

};

class GameEngineRenderUnit : public std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	GameEngineRenderUnit();
	GameEngineRenderUnit(const GameEngineRenderUnit& _Render);

	inline bool GetIsOn()
	{
		return IsOn && ParentRenderer->IsUpdate();
	}

	inline bool IsDeath()
	{
		return ParentRenderer->IsDeath();
	}

	inline void On()
	{
		IsOn = true;
	}

	inline void Off()
	{
		IsOn = false;
	}

	inline GameEngineRenderer* GetRenderer()
	{
		return ParentRenderer;
	}

	void SetMesh(const std::string& _Name);

	void SetMesh(std::shared_ptr<GameEngineMesh> _Mesh);

	void PushCamera();

	void SetMaterial(const std::string& _Name);

	void EngineShaderResourcesSetting(std::shared_ptr<GameEngineRenderer> _Renderer);

	void Render(float _DeltaTime);

	void SetRenderer(std::shared_ptr < GameEngineRenderer> _Renderer);

	void RenderInstancing(float _DeltaTime, size_t _RanderingCount, std::shared_ptr<GameEngineInstancingBuffer> _Buffer);

	std::shared_ptr<GameEngineMesh> GetMesh();

	std::shared_ptr<GameEngineMaterial> GetMaterial();

	std::shared_ptr<GameEngineMaterial> GetCloneMaterial();

	std::shared_ptr<GameEngineMaterial> CloneMaterial(std::shared_ptr<GameEngineMaterial> _Rendering);

	GameEngineShaderResourcesHelper ShaderResources;

	std::function<bool(float)> RenderFunction;

private:
	bool IsOn;

	GameEngineRenderer* ParentRenderer;
	std::shared_ptr<GameEngineMesh> Mesh; // �� �޽���
	std::shared_ptr<GameEngineMaterial> Material; // �� ��������
	std::shared_ptr<GameEngineInputLayOut> InputLayOut; // ��ǲ�����1 ����
	D3D11_PRIMITIVE_TOPOLOGY Topology;// �̷��� �׸���.

};