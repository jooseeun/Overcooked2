#pragma once
class LoadingData
{
public:
	LoadingData();
	~LoadingData();

	LoadingData(const LoadingData& _Other) = delete;
	LoadingData(const LoadingData&& _Other) noexcept = delete;
	LoadingData& operator=(const LoadingData& _Ohter) = delete;
	LoadingData& operator=(const LoadingData&& _Other) noexcept = delete;

public:
	static void AddFunc(std::string_view _StageName, std::function<void()> _Func);
	static std::function<void()> GetFunc(std::string_view _StageName);

	//static std::string CurStage_; // 1-1, 1-2 ...
private:
	static std::map<std::string, std::function<void()>> AllFunc_;
};
