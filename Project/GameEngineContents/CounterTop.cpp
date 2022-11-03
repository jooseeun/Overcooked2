#include "PreCompile.h"
#include "CounterTop.h"

CounterTop::CounterTop()
	: MyType_(CounterTopType::Normal)
{
}

CounterTop::~CounterTop()
{
}

void CounterTop::Start()
{
	GamePlayStaticObject::Start();
}