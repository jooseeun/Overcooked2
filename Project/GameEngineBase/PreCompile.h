#pragma once

#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <WinSock2.h>
#include <stdint.h>
#include <sstream>
#include <Windows.h>

// 윈도우 서버 코드들에 대한 구현 라이브러리
#pragma comment (lib, "ws2_32")

// std
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
