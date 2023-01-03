#pragma once
#include "GamePlayObject.h"

enum class MOVECARSTATE
{
	WAIT, //운전 준비
	DRIVE, //운전
	ARRIVAL //도착
};

class MoveCar : public GamePlayObject
{
	friend class TrafficLightBloom;
public:
	MoveCar();
	~MoveCar();

	MoveCar(const MoveCar& _Other) = delete;
	MoveCar(MoveCar&& _Other) noexcept = delete;
	MoveCar& operator=(const MoveCar& _Other) = delete;
	MoveCar& operator=(MoveCar&& _Other) noexcept = delete;

	void SetCarMesh(const std::string& _Name)
	{
		MeshName_ = _Name;
		GetFBXMesh()->SetFBXMesh(MeshName_);
		GetFBXMesh()->GetTransform().SetWorldScale({ 90.f, 90.f, 90.f });
	}

	void SetStartPos(float4 _Pos)
	{
		StartPos_ = _Pos;
	}

	void SetEndPos(float4 _Pos)
	{
		EndPos_ = _Pos;
	}
	
	void SetStartTime(float _Time)
	{
		StartTime_ = _Time;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	MOVECARSTATE State_;

	float StackInterval_;
	float TimeInterval_;

	float4 StartPos_;
	float4 EndPos_;

	bool IsMove_;
	bool IsSound_;

	float StartTime_;
	float StackTime_;

	std::string MeshName_;

	void SendObjectType(std::shared_ptr<ObjectStartPacket> Packet) override 
	{
		Packet->ExceptionData = ExceptionObject::MoveCar;
		Packet->Animation = MeshName_;
	}
	//void SetServerCookingGage(std::shared_ptr<ObjectCookingGagePacket> _Packet) override
	//{

	//}

	void SetServerCookingGage(std::shared_ptr<ObjectCookingGagePacket> _Packet) override;


	static std::list<MoveCar*> InstList_;
	static MoveCar* SelectCar();
	static bool IsWattingCar();
	static bool IsMovingCar();
};

