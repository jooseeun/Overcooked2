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

	GetCollisionObject()->GetTransform().SetWorldScale({100, 50, 100});
	GetCollisionObject()->GetTransform().SetWorldMove({0, 25, 0});
}