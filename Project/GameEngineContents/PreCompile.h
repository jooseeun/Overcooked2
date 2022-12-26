#pragma once

#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <WinSock2.h>
#include <stdint.h>
#include <sstream>
#include <Windows.h>

#include <string>

#include <map>
#include <list>
#include <set>
#include <vector>
#include <chrono>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// base
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameServerNet.h>
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>

// core
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineMaterial.h>
#include <GameEngineCore/GameEngineFBXMesh.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineCoreDebug.h>
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GlobalIOManager.h>

// contents
#include "MapEditorGUI.h"
#include "MapEditorWindow.h"
#include "LevelActor.h"
#include "GlobalBloomActor.h"
#include "GamePlayObject.h"
#include "GamePlayMapObject.h"
#include "GamePlayFloor.h"
#include "Enums.h"
#include "MouseInputWindow.h"
#include "GlobalMouseInput.h"
#include "GamePacket.h"
#include "ServerInitManager.h"


