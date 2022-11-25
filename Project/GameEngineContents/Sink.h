#pragma once
#include "GamePlayStaticObject.h"

enum class SinkType
{
	Normal,
	Wizard
};

//ΩÃ≈©¥Î
class Sink : public GamePlayStaticObject
{
public:
	Sink();
	~Sink();

	Sink(const Sink& _Other) = delete;
	Sink(Sink&& _Other) noexcept = delete;
	Sink& operator=(const Sink& _Other) = delete;
	Sink& operator=(Sink&& _Other) noexcept = delete;

	void SetSinkMesh(SinkType _Type);

protected:
	void Start() override;

private:
};
