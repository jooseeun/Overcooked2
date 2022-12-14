#pragma once
#include "GameEngineTexture.h"
#include <vector>
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineRenderer.h"

class GameEngineRenderTarget;
class GameEnginePostEffect	: public std::enable_shared_from_this<GameEnginePostEffect>
{
private:
	bool IsUpdate_ = true;

public:
	bool IsUpdate() 
	{
		return IsUpdate_;
	}

	virtual void On()
	{
		IsUpdate_ = true;
	}

	virtual void Off()
	{
		IsUpdate_ = false;
	}

public:
	virtual void EffectInit() = 0;
	virtual void Effect(std::shared_ptr<GameEngineRenderTarget> _Render) = 0;

	virtual ~GameEnginePostEffect() 
	{

	}
};

// 설명 :
class GameEngineStatusWindow;
class GameEngineDepthStencilTexture;
class GameEngineRenderTarget : public GameEngineRes<GameEngineRenderTarget>, public std::enable_shared_from_this<GameEngineRenderTarget>
{
	friend GameEngineStatusWindow;

public:
	static ID3D11RenderTargetView* PrevRenderTargetViews;
	static ID3D11DepthStencilView* PrevDepthStencilView;

	static void GetPrevRenderTarget();
	static void SetPrevRenderTarget();

public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr < GameEngineRenderTarget> Create(const std::string& _Name);

	static std::shared_ptr < GameEngineRenderTarget> Create();

	void CreateRenderTargetTexture(ID3D11Texture2D* _Texture, float4 _Color);

	void CreateRenderTargetTexture(float4 _Size, float4 _Color);

	void CreateRenderTargetTexture(float4 _Size, DXGI_FORMAT _Format, float4 _Color);

	// 직접 텍스처를 만들어내는 기능
	void CreateRenderTargetTexture(D3D11_TEXTURE2D_DESC _Data, float4 _Color);

	void CreateRenderTargetTexture(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);

	void SettingDepthTexture(std::shared_ptr<GameEngineTexture> _Texture);

	void Clear();

	void Setting();

	void CreateDepthTexture(int _Index = 0);

	inline std::shared_ptr<GameEngineTexture> GetDepthTexture()
	{
		return DepthTexture;
	}

	std::shared_ptr < GameEngineTexture> GetRenderTargetTexture(size_t _Index);

	void Copy(std::shared_ptr<GameEngineRenderTarget> _Other, int _Index = 0);

	void Merge(std::shared_ptr<GameEngineRenderTarget> _Other, int _Index = 0);
	
	// void Effect(GameEngineMaterial* _Other, GameEngineShaderResourcesHelper* _ShaderResourcesHelper);

	void Effect(std::shared_ptr<GameEngineRenderUnit> _RenderSet);

	void EffectProcess();


protected:
	std::vector< std::shared_ptr<GameEngineTexture>> RenderTargets;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews;
	std::vector<ID3D11ShaderResourceView*> ShaderResourceViews;
	std::vector<float4> ClearColors;

	ID3D11DepthStencilView* DepthStencilView;

	std::shared_ptr<GameEngineRenderUnit> MergeUnit;

	std::shared_ptr<GameEngineTexture> DepthTexture;

	// Post이펙트 부분
private:
	std::list< std::shared_ptr<GameEnginePostEffect>> Effects;

public:
	template<typename EffectType>
	std::shared_ptr<EffectType> AddEffect()
	{
		std::shared_ptr <GameEnginePostEffect> NewEffect = std::make_shared<EffectType>();
		NewEffect->EffectInit();
		Effects.push_back(NewEffect);

		return std::dynamic_pointer_cast<EffectType>(NewEffect);
	}
};

