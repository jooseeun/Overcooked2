#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineFBXStaticRenderer;
class LevelActor : public GameEngineActor
{

public:
	LevelActor();
	~LevelActor();

	LevelActor(const LevelActor& _Other) = delete;
	LevelActor(LevelActor&& _Other) noexcept = delete;
	LevelActor& operator=(const LevelActor& _Other) = delete;
	LevelActor& operator=(LevelActor&& _Other) noexcept = delete;

	void SetLevelMesh(std::string_view _Name)
	{
		//std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find("2_1.FBX");

		//if (FindFBXMesh != nullptr)
		//{
		//	GameEngineDirectory Dir;
		//	Dir.MoveParentToExitsChildDirectory("ContentsResources");
		//	Dir.Move("ContentsResources");
		//	Dir.Move("Mesh");
		//	Dir.Move("Level");
		//	Dir.Move("2_1");

		//	for (int i = 0; i < FindFBXMesh->GetFbxRenderUnit().size(); ++i)
		//	{
		//		FindFBXMesh->GetFbxRenderUnit()[i].MaterialData[0].NorTexturePath = Dir.GetFullPath();
		//		FindFBXMesh->GetFbxRenderUnit()[i].MaterialData[0].NorTextureName = "t_dlc3_snow_01_n.png";

		//	}

		//}

		Renderer_->SetFBXMesh(_Name.data(), "Texture");
		Renderer_->GetTransform().SetWorldScale({ 40, 40, 40 });
	};

	std::shared_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}

protected:
	void Start() override;
	void Update(float _Update) override;
	void End() override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

