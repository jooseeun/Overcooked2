#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader() 
	: ShaderPtr(nullptr)
	, IsDeferred(false)
{
	ShaderSettingType = ShaderType::Pixel;
}

GameEnginePixelShader::~GameEnginePixelShader() 
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}


// Color.hlsl
// 같은 쉐이더파일내에
// 버텍스쉐이더를 2개 작성못합니다.

// Color_VS

std::shared_ptr<GameEnginePixelShader> GameEnginePixelShader::Load(
	const std::string& _Path,
	const std::string& _EntryPoint,
	UINT _VersionHigh /*= 5*/, UINT _VersionLow /*= 0*/)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path), _EntryPoint, _VersionHigh, _VersionLow);
}


std::shared_ptr < GameEnginePixelShader> GameEnginePixelShader::Load(
	const std::string& _Path,
	const std::string& _Name,
	const std::string& _EntryPoint,
	UINT _VersionHigh = 5, UINT _VersionLow = 0)
{
	std::shared_ptr < GameEnginePixelShader> NewRes = CreateResName(_Name);
	NewRes->ShaderCompile(_Path, _EntryPoint, _VersionHigh, _VersionLow);
	return NewRes;
}


void GameEnginePixelShader::ShaderCompile(
	const std::string& _Path,
	const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	CreateVersion("ps", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;
	std::wstring UnicodePath = GameEngineString::AnsiToUniCodeReturn(_Path);

	if (S_OK != D3DCompileFromFile(
		UnicodePath.c_str(), // 파일 경로
		nullptr,  // 매크로 ()
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  // 헤더 ()
		_EntryPoint.c_str(), // 진입점 COLOR_VS(
		Version.c_str(),  // vs_5_0
		Flag,
		0,
		&BinaryPtr,
		&Error)
		)
	{
		std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssertString(ErrorText);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(
		BinaryPtr->GetBufferPointer(),
		BinaryPtr->GetBufferSize(),
		nullptr,
		&ShaderPtr))
	{
		MsgBoxAssert("픽셀 쉐이더 핸들 생성에 실패했습니다.");
	}

	ShaderResCheck(GetName());
}


void GameEnginePixelShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgBoxAssert("쉐이더 세팅 오류");
	}

	GameEngineDevice::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}