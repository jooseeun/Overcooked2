#pragma once

// std and direct
#include <string>

#include <map>
#include <list>
#include <set>
#include <vector>
#include <chrono>

#include <Windows.h>

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
#include "GamePlayObject.h"
#include "GamePlayMapObject.h"
#include "GamePlayFloor.h"
#include "Enums.h"
#include "GlobalMouseInput.h"
