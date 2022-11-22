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
	float4 UV;
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


// 랜더타겟이 세팅되어 있다면 이녀석으로 그릴수가 있다.

class GameEngineRenderUnit : public std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	GameEngineRenderUnit();

	GameEngineRenderUnit(const GameEngineRenderUnit& _Render);

	inline void On()
	{
		IsOn = true;
	}

	inline void Off()
	{
		IsOn = false;
	}

	void SetMesh(const std::string& _Name);

	void SetMesh(std::shared_ptr<GameEngineMesh> _Mesh);

	void SetMaterial(const std::string& _Name);

	void EngineShaderResourcesSetting(std::shared_ptr<GameEngineRenderer> _Renderer);

	void Render(float _DeltaTime);

	void SetRenderer(std::shared_ptr < GameEngineRenderer> _Renderer);

	std::shared_ptr < GameEngineMaterial> GetMaterial();

	std::shared_ptr < GameEngineMaterial> GetCloneMaterial();

	std::shared_ptr < GameEngineMaterial> ClonePipeLine(std::shared_ptr<GameEngineMaterial> _Rendering);

	GameEngineShaderResourcesHelper ShaderResources;

private:
	bool IsOn;
	std::weak_ptr<GameEngineRenderer> ParentRenderer;
	std::shared_ptr<GameEngineMesh> Mesh; // 이 메쉬를
	std::shared_ptr<GameEngineMaterial> Material; // 이 설정으로
	std::shared_ptr<GameEngineInputLayOut> InputLayOut;
	D3D11_PRIMITIVE_TOPOLOGY Topology;// 이렇게 그린다.
};


// 설명 :
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

    std::shared_ptr<GameEngineMaterial> ClonePipeLine(std::shared_ptr<GameEngineMaterial> _Rendering);

    inline int GetRenderingOrder() 
    {
        return RenderingOrder;
    }

    void SetRenderingOrder(int _Order);

	virtual void InstancingOn() 
	{
		IsInstancing_ = true;
	};

	void EngineShaderResourcesSetting(GameEngineShaderResourcesHelper* _ShaderResources);

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

    std::weak_ptr<class GameEngineCamera> Camera;

	PixelData PixelDataInst;


private:
	CAMERAORDER CameraOrder;
    int RenderingOrder;
	bool IsInstancing_;

	virtual void Render(float _DeltaTime) = 0;

};

