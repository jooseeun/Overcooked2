#pragma once
#include <GameEngineBase/GameEngineTransform.h>
#include "GameEngineTexture.h"

namespace GameEngineDebug
{
	void Debug3DInitialize();
	void Debug3DDestroy();

	void DrawBox(const GameEngineTransform& _Trans, const float4& _Color);
	void DrawBox(const GameEngineTransform& _Trans, std::shared_ptr<GameEngineCamera> _Camera, const float4& _Color);
	void DrawBox(const float4& _Pos, const float4& _Scale, const float4& _Rot, const float4& _Color);

	void DrawTexture(const std::string& _Texture, const float4& _Pos, const float4& _Scale = float4::ZERO, const float4& _Rot = float4::ZERO);
	void DrawTexture(const std::string& _Texture, std::shared_ptr<GameEngineCamera> _Camera, const float4& _Pos, const float4& _Scale = float4::ZERO, const float4& _Rot = float4::ZERO);

	void DrawTexture(std::shared_ptr<GameEngineTexture> _Texture, const float4& _Pos, const float4& _Scale = float4::ZERO, const float4& _Rot = float4::ZERO);
	void DrawTexture(std::shared_ptr<GameEngineTexture> _Texture, std::shared_ptr<GameEngineCamera> _Camera, const float4& _Pos, const float4& _Scale = float4::ZERO, const float4& _Rot = float4::ZERO);

	void DrawSphere(const GameEngineTransform& _Trans, const float4& _Color);
	void DrawSphere(const GameEngineTransform& _Trans, std::shared_ptr<GameEngineCamera> _Camera, const float4& _Color);

	void Debug3DRender();

	void SetWireFrame();

	void SetFillSolid();
}