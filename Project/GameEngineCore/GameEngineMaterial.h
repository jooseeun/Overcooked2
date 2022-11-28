#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineInstancingBuffer;
class GameEngineMaterial : public GameEngineRes<GameEngineMaterial>
{
public:
	static void AllShaderReset();

	static std::shared_ptr<GameEngineMaterial> Create();

	static std::shared_ptr<GameEngineMaterial> Create(const std::string& _Name);

public:
	// constrcuter destructer
	GameEngineMaterial();
	~GameEngineMaterial();

	// delete Function
	GameEngineMaterial(const GameEngineMaterial& _Other) = delete;
	GameEngineMaterial(GameEngineMaterial&& _Other) noexcept = delete;
	GameEngineMaterial& operator=(const GameEngineMaterial& _Other) = delete;
	GameEngineMaterial& operator=(GameEngineMaterial&& _Other) noexcept = delete;

	void SetVertexShader(const std::string& _Name);

	void SetVertexShader(std::shared_ptr<GameEngineVertexShader> _Shader);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencil(const std::string& _Name);

	void Setting();
	void SettingInstancing();

	//void RenderingInstancing(int _RenderingCount, std::shared_ptr<GameEngineInstancingBuffer> _Buffer);

	inline std::shared_ptr<GameEngineVertexShader> GetVertexShader()
	{
		return VertexShader;
	}

	inline std::shared_ptr<GameEnginePixelShader> GetPixelShader()
	{
		return PixelShader;
	}

	void Copy(std::shared_ptr<GameEngineMaterial> _Original);

	void SetWireFrame();

	void SetFillSolid();

protected:

private:
	std::shared_ptr<GameEngineVertexShader> VertexShader; // ���ؽ����̴� ����

	std::shared_ptr<GameEngineRasterizer> Rasterizer; // �����Ͷ����� ����

	std::shared_ptr<GameEnginePixelShader> PixelShader; // �ȼ����̴� ����

	std::shared_ptr<GameEngineDepthStencil> DepthStencil; // �ƿ�ǲ���� ���� ������ ���� 

	std::shared_ptr<GameEngineBlend> Blend; // �ƿ�ǲ���� �������� ���� 

public:
	void InputAssembler1InstancingVertexBufferSetting(std::shared_ptr<GameEngineInstancingBuffer> _Buffer);

	void VertexShaderSetting();

	void InstancingVertexShaderSetting();

	void RasterizerSetting();

	void PixelShaderSetting();

	void OutputMergerBlendSetting();

	void OutputMergerDepthStencilSetting();

	void InstancingDraw(int _RenderingCount);

	void InstancingDataCollect();
};
