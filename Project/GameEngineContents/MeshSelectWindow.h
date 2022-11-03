#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class MeshSelectWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	MeshSelectWindow();
	~MeshSelectWindow();

	// delete Function
	MeshSelectWindow(const MeshSelectWindow& _Other) = delete;
	MeshSelectWindow(MeshSelectWindow&& _Other) noexcept = delete;
	MeshSelectWindow& operator=(const MeshSelectWindow& _Other) = delete;
	MeshSelectWindow& operator=(MeshSelectWindow&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


private:

	bool OpenFbx_;
	int ListIndex_;

	GameEngineFBXRenderer* PreviewMesh_;

	std::vector<GameEngineFBXMesh*> AllFBXMesh_;

};

