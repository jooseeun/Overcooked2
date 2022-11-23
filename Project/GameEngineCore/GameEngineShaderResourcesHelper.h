#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineShader.h"

// 설명 :
class GameEngineShader;
class GameEngineShaderResourcesHelper
{
	friend GameEngineShader;

public:
	// constrcuter destructer
	GameEngineShaderResourcesHelper();
	~GameEngineShaderResourcesHelper();

	// delete Function
	//GameEngineShaderResourcesHelper(const GameEngineShaderResourcesHelper& _Other) = delete;
	//GameEngineShaderResourcesHelper(GameEngineShaderResourcesHelper&& _Other) noexcept = delete;
	//GameEngineShaderResourcesHelper& operator=(const GameEngineShaderResourcesHelper& _Other) = delete;
	//GameEngineShaderResourcesHelper& operator=(GameEngineShaderResourcesHelper&& _Other) noexcept = delete;

	void AllResourcesSetting();

	void AllResourcesReset();

	void ResourcesCheck(std::shared_ptr < GameEngineMaterial> _Line);

	template<typename Res>
	void SetConstantBufferLink(const std::string& _Name, const Res& Data)
	{
		SetConstantBufferLink(_Name, &Data, sizeof(Res));
	}

	void SetConstantBufferLink(const std::string& _Name, const void* Data, UINT _Size);

	template<typename Res>
	void SetConstantBufferNew(const std::string& _Name, const Res& Data)
	{
		SetConstantBufferNew(_Name, &Data, sizeof(Res));
	}

	template<typename Res>
	Res* GetConstantBufferNewData(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);


		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSettingMap.find(UpperName);

		if (FindIter == ConstantBufferSettingMap.end())
		{
			return nullptr;
		}
		int TypeSize = sizeof(Res);

		if (TypeSize != FindIter->second.Res->GetBufferDesc().ByteWidth)
		{
			MsgBoxAssert("상수버퍼의 데이터를 다른 크기의 데이터로 가져오려고 했습니다.");
		}

		// FindIter->second.OriginalData[0] SetData

		// Res* Data = reinterpret_cast<Res*>(&FindIter->second.OriginalData[0]);
		Res* Data = reinterpret_cast<Res*>(&FindIter->second.OriginalData[0]);

		return Data;
	}


	void SetConstantBufferNew(const std::string& _Name, const void* Data, UINT _Size);


	std::shared_ptr < GameEngineTexture> SetTexture(const std::string& _Name, const std::string& _TextureName);

	std::shared_ptr < GameEngineTexture> SetTexture(const std::string& _Name, const std::string& _FolderTextureName, int _Index);

	std::shared_ptr < GameEngineTexture> SetTexture(const std::string& _Name, std::shared_ptr<GameEngineTexture> _TextureName);


	std::shared_ptr < GameEngineSampler> SetSampler(const std::string& _Name, const std::string& _TextureName);

	std::shared_ptr < GameEngineSampler> SetSampler(const std::string& _Name, std::shared_ptr < GameEngineSampler> _SamplerName);

	void AllConstantBufferNew();

	bool IsTexture(const std::string& _Name);

	bool IsSampler(const std::string& _Name);

	bool IsConstantBuffer(const std::string& _Name);

	bool IsStructuredBuffer(const std::string& _Name);

	GameEngineStructuredBufferSetter* GetStructuredBuffer(const std::string& _Name);

	std::multimap<std::string, GameEngineStructuredBufferSetter>& GetStructuredBufferSettingMap()
	{
		return StructuredBufferSettingMap;
	}

	void ShaderCheck(std::shared_ptr < GameEngineShader> _Shader);

protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSettingMap;
	std::multimap<std::string, GameEngineTextureSetter> TextureSettingMap;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSettingMap;
	std::multimap<std::string, GameEngineStructuredBufferSetter> StructuredBufferSettingMap;

	void BindConstantBuffer(GameEngineConstantBufferSetter& _Setter, std::shared_ptr < GameEngineConstantBuffer> _Res);
	void BindSampler(GameEngineSamplerSetter& _Setter, std::shared_ptr < GameEngineSampler> _Res);
	void BindTexture(GameEngineTextureSetter& _Setter, std::shared_ptr < GameEngineTexture> _Res);
	void BindStructuredBuffer(GameEngineStructuredBufferSetter& _Setter, std::shared_ptr < GameEngineStructuredBuffer> _Res);
};

