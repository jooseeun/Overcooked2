#include "PreCompile.h"
#include "FadeFont.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
FadeFont::FadeFont()
{
}

FadeFont::~FadeFont()
{
}

void FadeFont::Start()
{
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
	//FontRenderer_.lock()->SetText("03:06", "Naughty Squirrel");
	FontRenderer_.lock()->SetColor({ 1.0f,1.0f,1.0f,1 });

	//FontRenderer_.lock()->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontRenderer_.lock()->SetAffectTransform(true);
}

void FadeFont::Update(float _DeltaTime)
{
	if (Color_.w > 0.f)
	{
		if (IsDebug_ == false)
		{
			Color_.w -= _DeltaTime;
		}
		if (Color_.w <= 0.f)
		{
			Color_.w = 0.f;
		}
	}
	else
	{
		if (GoingToDead_ == true)
		{
			return;
		}
		GoingToDead_ = true;
		Color_.w = 0.f;
		Death(1.1f);
	}
	if (IsDebug_ == false)
	{
		GetTransform().SetLocalMove(float4::UP * 70.f * _DeltaTime);
	}
	FontRenderer_.lock()->SetColor(Color_);
	FontRenderer_.lock()->SetText(Str_, "Naughty Squirrel");
	FontRenderer_.lock()->SetSize(Size_);
}

void FadeFont::End()
{
}