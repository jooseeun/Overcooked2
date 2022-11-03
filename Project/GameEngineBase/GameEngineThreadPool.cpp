#include "PreCompile.h"
#include "GameEngineThreadPool.h"
#include "GameEngineDebug.h"


GameEngineThreadPool::GameEngineThreadPool(const std::string& _ThreadName, int _ThreadCount /*= 0*/)
{
	Initialize(_ThreadName, _ThreadCount);
}

GameEngineThreadPool::GameEngineThreadPool()
{

}

void GameEngineThreadPool::Initialize(const std::string& _ThreadName, int _ThreadCount /*= 0*/)
{
	ThreadCount = _ThreadCount;
	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount = Info.dwNumberOfProcessors;
	}

	IocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	if (nullptr == IocpHandle)
	{
		MsgBoxAssert("IOCP 핸들 생성에 실패했습니다.");
		return;
	}

	IsRun = true;
	DestroyThreadCount = 0;
	for (size_t i = 0; i < ThreadCount; i++)
	{
		GameEngineThread* NewThread = new GameEngineThread();

		Threads.push_back(NewThread);

		NewThread->SetName(_ThreadName + std::to_string(i));
		NewThread->Start(_ThreadName + std::to_string(i), std::bind(ThreadPoolFunction, this, NewThread, IocpHandle));
	}
}

void GameEngineThreadPool::ThreadPoolFunction(GameEngineThreadPool* _ThreadPool, GameEngineThread* _Thread, HANDLE _IocpHandle)
{
	DWORD Byte;
	ULONG_PTR CompletionKey;
	LPOVERLAPPED lpOverlapped;

	while (_ThreadPool->IsRun)
	{
		GetQueuedCompletionStatus(_IocpHandle, &Byte, &CompletionKey, &lpOverlapped, INFINITE);

		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);
		switch (WorkType)
		{
		case UserWork:
		{
			GameEngineThreadCallBackJob* Job = reinterpret_cast<GameEngineThreadCallBackJob*>(CompletionKey);
			Job->Process();
			delete Job;
			break;
		}
		case Destroy:
			++_ThreadPool->DestroyThreadCount;
			return;
		default:
			break;
		}
	}
}

GameEngineThreadPool::~GameEngineThreadPool()
{
	IsRun = false;
	while (true)
	{
		if (FALSE == PostQueuedCompletionStatus(
			IocpHandle,
			static_cast<DWORD>(ThreadWorkType::Destroy),
			0,
			nullptr)
			)
		{
			MsgBoxAssert("쓰레드에게 콜백잡을 요청하는데 실패했습니다.");
		}

		Sleep(1);
		if (DestroyThreadCount == ThreadCount)
		{
			break;
		}
	}

	for (size_t i = 0; i < Threads.size(); i++)
	{
		Threads[i]->Join();
		delete Threads[i];
	}
}

void GameEngineThreadPool::Work(std::function<void()> _CallBack)
{
	if (nullptr == _CallBack)
	{
		MsgBoxAssert("유효하지 않은 함수 포인터 입니다. 이 함수포인터는 쓰레드에게 맡길수 없습니다.");
	}

	GameEngineThreadCallBackJob* NewJob = new GameEngineThreadCallBackJob();
	NewJob->Work = _CallBack;
	if (FALSE == PostQueuedCompletionStatus(
		IocpHandle,
		static_cast<DWORD>(ThreadWorkType::UserWork),
		reinterpret_cast<ULONG_PTR>(NewJob),
		nullptr)
		)
	{
		MsgBoxAssert("쓰레드에게 콜백잡을 요청하는데 실패했습니다.");
	}
}

