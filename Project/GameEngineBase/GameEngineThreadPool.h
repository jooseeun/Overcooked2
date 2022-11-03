#pragma once
#include <functional>
#include "GameEngineThread.h"
#include <atomic>

enum ThreadWorkType
{
	UserWork = -1,
	Destroy = -2,
};

// Ό³Έν :
class GameEngineThreadPool
{
private:
	class GameEngineThreadJob
	{
	public:
		virtual void Process() = 0;
	};

	class GameEngineThreadCallBackJob : public GameEngineThreadJob
	{
	public:
		std::function<void()> Work;

		void Process()
		{
			if (nullptr == Work)
			{
				return;
			}
			Work();
		}
	};

public:
	// constrcuter destructer
	GameEngineThreadPool();
	GameEngineThreadPool(const std::string& _ThreadName, int _ThreadCount = 0);
	~GameEngineThreadPool();

	// delete Function
	GameEngineThreadPool(const GameEngineThreadPool& _Other) = delete;
	GameEngineThreadPool(GameEngineThreadPool&& _Other) noexcept = delete;
	GameEngineThreadPool& operator=(const GameEngineThreadPool& _Other) = delete;
	GameEngineThreadPool& operator=(GameEngineThreadPool&& _Other) noexcept = delete;

	void Work(std::function<void()> _CallBack);
	void Initialize(const std::string& _ThreadName, int _ThreadCount = 0);

protected:

private:
	static void ThreadPoolFunction(GameEngineThreadPool* _ThreadPool, GameEngineThread* _Thread, HANDLE _IocpHandle);

	HANDLE IocpHandle;
	int ThreadCount;
	std::atomic<bool> IsRun;
	std::atomic<int> DestroyThreadCount;

	std::vector<GameEngineThread*> Threads;

};

