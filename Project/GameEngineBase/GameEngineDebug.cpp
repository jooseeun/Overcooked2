#include "PreCompile.h"
#include "GameEngineDebug.h"
#include <iostream>


namespace GameEngineDebug
{
	HANDLE hConsole = nullptr;

	void LeakCheckOn()
	{
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	}

	void ConsoleOpen()
	{

		if (AllocConsole())
		{
			FILE* FIle;
			freopen_s(&FIle, "CONIN$", "rb", stdin);
			freopen_s(&FIle, "CONOUT$", "wb", stdout);
			freopen_s(&FIle, "CONOUT$", "wb", stderr);

			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::cout << "Console Start" << std::endl;
		}
	}

	void OutPutString(const std::string& _Text)
	{
		// #ifdef _DEBUG
		OutputDebugStringA((_Text + "\n").c_str());
		// #endif
	}

	void Destroy()
	{
		if (nullptr != hConsole)
		{
			FreeConsole();
		}
	}

	void GetLastErrorPrint()
	{
		DWORD error = GetLastError();
		char* message = nullptr;

		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&message,
			0,
			nullptr);

		if (nullptr != message)
		{
			std::string Text = "Code : ";
			Text += std::to_string(error);
			Text += " Message : ";
			Text += message;

			MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK);
			LocalFree(message);
		}
	}
}