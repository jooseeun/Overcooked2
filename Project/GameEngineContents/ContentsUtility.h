#pragma once
#include <GameEngineBase/GameEngineMath.h>

namespace ContentsUtility
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		Timer(float _Value);

		Timer& operator=(float _Value)
		{
			Iter_Time_ = _Value;
			Default_Time_ = _Value;
			return *this;
		}

		Timer& operator-=(float _Value)
		{
			Iter_Time_ -= _Value;
			if (Iter_Time_ <= 0.0f)
			{
				Iter_Time_ = 0.0f;
			}
			return *this;
		}

		Timer& operator+=(float _Value)
		{
			Iter_Time_ += _Value;
			return *this;
		}

		bool IsTimeOver()
		{
			if (Iter_Time_ <= 0.0f)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void Off()
		{
			IsTimerOn_ = false;
		}

		void StartTimer()
		{
			On();
			Reset();
		}

		void StartTimer(float _Value)
		{
			On();
			Default_Time_ = _Value;
			Reset();
		}

		void Update(float _DeltaTime)
		{
			Iter_Time_ -= _DeltaTime;
			if (Iter_Time_ <= 0.0f)
			{
				Iter_Time_ = 0.0f;
				if (TimeOverFunc_ != nullptr && CallTimeOverFunc_ == false)
				{
					CallTimeOverFunc_ = true;
					TimeOverFunc_();
				}
			}
		}

		void UpdateFixedTime(float _FixedTime)//Iter_Time_ = FixedTime
		{
			Iter_Time_ = _FixedTime;
			if (Iter_Time_ <= 0.0f)
			{
				Iter_Time_ = 0.0f;
				if (TimeOverFunc_ != nullptr && CallTimeOverFunc_ == false)
				{
					CallTimeOverFunc_ = true;
					TimeOverFunc_();
				}
			}
		}

		inline float* GetCurTimeRef()
		{
			return &Iter_Time_;
		}
		inline float GetCurTime()
		{
			return Iter_Time_;
		}

		void SetTimeOverFunc(std::function<void()> _Func)
		{
			TimeOverFunc_ = _Func;
		}

		//타이머의 초기 시간
		float Default_Time_;

	private:
		//실제 시간
		float Iter_Time_;

		bool IsTimerOn_;

		bool CallTimeOverFunc_ = false;

		std::function<void()> TimeOverFunc_ = nullptr;

		void On()
		{
			IsTimerOn_ = true;
		}

		void Reset()
		{
			Iter_Time_ = Default_Time_;
			CallTimeOverFunc_ = false;
		}

		void SetDefaultTime(float _Value)
		{
			if (_Value <= 0.0f)
			{
				MsgBoxAssert("잘못된 _Value!");
			}
			Default_Time_ = _Value;
		}
	};

	class SyncManager
	{
	public:
		SyncManager();
		~SyncManager();

		void SetReady(int _ID, bool _IsReady)
		{
			Map_[_ID] = _IsReady;
		}

		void SetHost()
		{
			IsHost_ = true;
		}

		bool IsReady(int _ID)
		{
			return Map_[_ID];
		}

		bool IsAllReady()
		{
			if (IsAllReady_ == true)
			{
				return true;
			}

			if (IsHost_ == false) //호스트가 아니면 AllReady체크를 하지 않겠다.
			{
				return false;
			}

			int Count = 0;
			for (auto i : Map_)
			{
				if (i.second == false)
				{
					return false;
				}
				Count++;
			}

			//유저수가 미달일 경우
			if (Count < UserCount_)
			{
				return false;
			}

			IsAllReady_ = true;
			return true;
		}

		void SetIsAllReady(bool _IsAllReady)
		{
			IsAllReady_ = _IsAllReady;
		}

		int UserCount_ = 0;
	private:
		std::map<int, bool> Map_;
		bool IsAllReady_ = false;
		bool IsHost_ = false;
	};
}
