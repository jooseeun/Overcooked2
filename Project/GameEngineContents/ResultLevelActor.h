#pragma once
class ResultLevelActor
{
public:
	ResultLevelActor();
	~ResultLevelActor();


	ResultLevelActor(const ResultLevelActor& _Other) = delete;
	ResultLevelActor(const ResultLevelActor&& _Other) noexcept = delete;
	ResultLevelActor& operator=(const ResultLevelActor& _Ohter) = delete;
	ResultLevelActor& operator=(const ResultLevelActor&& _Other) noexcept = delete;

};

