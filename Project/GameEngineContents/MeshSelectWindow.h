#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct PreviewMeshInfo
{
	std::string DifTexturePath_;
	std::string DifTextureName_;
};

// 설명 :
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

	std::string PreviewMeshName_;							// 선택한 Fbx 이름
	std::vector<PreviewMeshInfo> PreviewMeshInfo_;			// 패스, 파일이름 저장. 실제 렌더유닛 인덱스 순으로 push 하고 있음

	GameEngineFBXRenderer* PreviewMeshRenderer_;			// 선택한 fbx의 서브셋의 랜더러
	GameEngineFBXMesh* PreviewMesh_;						// 선택한 서브셋의 매쉬정보
	std::vector<GameEngineFBXMesh*> AllFBXMesh_;			// 게임 내의 모든 fbx

	std::vector<GameEngineTexture*> AllMaterialTexture_;	// 선택한 fbx의 매테리얼

};

