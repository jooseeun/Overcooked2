#pragma once
#include <crtdbg.h>
#include <string>
#include <assert.h>
#include <Windows.h>


// Ό³Έν :
namespace GameEngineDebug
{
//public:
	void LeakCheckOn();
	void ConsoleOpen();

	void OutPutString(const std::string& _Text);

	void Destroy();

	void GetLastErrorPrint();
};

#define MsgBox(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK);  

#define MsgBoxAssert(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK); \
assert(false); 

#define MsgBoxAssertString(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK); \
assert(false); 
