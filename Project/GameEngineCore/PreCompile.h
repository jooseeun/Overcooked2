#pragma once

// server
#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <WinSock2.h>
#include <stdint.h>
#include <sstream>
#include <Windows.h>

// std
#include <map>
#include <set>
#include <list>
#include <vector>
#include <chrono>
#include <string>
#include <string_view>

// directx
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXCollision.h>
#include <DirectXPackedVector.h>

#pragma comment(lib, "DXGI")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// base
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineSound.h>

// core
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineMaterial.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GlobalIOManager.h>

// contents
